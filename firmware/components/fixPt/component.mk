#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS += libfixmath/libfixmath

COMPONENT_OBJS := libfixmath/libfixmath/fix16.o
COMPONENT_SRCDIRS := libfixmath/libfixmath

CFLAGS += -DFIXMATH_NO_ROUNDING -DFIXMATH_NO_OVERFLOW -DFIXMATH_NO_64BIT
