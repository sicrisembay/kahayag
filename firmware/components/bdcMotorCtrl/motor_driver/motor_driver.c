//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "freertos/FreeRTOS.h"
#include "motor_driver.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_struct.h"
#include "esp_log.h"

//*****************************************************************************
// Private definitions.
//*****************************************************************************

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
    int pwm_io_chA;
    int pwm_io_chB;
    fix16_t q16_maxDuty;
    fix16_t q16_minDuty;
} motor_driver_config_t;

static motor_driver_config_t const MOTOR_DRIVER_CFG[MOTOR_DRIVER_MAX] = {
    {
        .unit = MCPWM_UNIT_0,
        .timer = MCPWM_TIMER_0,
        .pwmA = MCPWM0A,
        .pwmB = MCPWM0B,
        .pwm_io_chA = CONFIG_PWM1_CHA_IO_PIN,
        .pwm_io_chB = CONFIG_PWM1_CHB_IO_PIN,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
    },
    {
        .unit = MCPWM_UNIT_0,
        .timer = MCPWM_TIMER_1,
        .pwmA = MCPWM1A,
        .pwmB = MCPWM1B,
        .pwm_io_chA = CONFIG_PWM2_CHA_IO_PIN,
        .pwm_io_chB = CONFIG_PWM2_CHB_IO_PIN,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
    },
    {
        .unit = MCPWM_UNIT_1,
        .timer = MCPWM_TIMER_0,
        .pwmA = MCPWM0A,
        .pwmB = MCPWM0B,
        .pwm_io_chA = CONFIG_PWM3_CHA_IO_PIN,
        .pwm_io_chB = CONFIG_PWM3_CHB_IO_PIN,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
    },
    {
        .unit = MCPWM_UNIT_1,
        .timer = MCPWM_TIMER_1,
        .pwmA = MCPWM1A,
        .pwmB = MCPWM1B,
        .pwm_io_chA = CONFIG_PWM3_CHA_IO_PIN,
        .pwm_io_chB = CONFIG_PWM3_CHB_IO_PIN,
        .q16_maxDuty = (fix16_t)(1 << 16),
        .q16_minDuty = -(fix16_t)(1 << 16),
    },
};

//*****************************************************************************
// Public / Internal member external declarations.
//*****************************************************************************
static fix16_t q16_dutyCycle[MOTOR_DRIVER_MAX] = {0};

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
    int id = 0;
    /* PWM GPIO Init */
    ESP_LOGI(TAG, "initializing mcpwm");

    for(id = 0; id < MOTOR_DRIVER_MAX; id++) {
        q16_dutyCycle[id] = (fix16_t)0;
        pwm_config.frequency = 40000;  /* 20kHz */
        pwm_config.cmpr_a = 0.0f;
        pwm_config.cmpr_b = 0.0f;
        pwm_config.duty_mode = MCPWM_DUTY_MODE_1; /* Active Low */
        pwm_config.counter_mode = MCPWM_UP_DOWN_COUNTER;

        mcpwm_gpio_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].pwmA, MOTOR_DRIVER_CFG[id].pwm_io_chA);
        mcpwm_gpio_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].pwmB, MOTOR_DRIVER_CFG[id].pwm_io_chB);
        mcpwm_init(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, &pwm_config);
    }

}

void motor_driver_safe_state(void)
{
    /* Set INA and INB high */
    int id = 0;
    portENTER_CRITICAL(&motor_drv_spinlock);
    for(id = 0; id < MOTOR_DRIVER_MAX; id++) {
        mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
        mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_B);
        q16_dutyCycle[id] = (fix16_t)0;
    }
    portEXIT_CRITICAL(&motor_drv_spinlock);
}

void motor_driver_set_value(motor_driver_id_t id, fix16_t value)
{
    fix16_t q16_duty;
    fix16_t q16_period;

    if(id < MOTOR_DRIVER_MAX) {
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
        } else if(value < (fix16_t)0) {
            value = -value;
            /* INA High */
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            /* INB PWM */
            q16_duty = fix16_mul(q16_period, value);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_value[MCPWM_OPR_B].cmpr_val = (uint32_t)(q16_duty >> 16);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.a_upmethod = BIT(0);
            PWM_UNIT[MOTOR_DRIVER_CFG[id].unit]->channel[MOTOR_DRIVER_CFG[id].timer].cmpr_cfg.b_upmethod = BIT(0);
        } else {
            /* INA and INB both High */
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_A);
            mcpwm_set_signal_high(MOTOR_DRIVER_CFG[id].unit, MOTOR_DRIVER_CFG[id].timer, MCPWM_OPR_B);
        }
        portEXIT_CRITICAL(&motor_drv_spinlock);
    }
}

fix16_t motor_driver_get_value(motor_driver_id_t id)
{
    fix16_t retval = (fix16_t)0;

    if(id < MOTOR_DRIVER_MAX) {
        retval = q16_dutyCycle[id];
    }
    return(retval);
}

