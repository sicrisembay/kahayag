//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "freertos/FreeRTOS.h"
#include "motor_driver.h"
#include "driver/mcpwm.h"
#include "driver/gpio.h"
#include "soc/mcpwm_struct.h"
#include "esp_log.h"
#include "test/test_motor_driver.h"

//*****************************************************************************
// Private definitions.
//*****************************************************************************
/*
 * Vin = 3.3V * DutyCycle
 * Vref = Vin * (5K / (5K + 4.7K)) = DutyCycle * (3.3V * 5K) / (5K + 4.7K)
 * Vref = 1.701031 * DutyCycle
 * Iref = (Vref / 8) / Rsense
 * Iref = DutyCycle * (1.701031 / 8) / 0.1ohm
 * Iref = DutyCycle * 2.126289
 * CURRENT_TO_DUTY_FACTOR = 0.470303
 * Q16_CURRENT_TO_DUTY_FACTOR = 30822
 */
#define Q16_CURRENT_TO_DUTY_FACTOR      ((fix16_t)30822)
#define Q16_BD62220_MAX_CURRENT         ((fix16_t)(2 << 16))

//*****************************************************************************
// Private member declarations.
//*****************************************************************************
static const char *TAG = "motor_driver";
static portMUX_TYPE motor_drv_spinlock = portMUX_INITIALIZER_UNLOCKED;
static mcpwm_dev_t * PWM_UNIT[2] = {&MCPWM0, &MCPWM1};

typedef struct {
    mcpwm_unit_t unit;
    mcpwm_timer_t timer;
    mcpwm_io_signals_t pwmA;
    mcpwm_io_signals_t pwmB;
    motor_driver_mode_t mode;
    int io_inA;
    int io_inB;
    int io_vref;
    fix16_t q16_maxDuty;
    fix16_t q16_minDuty;
    fix16_t q16_maxCurrent;
    fix16_t q16_minCurrent;
} motor_driver_config_t;

static motor_driver_config_t const MOTOR_DRIVER_CFG[MOTOR_DRIVER_MAX] = {
    {
        .unit = MCPWM_UNIT_0,
        .timer = MCPWM_TIMER_0,
        .pwmA = MCPWM0A,
        .pwmB = MCPWM0B,
#if defined CONFIG_DRV1_EXT_PWM
        .mode = MOTOR_DRIVER_MODE_EXT_PWM,
#elif defined CONFIG_DRV1_CONST_CURRENT
        .mode = MOTOR_DRIVER_MODE_CONST_CURRENT,
#endif
        .io_inA = CONFIG_DRV1_INA_IO_PIN,
        .io_inB = CONFIG_DRV1_INB_IO_PIN,
        .io_vref = CONFIG_DRV1_VREF_IO,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
        .q16_maxCurrent = Q16_BD62220_MAX_CURRENT,
        .q16_minCurrent = -Q16_BD62220_MAX_CURRENT,
    },
    {
        .unit = MCPWM_UNIT_0,
        .timer = MCPWM_TIMER_1,
        .pwmA = MCPWM1A,
        .pwmB = MCPWM1B,
#if defined CONFIG_DRV2_EXT_PWM
        .mode = MOTOR_DRIVER_MODE_EXT_PWM,
#elif defined CONFIG_DRV2_CONST_CURRENT
        .mode = MOTOR_DRIVER_MODE_CONST_CURRENT,
#endif
        .io_inA = CONFIG_DRV2_INA_IO_PIN,
        .io_inB = CONFIG_DRV2_INB_IO_PIN,
        .io_vref = CONFIG_DRV2_VREF_IO,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
        .q16_maxCurrent = Q16_BD62220_MAX_CURRENT,
        .q16_minCurrent = -Q16_BD62220_MAX_CURRENT,
    },
    {
        .unit = MCPWM_UNIT_1,
        .timer = MCPWM_TIMER_0,
        .pwmA = MCPWM0A,
        .pwmB = MCPWM0B,
#if defined CONFIG_DRV3_EXT_PWM
        .mode = MOTOR_DRIVER_MODE_EXT_PWM,
#elif defined CONFIG_DRV3_CONST_CURRENT
        .mode = MOTOR_DRIVER_MODE_CONST_CURRENT,
#endif
        .io_inA = CONFIG_DRV3_INA_IO_PIN,
        .io_inB = CONFIG_DRV3_INB_IO_PIN,
        .io_vref = CONFIG_DRV3_VREF_IO,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
        .q16_maxCurrent = Q16_BD62220_MAX_CURRENT,
        .q16_minCurrent = -Q16_BD62220_MAX_CURRENT,
    },
    {
        .unit = MCPWM_UNIT_1,
        .timer = MCPWM_TIMER_1,
        .pwmA = MCPWM1A,
        .pwmB = MCPWM1B,
#if defined CONFIG_DRV4_EXT_PWM
        .mode = MOTOR_DRIVER_MODE_EXT_PWM,
#elif defined CONFIG_DRV4_CONST_CURRENT
        .mode = MOTOR_DRIVER_MODE_CONST_CURRENT,
#endif
        .io_inA = CONFIG_DRV4_INA_IO_PIN,
        .io_inB = CONFIG_DRV4_INB_IO_PIN,
        .io_vref = CONFIG_DRV4_VREF_IO,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
        .q16_maxCurrent = Q16_BD62220_MAX_CURRENT,
        .q16_minCurrent = -Q16_BD62220_MAX_CURRENT,
    },
};

//*****************************************************************************
// Public / Internal member external declarations.
//*****************************************************************************
static fix16_t q16_dutyCycle[MOTOR_DRIVER_MAX] = {0};
static fix16_t q16_CurrentRef[MOTOR_DRIVER_MAX] = {0};

//*****************************************************************************
// Private function prototypes.
//*****************************************************************************

//*****************************************************************************
// Private function implementations.
//*****************************************************************************

//*****************************************************************************
// Public function implementations
//*****************************************************************************

void motor_driver_init(void)
{
    mcpwm_config_t pwm_config;
    gpio_config_t io_config;
    int id = 0;
    /* PWM GPIO Init */
    ESP_LOGI(TAG, "initializing...");

    for(id = 0; id < MOTOR_DRIVER_MAX; id++) {
        q16_CurrentRef[id] = (fix16_t)0;
        q16_dutyCycle[id] = (fix16_t)0;

        if(MOTOR_DRIVER_CFG[id].mode == MOTOR_DRIVER_MODE_EXT_PWM) {
            /* External PWM is applied to INA and INB of Rohm Driver */
            pwm_config.frequency = 40000;  /* 20kHz */
            pwm_config.cmpr_a = 0.0f;
            pwm_config.cmpr_b = 0.0f;
            pwm_config.duty_mode = MCPWM_DUTY_MODE_1; /* Active Low */
            pwm_config.counter_mode = MCPWM_UP_DOWN_COUNTER;
            mcpwm_gpio_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].pwmA, MOTOR_DRIVER_CFG[id].io_inA);
            mcpwm_gpio_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].pwmB, MOTOR_DRIVER_CFG[id].io_inB);
            mcpwm_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, &pwm_config);
            /* Vref is held high */
            io_config.intr_type = GPIO_PIN_INTR_DISABLE;
            io_config.mode = GPIO_MODE_OUTPUT;
            io_config.pin_bit_mask = 1ULL << MOTOR_DRIVER_CFG[id].io_vref;
            io_config.pull_down_en = 0;
            io_config.pull_up_en = 0;
            gpio_config(&io_config);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_vref, 1);
        } else if(MOTOR_DRIVER_CFG[id].mode == MOTOR_DRIVER_MODE_CONST_CURRENT) {
            /* INA and INB is used for motor direction */
            io_config.intr_type = GPIO_PIN_INTR_DISABLE;
            io_config.mode = GPIO_MODE_OUTPUT;
            io_config.pin_bit_mask = ((1ULL << MOTOR_DRIVER_CFG[id].io_inA) | (1ULL << MOTOR_DRIVER_CFG[id].io_inB));
            io_config.pull_down_en = 0;
            io_config.pull_up_en = 0;
            gpio_config(&io_config);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inA, 1);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inB, 1);
            /* PWM IO is used to set Vref */
            pwm_config.frequency = 40000;  /* 20kHz */
            pwm_config.cmpr_a = 0.0f;
            pwm_config.cmpr_b = 0.0f;
            pwm_config.duty_mode = MCPWM_DUTY_MODE_0; /* Active High */
            pwm_config.counter_mode = MCPWM_UP_DOWN_COUNTER;
            mcpwm_gpio_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].pwmA, MOTOR_DRIVER_CFG[id].io_vref);
            mcpwm_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, &pwm_config);
        } else {
            ESP_LOGE(TAG, "unsupported driver mode!");
        }
    }

#if (ENABLE_MOTOR_DRIVER_TEST != 0)
    test_motor_driver_init();
#endif /* #if (ENABLE_MOTOR_DRIVER_TEST != 0) */
}

void motor_driver_safe_state(void)
{
    /* Set INA and INB high */
    int id = 0;
    for(id = 0; id < MOTOR_DRIVER_MAX; id++) {
        if(MOTOR_DRIVER_CFG[id].mode == MOTOR_DRIVER_MODE_EXT_PWM) {
            portENTER_CRITICAL(&motor_drv_spinlock);
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_B);
            q16_dutyCycle[id] = (fix16_t)0;
            portEXIT_CRITICAL(&motor_drv_spinlock);
        } else if(MOTOR_DRIVER_CFG[id].mode == MOTOR_DRIVER_MODE_CONST_CURRENT) {
            portENTER_CRITICAL(&motor_drv_spinlock);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inA, 1);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inB, 1);
            mcpwm_set_signal_low(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            portEXIT_CRITICAL(&motor_drv_spinlock);
        } else {
            ESP_LOGE(TAG, "unsupported driver mode!");
        }
    }
}

void motor_driver_set_extPwm(motor_driver_id_t id, fix16_t value)
{
    fix16_t q16_duty;
    fix16_t q16_period;

    if(id < MOTOR_DRIVER_MAX) {
        if(MOTOR_DRIVER_CFG[id].mode != MOTOR_DRIVER_MODE_EXT_PWM) {
            ESP_LOGW(TAG, "Incompatible mode (%d)", MOTOR_DRIVER_CFG[id].mode);
            return;
        }
        /* Duty Cycle should be within limit */
        if(value > MOTOR_DRIVER_CFG[id].q16_maxDuty) {
            value = MOTOR_DRIVER_CFG[id].q16_maxDuty;
        } else if(value < MOTOR_DRIVER_CFG[id].q16_minDuty) {
            value = MOTOR_DRIVER_CFG[id].q16_minDuty;
        }
        q16_dutyCycle[id] = value;

        portENTER_CRITICAL(&motor_drv_spinlock);

        q16_period = (fix16_t)(PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->timer[MOTOR_DRIVER_CFG[id].timer].period.period) << 16;

        if(value > (fix16_t)0) {
            /* INB High */
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_B);
            /* INA PWM */
            q16_duty = fix16_mul(q16_period, value);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_value[MCPWM_OPR_A].cmpr_val = (uint32_t)(q16_duty >> 16);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.a_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.b_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utez = 1;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utea = 2;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].dtea = 1;
        } else if(value < (fix16_t)0) {
            value = -value;
            /* INA High */
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            /* INB PWM */
            q16_duty = fix16_mul(q16_period, value);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_value[MCPWM_OPR_B].cmpr_val = (uint32_t)(q16_duty >> 16);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.a_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.b_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_B].utez = 1;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_B].uteb = 2;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_B].dteb = 1;
        } else {
            /* INA and INB both High */
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_B);
        }
        portEXIT_CRITICAL(&motor_drv_spinlock);
    }
}

void motor_driver_set_current(motor_driver_id_t id, fix16_t value)
{
    fix16_t q16_duty;
    fix16_t q16_period;

    if(id < MOTOR_DRIVER_MAX) {
        if(MOTOR_DRIVER_CFG[id].mode != MOTOR_DRIVER_MODE_CONST_CURRENT) {
            ESP_LOGW(TAG, "Incompatible mode (%d)", MOTOR_DRIVER_CFG[id].mode);
            return;
        }

        /* current should be within limit */
        if(value > MOTOR_DRIVER_CFG[id].q16_maxCurrent) {
            value = MOTOR_DRIVER_CFG[id].q16_maxCurrent;
        } else if(value < MOTOR_DRIVER_CFG[id].q16_minCurrent) {
            value = MOTOR_DRIVER_CFG[id].q16_minCurrent;
        }
        q16_CurrentRef[id] = value;

        /* Convert current reference to duty cycle value */
        q16_dutyCycle[id] = fix16_mul(value, Q16_CURRENT_TO_DUTY_FACTOR);

        portENTER_CRITICAL(&motor_drv_spinlock);
        q16_period = (fix16_t)(PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->timer[MOTOR_DRIVER_CFG[id].timer].period.period) << 16;
        q16_duty = fix16_abs(fix16_mul(q16_period, q16_dutyCycle[id]));
        if(value > (fix16_t)0) {
            /* Set INA and INB */
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inA, 0);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inB, 1);
            /* Set Vref */
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_value[MCPWM_OPR_A].cmpr_val = (uint32_t)(q16_duty >> 16);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.a_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.b_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utez = 2;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utea = 1;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].dtea = 2;
        } else if(value < (fix16_t)0) {
            /* Set INA and INB */
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inA, 1);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inB, 0);
            /* Set Vref */
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_value[MCPWM_OPR_A].cmpr_val = (uint32_t)(q16_duty >> 16);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.a_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.b_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utez = 2;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].utea = 1;
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].generator[MCPWM_OPR_A].dtea = 2;
        } else {
            /* Set INA and INB */
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inA, 1);
            gpio_set_level(MOTOR_DRIVER_CFG[id].io_inB, 1);
            /* Set Vref */
            mcpwm_set_signal_low(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
        }
        portEXIT_CRITICAL(&motor_drv_spinlock);
    }
}

fix16_t motor_driver_get_extPwm(motor_driver_id_t id)
{
    fix16_t retval = (fix16_t)0;

    if(id < MOTOR_DRIVER_MAX) {
        retval = q16_dutyCycle[id];
    }
    return(retval);
}

fix16_t motor_driver_get_currentRef(motor_driver_id_t id)
{
    fix16_t retval = (fix16_t)0;
    if(id < MOTOR_DRIVER_MAX) {
        if(MOTOR_DRIVER_CFG[id].mode == MOTOR_DRIVER_MODE_CONST_CURRENT) {
            retval = q16_CurrentRef[id];
        }
    }
    return (retval);
}

motor_driver_mode_t motor_driver_get_mode(motor_driver_id_t id)
{
    motor_driver_mode_t driver_mode = MOTOR_DRIVER_MODE_MAX;
    if(id < MOTOR_DRIVER_MAX) {
        driver_mode = MOTOR_DRIVER_CFG[id].mode;
    }
    return(driver_mode);
}

