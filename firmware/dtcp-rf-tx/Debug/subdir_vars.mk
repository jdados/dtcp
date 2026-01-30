################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../gpio_toggle_output.syscfg 

C_SRCS += \
../gpio_toggle_output.c \
./ti_msp_dl_config.c \
C:/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0c110x_gcc.c 

GEN_CMDS += \
./device_linker.lds 

GEN_FILES += \
./device_linker.lds \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./gpio_toggle_output.d \
./ti_msp_dl_config.d \
./startup_mspm0c110x_gcc.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./gpio_toggle_output.o \
./ti_msp_dl_config.o \
./startup_mspm0c110x_gcc.o 

GEN_MISC_FILES += \
./device.lds.genlibs \
./ti_msp_dl_config.h \
./Event.dot 

OBJS__QUOTED += \
"gpio_toggle_output.o" \
"ti_msp_dl_config.o" \
"startup_mspm0c110x_gcc.o" 

GEN_MISC_FILES__QUOTED += \
"device.lds.genlibs" \
"ti_msp_dl_config.h" \
"Event.dot" 

C_DEPS__QUOTED += \
"gpio_toggle_output.d" \
"ti_msp_dl_config.d" \
"startup_mspm0c110x_gcc.d" 

GEN_FILES__QUOTED += \
"device_linker.lds" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../gpio_toggle_output.c" \
"./ti_msp_dl_config.c" \
"C:/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0c110x_gcc.c" 

SYSCFG_SRCS__QUOTED += \
"../gpio_toggle_output.syscfg" 


