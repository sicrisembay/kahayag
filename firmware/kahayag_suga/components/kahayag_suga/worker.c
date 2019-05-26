/*$file${.::worker.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: kahayag_suga.qm
* File:  ${.::worker.c}
*
* This code has been generated by QM 4.5.0 (https://www.state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*$endhead${.::worker.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "worker.h"
#include "esp_log.h"
#include "soc/soc.h"
#include "priorityList.h"

#define WORKER_DEFAULT_STACK_SIZE        (2*configIDLE_TASK_STACK_SIZE)

static const char *TAG = "worker";

static void workTask(void *pParam)
{
    WorkFunction fcn = (WorkFunction)pParam;
    if(fcn != NULL) {
        (*fcn)();
    } else {
        ESP_LOGE(TAG, "Invalid Worker Function Pointer");
    }
    vTaskDelete(NULL);
}

esp_err_t doWork(WorkFunction fcn)
{
    esp_err_t retval = ESP_OK;

#if defined( CONFIG_QPC_PINNED_TO_CORE_0 )
    BaseType_t xCoreId = PRO_CPU_NUM;
#elif defined( CONFIG_QPC_PINNED_TO_CORE_1)
    BaseType_t xCoreId = APP_CPU_NUM;
#else
    BaseType_t xCoreId = tskNO_AFFINITY;
#endif

    /* Create Worker Thread */
    if(pdPASS != xTaskCreatePinnedToCore(
                    workTask,
                    "workTask",
                    WORKER_DEFAULT_STACK_SIZE,
                    (void *) fcn,
                    PRIORITY_WORKER,
                    NULL,
                    xCoreId)) {
        return ESP_FAIL;
    }

    return (retval);
}