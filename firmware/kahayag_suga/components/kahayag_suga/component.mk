#
# Component Makefile
#

COMPONENT_DEPENDS := qpc

COMPONENT_ADD_INCLUDEDIRS += .

# System Management
COMPONENT_ADD_INCLUDEDIRS += components/SystemManagement
COMPONENT_SRCDIRS += components/SystemManagement

# Input Output
COMPONENT_ADD_INCLUDEDIRS += components/InputOutput
COMPONENT_SRCDIRS += components/InputOutput

