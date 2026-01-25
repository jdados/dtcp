################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"C:/Users/jdado/workspace_ccstheia/dtcp" -I"C:/Users/jdado/workspace_ccstheia/dtcp/Debug" -I"C:/ti/mspm0_sdk_2_06_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_06_00_05/source" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1547336655: ../gpio_toggle_output.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2030/ccs/utils/sysconfig_1.25.0/sysconfig_cli.bat" --script "C:/Users/jdado/workspace_ccstheia/dtcp/gpio_toggle_output.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_06_00_05/.metadata/product.json" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.lds: build-1547336655 ../gpio_toggle_output.syscfg
device.opt: build-1547336655
device.lds.genlibs: build-1547336655
ti_msp_dl_config.c: build-1547336655
ti_msp_dl_config.h: build-1547336655
Event.dot: build-1547336655

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"C:/Users/jdado/workspace_ccstheia/dtcp" -I"C:/Users/jdado/workspace_ccstheia/dtcp/Debug" -I"C:/ti/mspm0_sdk_2_06_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_06_00_05/source" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0c110x_gcc.o: C:/ti/mspm0_sdk_2_06_00_05/source/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0c110x_gcc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1.exe" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"C:/Users/jdado/workspace_ccstheia/dtcp" -I"C:/Users/jdado/workspace_ccstheia/dtcp/Debug" -I"C:/ti/mspm0_sdk_2_06_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_06_00_05/source" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"C:/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


