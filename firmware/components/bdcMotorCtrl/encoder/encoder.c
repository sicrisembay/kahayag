//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "encoder.h"
#include "test/test_encoder.h"
#include "driver/pcnt.h"
#include "driver/timer.h"
#include "fix16.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

//*****************************************************************************
// Private definitions.
//*****************************************************************************
#define FREE_RUNNING_TMR_PRESCALER    (10)
#define FREE_RUNNING_TMR_FREQUENCY    (TIMER_BASE_CLK / FREE_RUNNING_TMR_PRESCALER)
#define FREE_RUNNING_TMR_MAX_VAL      (uint32_t)(0xFFFFFFFFUL)
#define NUM_EDGES_PER_ENC_PERIOD      (4UL)     // QEI in 4X mode
#define TIMER_IDX                     (TIMER_0)
#define ENCODER_EDGE_TIMEOUT          (100 / CONFIG_MOTOR_CTRL_INTERVAL)     // unit is millisecond

#define ENCODER_MIN_INT_RATE_HZ       (1000UL)
#define ENCODER_MAX_TICK_PER_INT      (uint32_t)(FREE_RUNNING_TMR_FREQUENCY/ENCODER_MIN_INT_RATE_HZ)
#define ENCODER_MAX_INT_RATE_HZ       (3000UL)
#define ENCODER_MIN_TICK_PER_INT      (uint32_t)(FREE_RUNNING_TMR_FREQUENCY/ENCODER_MAX_INT_RATE_HZ)

// BEWARE OF OVERFLOW
#ifndef PI
#define PI                            (3.141592654f)
#endif
#define TWO_PI_FIX16                  (fix16_t)(411775)

#define MIN_SUPPORTED_ENC_PER_REV     (5)     // This is the minimum encoder stripes
                                                // per revolution supported.
                                                // Below this value (5), overflow occurs.
#if((FREE_RUNNING_TMR_FREQUENCY <= 8000000UL) && (MIN_SUPPORTED_ENC_PER_REV >= 5))
#define Q25_7_SPD_CONSTANT              ((int32_t)((((float)FREE_RUNNING_TMR_FREQUENCY * 2.0f * PI)/((float)NUM_EDGES_PER_ENC_PERIOD)) * 128.0f))
#else
#error "Overflow on Q25_7_SPD_CONSTANT"
#endif


typedef struct {
    uint32_t EncoderEdge:1;
    uint32_t EncoderValid:1;
    uint32_t EncoderFirstEdge:1;
    uint32_t EncoderType:2;
} encoder_flags_t;

typedef struct {
    pcnt_unit_t unit;
    encoder_decode_mode_t mode;
    uint32_t u32_EncPerRev;
    volatile int32_t s32_EncCount;
    volatile fix16_t q16_radPerSec;
    volatile int32_t s32_EncTimeDiff;
    volatile int32_t q24_8_TickPerEncEdg;
    volatile uint32_t u32_EncTimeStamp;
    volatile uint32_t u32_EncPrevTimeStamp;
    volatile int32_t s32_EncEdgePerInt;
    volatile uint32_t u32_EncEdgeTimeout;
    volatile uint32_t u32_isUpCounting;
    volatile encoder_flags_t flag;
} encoder_record_t;

//*****************************************************************************
// Private member declarations.
//*****************************************************************************
static pcnt_unit_t const ENCODER_PCNT_UNIT[ENCODER_ID_MAX] = {
    PCNT_UNIT_0,
    PCNT_UNIT_1,
    PCNT_UNIT_2,
    PCNT_UNIT_3,
};

static uint32_t const ENCODER_TYPE[ENCODER_ID_MAX] = {
    ENCODER_TYPE_QUAD,
    ENCODER_TYPE_QUAD,
    ENCODER_TYPE_QUAD,
    ENCODER_TYPE_QUAD,
};

static int const ENCODER_CHA_IO[ENCODER_ID_MAX] = {
    CONFIG_ENC1_CHA_IO_PIN,
    CONFIG_ENC2_CHA_IO_PIN,
    CONFIG_ENC3_CHA_IO_PIN,
    CONFIG_ENC4_CHA_IO_PIN
};

static int const ENCODER_CHB_IO[ENCODER_ID_MAX] = {
    CONFIG_ENC1_CHB_IO_PIN,
    CONFIG_ENC2_CHB_IO_PIN,
    CONFIG_ENC3_CHB_IO_PIN,
    CONFIG_ENC4_CHB_IO_PIN
};

static encoder_decode_mode_t const ENCODER_DECODE_MODE[ENCODER_ID_MAX] = {
    ENCODER_MODE_4X,
    ENCODER_MODE_4X,
    ENCODER_MODE_4X,
    ENCODER_MODE_4X,
};

static uint32_t const ENCODER_STRIPE_PER_REV[ENCODER_ID_MAX] = {
    100,
    100,
    100,
    100,
};

static const char *TAG = "encoder";

static encoder_record_t encoderRecord[ENCODER_ID_MAX];
pcnt_isr_handle_t encoder_isr_handle = NULL;

//*****************************************************************************
// Public / Internal member external declarations.
//*****************************************************************************

//*****************************************************************************
// Private function implementations.
//*****************************************************************************
static void IRAM_ATTR encoder_intr_handler(void *arg)
{
    uint32_t intr_status = PCNT.int_st.val;
    uint32_t i = 0;
    uint32_t sts;
    uint32_t timeStamp;
    uint32_t isUpCount;
    encoder_record_t * pEncRecord;

    /* Read timestamp */
    TIMERG0.hw_timer[TIMER_IDX].update = 1;
    timeStamp = TIMERG0.hw_timer[TIMER_IDX].cnt_low;

    for(i = 0; i < ENCODER_ID_MAX; i++) {
        if(intr_status & (BIT(encoderRecord[i].unit))) {
            pEncRecord = &encoderRecord[i];
            sts = PCNT.status_unit[pEncRecord->unit].val;
            PCNT.int_clr.val = BIT(pEncRecord->unit);

            if(sts & (PCNT_STATUS_H_LIM_M | PCNT_STATUS_L_LIM_M)) {
                pEncRecord->u32_EncTimeStamp = timeStamp;
                /* Update count */
                if(sts & PCNT_STATUS_H_LIM_M) {
                    pEncRecord->s32_EncCount += pEncRecord->s32_EncEdgePerInt;
                    isUpCount = 1;
                } else {
                    pEncRecord->s32_EncCount -= pEncRecord->s32_EncEdgePerInt;
                    isUpCount = 0;
                }
                /* Determine the number of timer ticks between interrupt */
                if((isUpCount == pEncRecord->u32_isUpCounting) && (1 == pEncRecord->flag.EncoderFirstEdge)) {
                    if(pEncRecord->u32_EncTimeStamp > pEncRecord->u32_EncPrevTimeStamp) {
                        pEncRecord->s32_EncTimeDiff = (int32_t)(pEncRecord->u32_EncTimeStamp -
                                                    pEncRecord->u32_EncPrevTimeStamp);
                    } else {
                        pEncRecord->s32_EncTimeDiff = (int32_t)((FREE_RUNNING_TMR_MAX_VAL -
                                pEncRecord->u32_EncPrevTimeStamp) + pEncRecord->u32_EncTimeStamp + 1);
                    }
                    /* Determine the number of ticks per encoder edge count */
                    if((pEncRecord->s32_EncEdgePerInt != 0) &&                  /* safeguard against divide by zero */
                       (pEncRecord->s32_EncTimeDiff < ((int32_t)1 << 23))) {    /* prevent overflow */
                        pEncRecord->q24_8_TickPerEncEdg = (pEncRecord->s32_EncTimeDiff << 8) /
                                                            pEncRecord->s32_EncEdgePerInt;
                    }
                }
                /* Store count direction */
                pEncRecord->u32_isUpCounting = isUpCount;
                /* Indicate that an edge has been seen */
                pEncRecord->flag.EncoderEdge = 1;
                /* If previous edge time was valid, then indicate that the time between
                 * edges is also now value */
                if(1 == pEncRecord->flag.EncoderFirstEdge) {
                    pEncRecord->flag.EncoderValid = 1;
                    /* Regulate rate of interrupt */
                    if(pEncRecord->s32_EncTimeDiff > (int32_t)ENCODER_MAX_TICK_PER_INT) {
                        /* Interrupt rate is slow, decrease Encoder per interrupt */
                        pEncRecord->s32_EncEdgePerInt = (int32_t)(pEncRecord->s32_EncEdgePerInt - NUM_EDGES_PER_ENC_PERIOD);
                        if(pEncRecord->s32_EncEdgePerInt < NUM_EDGES_PER_ENC_PERIOD) {
                            pEncRecord->s32_EncEdgePerInt = NUM_EDGES_PER_ENC_PERIOD;
                        }
                        /* Update */
                        pcnt_set_event_value(pEncRecord->unit, PCNT_EVT_H_LIM, (int16_t)(pEncRecord->s32_EncEdgePerInt));
                        pcnt_set_event_value(pEncRecord->unit, PCNT_EVT_L_LIM, (int16_t)(-pEncRecord->s32_EncEdgePerInt));
                    } else if(pEncRecord->s32_EncTimeDiff < (int32_t)ENCODER_MIN_TICK_PER_INT) {
                        // Interrupt rate is fast, increase encoder per interrupt
                        pEncRecord->s32_EncEdgePerInt = (int32_t)(pEncRecord->s32_EncEdgePerInt + NUM_EDGES_PER_ENC_PERIOD);
                        /* Update */
                        pcnt_set_event_value(pEncRecord->unit, PCNT_EVT_H_LIM, (int16_t)(pEncRecord->s32_EncEdgePerInt));
                        pcnt_set_event_value(pEncRecord->unit, PCNT_EVT_L_LIM, (int16_t)(-pEncRecord->s32_EncEdgePerInt));
                    }
                } else { // if(1 == pEncRecord->flag.EncoderFirstEdge)
                    /* First edge */
                    pEncRecord->flag.EncoderValid = 0;
                    pEncRecord->s32_EncTimeDiff = 0x00FFFFFF;
                    pEncRecord->q24_8_TickPerEncEdg = 0x7FFFFFFF;  // Max. positive value of Q24.8 = (2^(24-1) - 2^(-8))
                }
                pEncRecord->flag.EncoderFirstEdge = 1;

                /* Save information for the next iteration */
                pEncRecord->u32_EncPrevTimeStamp = pEncRecord->u32_EncTimeStamp;
            }
        }
    }
}

//*****************************************************************************
// Public function implementations
//*****************************************************************************
void encoder_init(void)
{
    pcnt_config_t pcnt_config;
    timer_config_t timer_config;
    uint32_t id;

    ESP_LOGI(TAG, "initializing...");

    /* Initialize timer used for encoder timestamp */
    timer_config.divider = FREE_RUNNING_TMR_PRESCALER;
    timer_config.counter_dir = TIMER_COUNT_UP;
    timer_config.counter_en = TIMER_PAUSE;
    timer_config.alarm_en = TIMER_ALARM_DIS;
    timer_config.intr_type = TIMER_INTR_LEVEL;
    timer_config.auto_reload = true;
    timer_init(TIMER_GROUP_0, TIMER_IDX, &timer_config);
    timer_set_counter_value(TIMER_GROUP_0, TIMER_IDX, 0x000ULL);
    timer_start(TIMER_GROUP_0, TIMER_IDX);

    for(id = 0; id < ENCODER_ID_MAX; id++) {
        encoderRecord[id].unit = ENCODER_PCNT_UNIT[id];
        encoderRecord[id].mode = ENCODER_DECODE_MODE[id];
        encoderRecord[id].s32_EncCount = 0;
        encoderRecord[id].q16_radPerSec = (fix16_t)0;
        encoderRecord[id].s32_EncEdgePerInt = NUM_EDGES_PER_ENC_PERIOD;
        encoderRecord[id].flag.EncoderEdge = 0;
        encoderRecord[id].flag.EncoderFirstEdge = 0;
        encoderRecord[id].flag.EncoderValid = 0;
        encoderRecord[id].flag.EncoderType = ENCODER_TYPE[id];
        encoderRecord[id].u32_EncPerRev = ENCODER_STRIPE_PER_REV[id];
        /* Channel 0 Configuration */
        pcnt_config.unit = ENCODER_PCNT_UNIT[id];
        pcnt_config.channel = PCNT_CHANNEL_0;
        pcnt_config.pulse_gpio_num = ENCODER_CHA_IO[id];
        pcnt_config.ctrl_gpio_num = ENCODER_CHB_IO[id];
        pcnt_config.pos_mode = PCNT_COUNT_INC;
        pcnt_config.neg_mode = PCNT_COUNT_DEC;
        pcnt_config.lctrl_mode = PCNT_MODE_KEEP;
        pcnt_config.hctrl_mode = PCNT_MODE_REVERSE;
        pcnt_config.counter_h_lim = (int16_t)(encoderRecord[id].s32_EncEdgePerInt);
        pcnt_config.counter_l_lim = (int16_t)(-pcnt_config.counter_h_lim);
        pcnt_unit_config(&pcnt_config);
        /* Channel 1 Configuration */
        pcnt_config.unit = ENCODER_PCNT_UNIT[id];
        pcnt_config.channel = PCNT_CHANNEL_1;
        pcnt_config.pulse_gpio_num = ENCODER_CHB_IO[id];
        pcnt_config.ctrl_gpio_num = ENCODER_CHA_IO[id];
        pcnt_config.pos_mode = PCNT_COUNT_INC;
        pcnt_config.neg_mode = PCNT_COUNT_DEC;
        pcnt_config.lctrl_mode = PCNT_MODE_REVERSE;
        pcnt_config.hctrl_mode = PCNT_MODE_KEEP;
        pcnt_config.counter_h_lim = (int16_t)(encoderRecord[id].s32_EncEdgePerInt);
        pcnt_config.counter_l_lim = (int16_t)(-pcnt_config.counter_h_lim);
        pcnt_unit_config(&pcnt_config);

        /// TODO: Configure input filters

        /* Enable Events */
        pcnt_event_enable(ENCODER_PCNT_UNIT[id], PCNT_EVT_H_LIM);
        pcnt_event_enable(ENCODER_PCNT_UNIT[id], PCNT_EVT_L_LIM);
        /* Initialize counter to zero */
        pcnt_counter_pause(ENCODER_PCNT_UNIT[id]);
        pcnt_counter_clear(ENCODER_PCNT_UNIT[id]);
    }

    /* Register ISR, Note: All units share the same interrupt */
    pcnt_isr_register(encoder_intr_handler, NULL, 0, &encoder_isr_handle);

    for(id = 0; id < ENCODER_ID_MAX; id++) {
        /* enable interrupt */
        pcnt_intr_enable(ENCODER_PCNT_UNIT[id]);
        /* Continue Counting */
        pcnt_counter_resume(ENCODER_PCNT_UNIT[id]);
    }
#if(ENABLE_ENCODER_TEST != 0)
    test_encoder_init();
#endif /* #if (ENABLE_ENCODER_TEST != 0) */
}

void encoder_deinit(void)
{
    uint32_t id = 0;

    for(id = 0; id < ENCODER_ID_MAX; id++) {
        pcnt_intr_disable(ENCODER_PCNT_UNIT[id]);
        pcnt_counter_pause(ENCODER_PCNT_UNIT[id]);
    }

    if(encoder_isr_handle) {
        /* Free ISR handle */
        esp_intr_free(encoder_isr_handle);
        encoder_isr_handle = NULL;
    }
}

void encoder_update(encoder_id_t id)
{
    encoder_record_t *pEncRecord = NULL;
    if(id < ENCODER_ID_MAX) {
        pEncRecord = &encoderRecord[id];
        /* See if an edge has been seen since the last call */
        if(pEncRecord->flag.EncoderEdge == 1) {
            /* Clear the edge flag */
            pEncRecord->flag.EncoderEdge = 0;
            /* Reset the delay counter */
            pEncRecord->u32_EncEdgeTimeout = ENCODER_EDGE_TIMEOUT;
        } else if(pEncRecord->u32_EncEdgeTimeout != 0){
            /* Decrement the delay counter */
            pEncRecord->u32_EncEdgeTimeout--;
            /* If the delay counter has reached zero, then indicate that there are
             * no valid speed values from the encoder.
             */
            if(pEncRecord->u32_EncEdgeTimeout == 0) {
                pEncRecord->flag.EncoderFirstEdge = 0;
                pEncRecord->flag.EncoderValid = 0;
            } else {
                /// TODO
            }
        }

        /* Calculate Speed */
        if(pEncRecord->flag.EncoderValid != 1) {
            /* No Valid Speed Values from encoder */
            pEncRecord->q16_radPerSec = 0;
        } else {
            if((pEncRecord->q24_8_TickPerEncEdg != 0) && (pEncRecord->u32_EncPerRev != 0)){ /* paranoid check */
                pEncRecord->q16_radPerSec = (((Q25_7_SPD_CONSTANT/pEncRecord->u32_EncPerRev) << 3) /
                                        pEncRecord->q24_8_TickPerEncEdg) << 14;
            }
        }

        /* Add direction information */
        if(pEncRecord->u32_isUpCounting != 1) {
            pEncRecord->q16_radPerSec = -pEncRecord->q16_radPerSec;
        }
    }
}

int32_t encoder_getCount(encoder_id_t id)
{
    int32_t retval = 0;
    encoder_record_t *pEncRec;
    int16_t count;
    if(id < ENCODER_ID_MAX) {
        pEncRec = &encoderRecord[id];
        pcnt_get_counter_value(pEncRec->unit, &count);
        retval = pEncRec->s32_EncCount + count;
    }
    return (retval);
}

void encoder_setCount(encoder_id_t id, int32_t count)
{
    encoder_record_t *pEncRec;
    if(id < ENCODER_ID_MAX) {
        pEncRec = &encoderRecord[id];
        pEncRec->s32_EncCount = 0;
    }
}

fix16_t encoder_get_position(encoder_id_t id)
{
    fix16_t retval = 0;
    int32_t count = 0;
    encoder_record_t *pEncRec;

    if(id < ENCODER_ID_MAX) {
        pEncRec = &encoderRecord[id];
        count = encoder_getCount(id);
        /* 1X decoding */
        retval = count * (TWO_PI_FIX16 / pEncRec->u32_EncPerRev);
        /* adjusted for 4X decoding */
        retval = retval >> 2;
    }
    return (retval);
}

fix16_t encoder_get_speed(encoder_id_t id)
{
    fix16_t retval = 0;
    if(id < ENCODER_ID_MAX) {
        retval = encoderRecord[id].q16_radPerSec;
    }
    return (retval);
}
