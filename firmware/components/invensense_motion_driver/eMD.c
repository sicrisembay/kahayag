#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "priorityList.h"
#include "eMD.h"
#include "hal_i2c.h"
#include "inv_mpu.h"

static const char *TAG = "mpu9250";

static TaskHandle_t mpu9250_task_handle;
static bool bInit = false;

static void _run_self_test(void)
{
    uint8_t rawData[6] = {0};
    int32_t aAvg[3] = {0};
    uint32_t i;

    mpu_set_sample_rate(1000);
    mpu_set_lpf(98);
    mpu_set_gyro_fsr(250);
    mpu_set_accel_fsr(2);

    for(i = 0; i < 200; i++) {

    }
}

static void _mpu9250_task(void *vArg)
{
    struct int_param_s int_param;
    int id;
    ESP_LOGI(TAG, "Initializing device...");
    id = mpu_get_devId();
    ESP_LOGI(TAG, "Device ID: 0x%02X", mpu_get_devId());
    if(id != 0x71) {
        ESP_LOGE(TAG, "MPU9250 not found!");
        vTaskSuspend(NULL);
    }

    if(mpu_init(&int_param)) {
        ESP_LOGE(TAG, "Failed to initialize MPU9250");
    } else {
        ESP_LOGI(TAG, "Initialized.");
    }

    _run_self_test();

    /* Chip Init Done */
    bInit = true;

    while(1) {
        vTaskDelay(100);
    }
}
esp_err_t eMD_Init(void)
{
    esp_err_t retval = ESP_OK;
    gpio_config_t io_conf;

    if(bInit != true) {
        if(esp32_i2c_init() != 0) {
            return (ESP_FAIL);
        }

        io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pin_bit_mask = (1ULL << CONFIG_MPU9250_INT_IO);
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;       /* external Pull-up resistor is present in board */
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        retval = gpio_config(&io_conf);
        if(retval != ESP_OK) {
            return(retval);
        }

#if defined(CONFIG_INVENSENSE_PINNED_TO_CORE_0)
        if(pdPASS != xTaskCreatePinnedToCore(
                    _mpu9250_task,            /* the task function */
                    "mpu9250",                /* the name of the task */
                    2048,                     /* stack size */
                    NULL,                     /* the 'pvParameters' parameter */
                    PRIORITY_MPU9250,         /* FreeRTOS priority */
                    &mpu9250_task_handle,     /* task handle */
                    APP_CPU_NUM)) {
#elif defined(CONFIG_INVENSENSE_PINNED_TO_CORE_1)
        if(pdPASS != xTaskCreatePinnedToCore(
                    _mpu9250_task,            /* the task function */
                    "mpu9250",                /* the name of the task */
                    4096,                     /* stack size */
                    NULL,                     /* the 'pvParameters' parameter */
                    PRIORITY_MPU9250,         /* FreeRTOS priority */
                    &mpu9250_task_handle,     /* task handle */
                    APP_CPU_NUM)) {
#else
        if(pdPASS != xTaskCreate(
                    _mpu9250_task,            /* the task function */
                    "mpu9250",                /* the name of the task */
                    2048,                     /* stack size */
                    NULL,                     /* the 'pvParameters' parameter */
                    PRIORITY_MPU9250,         /* FreeRTOS priority */
                    &mpu9250_task_handle)) {
#endif
            retval = ESP_FAIL;
        }
    }

    return (retval);
}
