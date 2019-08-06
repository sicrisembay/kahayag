#
# Component Makefile
#

CFLAGS += -DMOTION_DRIVER_TARGET_ESP32 -DMPU9250

COMPONENT_DEPENDS := freertos
# COMPONENT_DEPENDS += qpc

COMPONENT_OBJS := eMD.o
COMPONENT_OBJS += eMD6.12/core/driver/esp32/hal_i2c.o
COMPONENT_OBJS += eMD6.12/core/driver/eMPL/inv_mpu.o
COMPONENT_OBJS += madgwick_filter/madgwick_filter.o
COMPONENT_SRCDIRS := .
COMPONENT_SRCDIRS += eMD6.12/core/driver/esp32
COMPONENT_SRCDIRS += eMD6.12/core/driver/eMPL
COMPONENT_SRCDIRS += madgwick_filter


COMPONENT_PRIV_INCLUDEDIRS := eMD6.12/core/driver/eMPL
COMPONENT_PRIV_INCLUDEDIRS += eMD6.12/core/driver/esp32
COMPONENT_PRIV_INCLUDEDIRS += madgwick_filter
