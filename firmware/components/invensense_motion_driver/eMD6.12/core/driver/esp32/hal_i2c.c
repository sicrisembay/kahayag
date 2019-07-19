#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "hal_i2c.h"

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

int esp32_i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = CONFIG_MPU9250_I2C_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;       /* external Pull-up resistor is present in board */
    conf.scl_io_num = CONFIG_MPU9250_I2C_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;       /* external Pull-up resistor is present in board */
    conf.master.clk_speed = CONFIG_MPU9250_I2C_CLK_FREQ;
    i2c_param_config(i2c_master_port, &conf);
    if(ESP_OK != i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0)) {
        return -1;
    }
    return 0;
}

int esp32_i2c_write(unsigned char slave_addr,
                    unsigned char reg_addr,
                    unsigned char length,
                    unsigned char *data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(ESP_OK != i2c_master_start(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write_byte(cmd, (slave_addr << 1) | WRITE_BIT, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write(cmd, data, length, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_stop(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    i2c_cmd_link_delete(cmd);
    return 0;
}

int esp32_i2c_read(unsigned char slave_addr,
                   unsigned char reg_addr,
                   unsigned char length,
                   unsigned char *data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(ESP_OK != i2c_master_start(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write_byte(cmd, slave_addr << 1 | WRITE_BIT, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_stop(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    if(ESP_OK != i2c_master_start(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_write_byte(cmd, slave_addr << 1 | READ_BIT, ACK_CHECK_EN)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(length > 1) {
        if(ESP_OK != i2c_master_read(cmd, data, length - 1, ACK_VAL)) {
            i2c_cmd_link_delete(cmd);
            return -1;
        }
    }
    if(ESP_OK != i2c_master_read_byte(cmd, data + length - 1, NACK_VAL)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_stop(cmd)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    if(ESP_OK != i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS)) {
        i2c_cmd_link_delete(cmd);
        return -1;
    }
    i2c_cmd_link_delete(cmd);
    return 0;
}
