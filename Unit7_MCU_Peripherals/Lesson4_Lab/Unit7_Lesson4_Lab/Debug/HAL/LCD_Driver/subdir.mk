################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD_Driver/LCD.c 

OBJS += \
./HAL/LCD_Driver/LCD.o 

C_DEPS += \
./HAL/LCD_Driver/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LCD_Driver/LCD.o: ../HAL/LCD_Driver/LCD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/metro/STM32CubeIDE/workspace_1.4.0/Unit7_Lesson4_Lab/STM32F103C6_Drivers/Inc" -I"C:/Users/metro/STM32CubeIDE/workspace_1.4.0/Unit7_Lesson4_Lab/STM32F103C6_Drivers/GPIO_Driver" -I"C:/Users/metro/STM32CubeIDE/workspace_1.4.0/Unit7_Lesson4_Lab/STM32F103C6_Drivers/EXTI_Driver" -I"C:/Users/metro/STM32CubeIDE/workspace_1.4.0/Unit7_Lesson4_Lab/HAL/LCD_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Driver/LCD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

