################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EEPROM/I2C_Slave_EEPROM.c 

OBJS += \
./HAL/EEPROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./HAL/EEPROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EEPROM/I2C_Slave_EEPROM.o: ../HAL/EEPROM/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit8_Lesson7_Lab/STM32F103C6_Drivers/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit8_Lesson7_Lab/STM32F103C6_Drivers/RCC_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit8_Lesson7_Lab/STM32F103C6_Drivers/GPIO_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit8_Lesson7_Lab/STM32F103C6_Drivers/I2C_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit8_Lesson7_Lab/HAL/EEPROM" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/EEPROM/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

