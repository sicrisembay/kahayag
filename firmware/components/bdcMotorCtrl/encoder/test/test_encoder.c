//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "test_encoder.h"
#if (ENABLE_ENCODER_TEST != 0)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../encoder.h"
#include "esp_log.h"

#define ENCODER_TEST_PRIO               (tskIDLE_PRIORITY + 1)
#define ENCODER_TEST_STACK_SIZE         (4096)
#define ENCODER_TEST_PRINT_INTERVAL     (100)   /* millisecond */

static const char *TAG = "encoder_test";

static void encoder_test_task(void * arg)
{
    TickType_t prevWakeTime;
    encoder_id_t id;
    uint32_t cnt;

    ESP_LOGI(TAG, "Test Running...");
    prevWakeTime = xTaskGetTickCount();
    while(1) {
        vTaskDelayUntil(&prevWakeTime, CONFIG_MOTOR_CTRL_INTERVAL);
        for(id = ENCODER_ID_1; id < ENCODER_ID_MAX; id++) {
            encoder_update(id);
        }

        cnt += CONFIG_MOTOR_CTRL_INTERVAL;
        if(cnt >= ENCODER_TEST_PRINT_INTERVAL) {
            cnt = 0;
            ESP_LOGI(TAG, "ENC1 (Cnt:%d, Spd:%d) "
                    "ENC2 (Cnt:%d, Spd:%d) "
                    "ENC3 (Cnt:%d, Spd:%d) "
                    "ENC4 (Cnt:%d, Spd:%d) ",
                    /* Encoder One */
                    encoder_getCount(ENCODER_ID_1),
                    encoder_get_speed(ENCODER_ID_1) >> 16,
                    /* Encoder Two */
                    encoder_getCount(ENCODER_ID_2),
                    encoder_get_speed(ENCODER_ID_2) >> 16,
                    /* Encoder Three */
                    encoder_getCount(ENCODER_ID_3),
                    encoder_get_speed(ENCODER_ID_3) >> 16,
                    /* Encoder Four */
                    encoder_getCount(ENCODER_ID_4),
                    encoder_get_speed(ENCODER_ID_4) >> 16
                    );
        }
    }
    vTaskDelete(NULL);
}

void test_encoder_init(void)
{
    ESP_LOGI(TAG, "initializing test");

    xTaskCreate(encoder_test_task,
                "encoder_test",
                ENCODER_TEST_STACK_SIZE,
                NULL,
                ENCODER_TEST_PRIO,
                NULL);
}

#endif /* #if (ENABLE_ENCODER_TEST != 0) */
