#ifndef _ESP32_HAL_I2C_H_
#define _ESP32_HAL_I2C_H_

int esp32_i2c_init(void);

int esp32_i2c_write(unsigned char slave_addr,
                    unsigned char reg_addr,
                    unsigned char length,
                    unsigned char *data);

int esp32_i2c_read(unsigned char slave_addr,
                   unsigned char reg_addr,
                   unsigned char length,
                   unsigned char *data);

#endif /* _ESP32_HAL_I2C_H_ */
