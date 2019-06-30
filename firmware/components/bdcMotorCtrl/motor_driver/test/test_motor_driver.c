//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "test_motor_driver.h"
#if (ENABLE_MOTOR_DRIVER_TEST != 0)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../motor_driver.h"
#include "esp_log.h"

#define MOT_DRV_TEST_PRIO               (tskIDLE_PRIORITY + 1)
#define MOT_DRV_TEST_STACK_SIZE         (4096)
#define MOT_DRV_TEST_SIGNAL_PERIOD      (10000) /* 10s */
#define MOT_DRV_INC_VAL_Q16             (fix16_t)(65536 / (MOT_DRV_TEST_SIGNAL_PERIOD / (4 * CONFIG_MOTOR_CTRL_INTERVAL)))
#define MOT_DRV_MAX_TEST_CURR           (fix16_t)(1.5f * 65536)
#define MOT_DRV_INC_CUR_Q16             (fix16_t)(MOT_DRV_MAX_TEST_CURR / (MOT_DRV_TEST_SIGNAL_PERIOD / (4 * CONFIG_MOTOR_CTRL_INTERVAL)))

static const char *TAG = "motor_driver_test";

static fix16_t const SEED_VALUE[MOTOR_DRIVER_MAX] = {
    0,
    0,
    0,
    0
};

static void motor_driver_test_task(void * arg)
{
    TickType_t prevWakeTime;
    motor_driver_id_t id;
    fix16_t dutyCycle;
    fix16_t current;
    uint32_t dir[MOTOR_DRIVER_MAX] = {0, 0, 0, 0};

    ESP_LOGI(TAG, "Test Running...");

    for(id = MOTOR_DRIVER_ID_1; id < MOTOR_DRIVER_MAX; id++) {
        if(motor_driver_get_mode(id) == MOTOR_DRIVER_MODE_EXT_PWM) {
            motor_driver_set_extPwm(id, SEED_VALUE[id]);
        } else {
            motor_driver_set_current(id, SEED_VALUE[id]);
        }
    }
    prevWakeTime = xTaskGetTickCount();

    while(1) {
        vTaskDelayUntil(&prevWakeTime, CONFIG_MOTOR_CTRL_INTERVAL);
        for(id = MOTOR_DRIVER_ID_1; id < MOTOR_DRIVER_MAX; id++) {
            if(motor_driver_get_mode(id) == MOTOR_DRIVER_MODE_EXT_PWM) {
                dutyCycle = motor_driver_get_extPwm(id);
                if(dir[id]) {
                    if((dutyCycle + MOT_DRV_INC_VAL_Q16) <= fix16_one) {
                        motor_driver_set_extPwm(id, (dutyCycle + MOT_DRV_INC_VAL_Q16));
                    } else {
                        dir[id] = 0;
                        motor_driver_set_extPwm(id, (dutyCycle - MOT_DRV_INC_VAL_Q16));
                    }
                } else {
                    if((dutyCycle - MOT_DRV_INC_VAL_Q16) >= -fix16_one) {
                        motor_driver_set_extPwm(id, (dutyCycle - MOT_DRV_INC_VAL_Q16));
                    } else {
                        dir[id] = 1;
                        motor_driver_set_extPwm(id, (dutyCycle + MOT_DRV_INC_VAL_Q16));
                    }
                }
            } else if(motor_driver_get_mode(id) == MOTOR_DRIVER_MODE_CONST_CURRENT) {
                current = motor_driver_get_currentRef(id);
                if(dir[id]) {
                    if(current + MOT_DRV_INC_CUR_Q16 <= MOT_DRV_MAX_TEST_CURR) {
                        motor_driver_set_current(id, (current + MOT_DRV_INC_CUR_Q16));
                    } else {
                        dir[id] = 0;
                        motor_driver_set_current(id, (current - MOT_DRV_INC_CUR_Q16));
                    }
                } else {
                    if(current - MOT_DRV_INC_CUR_Q16 >= -MOT_DRV_MAX_TEST_CURR) {
                        motor_driver_set_current(id, (current - MOT_DRV_INC_CUR_Q16));
                    } else {
                        dir[id] = 1;
                        motor_driver_set_current(id, (current + MOT_DRV_INC_CUR_Q16));
                    }
                }
            } else {
                ESP_LOGE(TAG, "MOTOR_DRIVER_ID_%d Invalid Mode (%d)", id+1, motor_driver_get_mode(id));
            }
        }
    }
    vTaskDelete(NULL);
}

void test_motor_driver_init(void)
{
    ESP_LOGI(TAG, "initializing test");

    xTaskCreate(motor_driver_test_task,
                "mot_drv_test",
                MOT_DRV_TEST_STACK_SIZE,
                NULL,
                MOT_DRV_TEST_PRIO,
                NULL);
}

#endif /* #if (ENABLE_ENCODER_TEST != 0) */
