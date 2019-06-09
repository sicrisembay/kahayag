#
# Component Makefile
#

COMPONENT_DEPENDS := freertos qpc

COMPONENT_OBJS := bdcMotor.o encoder/encoder.o motor_driver/motor_driver.o
COMPONENT_SRCDIRS := . encoder motor_driver

