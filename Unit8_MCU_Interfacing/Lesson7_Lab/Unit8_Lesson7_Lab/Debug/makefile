################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103C6_Drivers/RCC_Driver/subdir.mk
-include STM32F103C6_Drivers/I2C_Driver/subdir.mk
-include STM32F103C6_Drivers/GPIO_Driver/subdir.mk
-include HAL/EEPROM/subdir.mk
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
Unit8_Lesson7_Lab.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Unit8_Lesson7_Lab.list \

OBJCOPY_BIN += \
Unit8_Lesson7_Lab.bin \


# All Target
all: Unit8_Lesson7_Lab.elf secondary-outputs

# Tool invocations
Unit8_Lesson7_Lab.elf: $(OBJS) $(USER_OBJS) C:\Users\Aseel\STM32CubeIDE\workspace_1.4.0\Unit8_Lesson7_Lab\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Unit8_Lesson7_Lab.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Aseel\STM32CubeIDE\workspace_1.4.0\Unit8_Lesson7_Lab\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Unit8_Lesson7_Lab.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Unit8_Lesson7_Lab.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Unit8_Lesson7_Lab.list"
	@echo 'Finished building: $@'
	@echo ' '

Unit8_Lesson7_Lab.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Unit8_Lesson7_Lab.bin"
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
