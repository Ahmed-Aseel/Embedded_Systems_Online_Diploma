################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103C6_Drivers/GPIO_Driver/subdir.mk
-include STM32F103C6_Drivers/EXTI_Driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Unit14_Lesson5_Lab.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Unit14_Lesson5_Lab.list \

OBJCOPY_BIN += \
Unit14_Lesson5_Lab.bin \


# All Target
all: Unit14_Lesson5_Lab.axf secondary-outputs

# Tool invocations
Unit14_Lesson5_Lab.axf: $(OBJS) $(USER_OBJS) C:\Users\Aseel\STM32CubeIDE\workspace_1.4.0\Unit14_Lesson5_Lab\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Unit14_Lesson5_Lab.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Aseel\STM32CubeIDE\workspace_1.4.0\Unit14_Lesson5_Lab\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Unit14_Lesson5_Lab.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Unit14_Lesson5_Lab.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Unit14_Lesson5_Lab.list"
	@echo 'Finished building: $@'
	@echo ' '

Unit14_Lesson5_Lab.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Unit14_Lesson5_Lab.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
