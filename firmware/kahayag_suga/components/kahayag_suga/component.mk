#
# Component Makefile
#

COMPONENT_DEPENDS := qpc

COMPONENT_ADD_INCLUDEDIRS += .

# System Management
COMPONENT_ADD_INCLUDEDIRS += components/SystemManagement
COMPONENT_SRCDIRS += components/SystemManagement

# Wifi
COMPONENT_ADD_INCLUDEDIRS += components/SystemManagement/Wifi
COMPONENT_SRCDIRS += components/SystemManagement/Wifi

# Provision
COMPONENT_ADD_INCLUDEDIRS += components/SystemManagement/Provision
COMPONENT_SRCDIRS += components/SystemManagement/Provision

# Input Output
COMPONENT_ADD_INCLUDEDIRS += components/InputOutput
COMPONENT_SRCDIRS += components/InputOutput

