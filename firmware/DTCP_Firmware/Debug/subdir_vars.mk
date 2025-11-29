################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../main.syscfg 

C_SRCS += \
../ads1299.c \
../main.c \
./ti_msp_dl_config.c \
C:/ti/mspm0_sdk_2_07_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0c110x_ticlang.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./ads1299.d \
./main.d \
./ti_msp_dl_config.d \
./startup_mspm0c110x_ticlang.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./ads1299.o \
./main.o \
./ti_msp_dl_config.o \
./startup_mspm0c110x_ticlang.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h \
./Event.dot 

OBJS__QUOTED += \
"ads1299.o" \
"main.o" \
"ti_msp_dl_config.o" \
"startup_mspm0c110x_ticlang.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" \
"Event.dot" 

C_DEPS__QUOTED += \
"ads1299.d" \
"main.d" \
"ti_msp_dl_config.d" \
"startup_mspm0c110x_ticlang.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../ads1299.c" \
"../main.c" \
"./ti_msp_dl_config.c" \
"C:/ti/mspm0_sdk_2_07_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0c110x_ticlang.c" 

SYSCFG_SRCS__QUOTED += \
"../main.syscfg" 


