#include "qpc.h"
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "dataStreamer.h"
#include "priorityList.h"
#include "signalList.h"
#include "userCommand.h"
#include "bdcMotor.h"

static uint32_t streamFlag = 0U;
static TickType_t streamInterval = 0;
static bool bInit = false;

static const char * TAG = "dataStreamer";
static SemaphoreHandle_t  xMutexDataStreamer;

static void _DataStreamerTask(void *pxParam)
{
    TickType_t xLastWakeTime;
    uint32_t streamFlagShadow = 0;
    ESP_LOGI(TAG, "Task is up.");
    xLastWakeTime = xTaskGetTickCount();
    while(1) {
        vTaskDelayUntil(&xLastWakeTime, streamInterval);

        if(pdTRUE == xSemaphoreTake(xMutexDataStreamer, portMAX_DELAY)) {
            streamFlagShadow = streamFlag;
            xSemaphoreGive(xMutexDataStreamer);
        }

        if(streamFlagShadow) {
            QS_BEGIN(RECORD_STREAM, _DataStreamerTask);
            QS_U8(3, STREAM_TAG);
            QS_U32(10, streamFlagShadow);

            if(streamFlagShadow & STREAM_MOTOR_ONE_POSITION_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_position(MOTOR_ID_ONE));
            }
            if(streamFlagShadow & STREAM_MOTOR_ONE_SPEED_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_speed(MOTOR_ID_ONE));
            }
            if(streamFlagShadow & STREAM_MOTOR_ONE_CURRENT_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_current(MOTOR_ID_ONE));
            }
            if(streamFlagShadow & STREAM_MOTOR_TWO_POSITION_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_position(MOTOR_ID_TWO));
            }
            if(streamFlagShadow & STREAM_MOTOR_TWO_SPEED_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_speed(MOTOR_ID_TWO));
            }
            if(streamFlagShadow & STREAM_MOTOR_TWO_CURRENT_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_current(MOTOR_ID_TWO));
            }
            if(streamFlagShadow & STREAM_MOTOR_THREE_POSITION_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_position(MOTOR_ID_THREE));
            }
            if(streamFlagShadow & STREAM_MOTOR_THREE_SPEED_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_speed(MOTOR_ID_THREE));
            }
            if(streamFlagShadow & STREAM_MOTOR_THREE_CURRENT_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_current(MOTOR_ID_THREE));
            }
            if(streamFlagShadow & STREAM_MOTOR_FOUR_POSITION_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_position(MOTOR_ID_FOUR));
            }
            if(streamFlagShadow & STREAM_MOTOR_FOUR_SPEED_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_speed(MOTOR_ID_FOUR));
            }
            if(streamFlagShadow & STREAM_MOTOR_FOUR_CURRENT_MASK) {
                QS_I32(10, (uint32_t)bdc_motor_get_current(MOTOR_ID_FOUR));
            }
            QS_END();
        }
    }
}
esp_err_t data_streamer_init(void)
{
    esp_err_t retval = ESP_OK;

    if(bInit != true) {
        streamFlag = 0;
        streamInterval = CONFIG_DATA_STREAMER_INTERVAL / portTICK_RATE_MS;

        xMutexDataStreamer = xSemaphoreCreateMutex();
        if(xMutexDataStreamer == NULL) {
            return(ESP_ERR_NO_MEM);
        }

        if(pdPASS != xTaskCreate(_DataStreamerTask, "Stream", CONFIG_DATA_STREAMER_STACK_SIZE, NULL, PRIORITY_DATA_STREAMER, NULL)) {
            vSemaphoreDelete(xMutexDataStreamer);
            return(ESP_ERR_NO_MEM);
        }

        bInit = true;
    }

    return(retval);
}

esp_err_t data_streamer_enable(uint32_t streamMask, bool enable)
{
    esp_err_t retval = ESP_OK;
    if(pdTRUE == xSemaphoreTake(xMutexDataStreamer, portMAX_DELAY)) {
        if(enable) {
            streamFlag |= streamMask;
        } else {
            streamFlag &= ~streamMask;
        }
        xSemaphoreGive(xMutexDataStreamer);
    }
    return(retval);
}

esp_err_t data_streamer_setInterval(uint32_t intMs)
{
    esp_err_t retval = ESP_OK;
    if(intMs > 0) {
        streamInterval = intMs;
    } else {
        retval = ESP_ERR_INVALID_ARG;
    }
    return(retval);
}
