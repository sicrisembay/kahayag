#
# Component Makefile
#

COMPONENT_DEPENDS := freertos
COMPONENT_DEPENDS += qpc

COMPONENT_OBJS := bdcMotor.o
COMPONENT_OBJS += motor_driver/motor_driver.o
COMPONENT_OBJS += encoder/encoder.o
COMPONENT_SRCDIRS := .
COMPONENT_SRCDIRS += motor_driver
COMPONENT_SRCDIRS += encoder

# Unit Test (Encoder)
COMPONENT_OBJS += encoder/test/test_encoder.o
COMPONENT_SRCDIRS += encoder/test
# Unit Test (Motor Driver)
COMPONENT_OBJS += motor_driver/test/test_motor_driver.o
COMPONENT_SRCDIRS += motor_driver/test
