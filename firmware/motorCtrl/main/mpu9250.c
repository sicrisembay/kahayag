#include "qpc.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "priorityList.h"
#include "mpu9250.h"
#include "fix16.h"

static const char *TAG = "mpu9250";

#define _I2C_NUMBER(num)                I2C_NUM_##num
#define I2C_NUMBER(num)                 _I2C_NUMBER(num)
#define I2C_MASTER_NUM                  I2C_NUMBER(CONFIG_MPU9250_I2C_PORT_NUM)
#define MPU9250_DEV_ADDR                (0x68)
#define WRITE_BIT                       I2C_MASTER_WRITE        /*!< I2C master write */
#define READ_BIT                        I2C_MASTER_READ         /*!< I2C master read */
#define ACK_CHECK_EN                    (0x1)                   /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS                   (0x0)                   /*!< I2C master will not check ack from slave */
#define ACK_VAL                         (0x0)                   /*!< I2C ack value */
#define NACK_VAL                        (0x1)                   /*!< I2C nack value */

static TaskHandle_t mpu9250_task_handle;
static bool bInit = false;

static uint8_t const init_conf[][2] = {
        {MPU9250_REG_ADDR_PWR_MGMT_1, 0x80},    /* reset */
        {MPU9250_REG_ADDR_PWR_MGMT_1, 0x01},    /* clock source */
        {MPU9250_REG_ADDR_PWR_MGMT_2, 0x3F},    /* disable accel & gyro */
        {MPU9250_REG_ADDR_INT_PIN_CFG, 0xF0},   /* INT pin active low, open drain, latch enable */
        {MPU9250_REG_ADDR_I2C_MST_CTRL, 0x0D},  /* I2C master clock: 400kHz */
        {MPU9250_REG_ADDR_USER_CTRL, 0x20},     /* I2C Master mode */
        {0xFF, 0xFF} /* Watermark for end of entry */
};

static uint8_t magnetometer_calib[3];

static esp_err_t _i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, size_t size)
{
    esp_err_t retval = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, addr << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    retval = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if(retval != ESP_OK) {
        return(retval);
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, addr << 1 | READ_BIT, ACK_CHECK_EN);
    if(size > 1) {
        i2c_master_read(cmd, buf, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, buf + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    retval = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return(retval);
}

static esp_err_t _i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, size_t size)
{
    esp_err_t retval = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_write(cmd, buf, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    retval = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return(retval);
}

static esp_err_t _i2c_write_byte(uint8_t addr, uint8_t reg, uint8_t byte) {
    esp_err_t retval = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, byte, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    retval = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return(retval);
}

#define Q16_1_01    (66191)

static void _mpu9250_selftest(void)
{
    uint8_t rawData[14] = {0};
    uint8_t selfTest[6];
    int32_t gAvg[3] = {0};
    int32_t aAvg[3] = {0};
    int32_t aSTAvg[3] = {0};
    int32_t gSTAvg[3] = {0};
    fix16_t factoryTrim[6];
    uint8_t FS = 0;
    int32_t ii;
    TickType_t xLastWakeTime;
    fix16_t aTrimDelta[3];
    fix16_t gTrimDelta[3];

    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_CONFIG, 0x02);        // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_GYRO_CONFIG, 0x01); // Set full scale range for the gyro to 250 dps
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_CONFIG_2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_CONFIG, 0x01); // Set full scale range for the accelerometer to 2 g

    xLastWakeTime = xTaskGetTickCount();

    for(ii = 0; ii < 200; ii++) { // get average current values of gyro and acclerometer
        vTaskDelayUntil( &xLastWakeTime, 1);
        _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_XOUT_H, &rawData[0], 14);        // Read the six raw data registers into data array
        aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);
        aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
        // Temperature rawData[6] and rawData[7]
        gAvg[0] += (int16_t)(((int16_t)rawData[8] << 8) | rawData[9]);
        gAvg[1] += (int16_t)(((int16_t)rawData[10] << 8) | rawData[11]);
        gAvg[2] += (int16_t)(((int16_t)rawData[12] << 8) | rawData[13]);
    }
    ESP_LOGI(TAG,"Sum A:(%d, %d, %d) Sum G: (%d, %d, %d)",
                aAvg[0], aAvg[1], aAvg[2],
                gAvg[0], gAvg[1], gAvg[2]);

    for(ii = 0; ii < 3; ii++) {
        aAvg[ii] /= 200;
        gAvg[ii] /= 200;
    }

    // Configure the accelerometer for self-test
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_GYRO_CONFIG,  0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
    vTaskDelay(25);  // Delay a while to let the device stabilize

    for(ii = 0; ii < 200; ii++) { // get average current values of gyro and acclerometer
        vTaskDelayUntil( &xLastWakeTime, 1);
        _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_XOUT_H, &rawData[0], 14);        // Read the six raw data registers into data array
        aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);
        aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
        // Temperature rawData[6] and rawData[7]
        gSTAvg[0] += (int16_t)(((int16_t)rawData[8] << 8) | rawData[9]);
        gSTAvg[1] += (int16_t)(((int16_t)rawData[10] << 8) | rawData[11]);
        gSTAvg[2] += (int16_t)(((int16_t)rawData[12] << 8) | rawData[13]);
    }

    for(ii = 0; ii < 3; ii++) {
        aSTAvg[ii] /= 200;
        gSTAvg[ii] /= 200;
    }

    // Configure the gyro and accelerometer for normal operation
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_ACCEL_CONFIG, 0x00);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_GYRO_CONFIG,  0x00);
    vTaskDelay(25);  // Delay a while to let the device stabilize

    // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
    _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_SELF_TEST_X_ACCEL, &selfTest[0], 3);
    _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_SELF_TEST_X_GYRO, &selfTest[3], 3);

    for(ii = 0; ii < 6; ii++) {
        factoryTrim[ii] = fix16_one;
        /* Power calculation: power(1.01, selfTest[ii] - 1) */
        for(int jj = 0; jj < (selfTest[ii] - 1); jj++) {
            factoryTrim[ii] = fix16_mul(factoryTrim[ii], Q16_1_01);
        }
        factoryTrim[ii] = fix16_mul((2620 << 16), factoryTrim[ii]);
    }

    for(ii = 0; ii < 3; ii++) {
        aTrimDelta[ii] = fix16_div((aSTAvg[ii] - aAvg[ii]) << 16, factoryTrim[ii]);
        aTrimDelta[ii] = (100 * aTrimDelta[ii]) - (100 << 16);
        gTrimDelta[ii] = fix16_div((gSTAvg[ii] - gAvg[ii]) << 16, factoryTrim[ii + 3]);
        gTrimDelta[ii] = (100 * gTrimDelta[ii]) - (100 << 16);
    }
#if 1
    ESP_LOGI(TAG,"A:(%d, %d, %d) G: (%d, %d, %d)",
            aAvg[0], aAvg[1], aAvg[2],
            gAvg[0], gAvg[1], gAvg[2]);
    ESP_LOGI(TAG,"ST A:(%d, %d, %d) ST G: (%d, %d, %d)",
            aSTAvg[0], aSTAvg[1], aSTAvg[2],
            gSTAvg[0], gSTAvg[1], gSTAvg[2]);
    ESP_LOGI(TAG,"Trim accel:(%d, %d, %d) Trim gyro: (%d, %d, %d)",
            selfTest[0], selfTest[1], selfTest[2],
            selfTest[3], selfTest[4], selfTest[5]);
    ESP_LOGI(TAG, "Accel Trim Change: %f%%, %f%%, %f%%",
            aTrimDelta[0] / 65536.0f,
            aTrimDelta[1] / 65536.0f,
            aTrimDelta[2] / 65536.0f);
    ESP_LOGI(TAG, "Gyro Trim Change: %f%%, %f%%, %f%%",
            gTrimDelta[0] / 65536.0f,
            gTrimDelta[1] / 65536.0f,
            gTrimDelta[2] / 65536.0f);
#endif
}

static void _mpu9250_task(void *vArg)
{
    uint32_t i;
    uint8_t val;

    ESP_LOGI(TAG, "Initializing device.");
    bInit = false;
    /* Check if MPU9250 device is present *********************/
    for(i = 0; i < 10; i++) {
        val = 0;
        _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_WHO_AM_I, &val, 1);
        if(0x71 == val) {
            ESP_LOGI(TAG, "MPU9250 chip found");
            break;
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
    if(val != 0x71) {
        ESP_LOGE(TAG, "MPU9250 not found.");
        vTaskSuspend(NULL);
    }

    /* Self Test */
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_PWR_MGMT_1, 0x80);
    vTaskDelay(100);
    _mpu9250_selftest();

    /* Init main chip */
    for(i = 0; init_conf[i][0] != 0xFF; i++) {
        if(ESP_OK != _i2c_write_byte(MPU9250_DEV_ADDR, init_conf[i][0], init_conf[i][1])) {
            ESP_LOGE(TAG, "Error in main chip initialization");
            vTaskSuspend(NULL);
        }
        vTaskDelay(1 / portTICK_RATE_MS);
    }

    /* Init AK8963 chip */
    /* AK8963 ID */
    ESP_ERROR_CHECK(_i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_ADDR, AK8963_I2C_ADDR | 0x80));
    ESP_ERROR_CHECK(_i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_REG,  AK8963_REG_WIA));
    ESP_ERROR_CHECK(_i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_CTRL, 0x81));
    for (int i = 0; i < 100; i++) {
        vTaskDelay(10 / portTICK_RATE_MS);
        val = 0;
        ESP_ERROR_CHECK(_i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_EXT_SENS_DATA_00, &val, 1));
        if (val == 0x48) {
            ESP_LOGI(TAG, "AK8963 chip found.");
            break;
        }
    }
    if (val != 0x48) {
        ESP_LOGE(TAG, "AK8963 not found (0x%02x).", val);
        vTaskSuspend(NULL);
    }
    /* Reset */
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_ADDR, AK8963_I2C_ADDR);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_REG, AK8963_REG_CNTL1);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_DO, 0x12);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_CTRL, 0x83);
    vTaskDelay(10 / portTICK_RATE_MS);
    /* Read AK8963 calibration data */
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_ADDR, AK8963_I2C_ADDR | 0x80);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_REG,  AK8963_REG_ASAX);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_CTRL, 0x83);
    vTaskDelay(10 / portTICK_RATE_MS);
    _i2c_read(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_EXT_SENS_DATA_00, magnetometer_calib, sizeof(magnetometer_calib));
    ESP_LOGI(TAG, "AK8963 cal value: %d, %d, %d",
            magnetometer_calib[0],
            magnetometer_calib[1],
            magnetometer_calib[2]);
    /* AK8963 Periodical mode */
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_ADDR, AK8963_I2C_ADDR);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_REG,  AK8963_REG_CNTL1);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_DO,   0x12);
    _i2c_write_byte(MPU9250_DEV_ADDR, MPU9250_REG_ADDR_I2C_SLV0_CTRL, 0x81);
    vTaskDelay(10 / portTICK_RATE_MS);

    /* Chip Init Done */
    bInit = true;

    while(1) {
        vTaskDelay(100);
    }
}

esp_err_t mpu9250_init(void)
{
    esp_err_t retval = ESP_OK;
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    gpio_config_t io_conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = CONFIG_MPU9250_I2C_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;       /* external Pull-up resistor is present in board */
    conf.scl_io_num = CONFIG_MPU9250_I2C_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;       /* external Pull-up resistor is present in board */
    conf.master.clk_speed = CONFIG_MPU9250_I2C_CLK_FREQ;
    i2c_param_config(i2c_master_port, &conf);
    retval = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);
    if(retval != ESP_OK) {
        return(retval);
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

#if defined(CONFIG_USER_APP_PINNED_TO_CORE_0)
    if(pdPASS != xTaskCreatePinnedToCore(
                _mpu9250_task,            /* the task function */
                "mpu9250",                /* the name of the task */
                2048,                     /* stack size */
                NULL,                     /* the 'pvParameters' parameter */
                PRIORITY_MPU9250,         /* FreeRTOS priority */
                &mpu9250_task_handle,     /* task handle */
                APP_CPU_NUM)) {
#elif defined(CONFIG_USER_APP_PINNED_TO_CORE_1)
    if(pdPASS != xTaskCreatePinnedToCore(
                _mpu9250_task,            /* the task function */
                "mpu9250",                /* the name of the task */
                2048,                     /* stack size */
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
    return (retval);
}
