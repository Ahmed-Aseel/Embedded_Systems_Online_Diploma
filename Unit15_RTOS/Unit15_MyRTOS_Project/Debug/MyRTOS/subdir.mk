################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyRTOS/CortexMx_OS_Porting.c \
../MyRTOS/MyRTOS_FIFO.c \
../MyRTOS/Scheduler.c 

OBJS += \
./MyRTOS/CortexMx_OS_Porting.o \
./MyRTOS/MyRTOS_FIFO.o \
./MyRTOS/Scheduler.o 

C_DEPS += \
./MyRTOS/CortexMx_OS_Porting.d \
./MyRTOS/MyRTOS_FIFO.d \
./MyRTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MyRTOS/CortexMx_OS_Porting.o: ../MyRTOS/CortexMx_OS_Porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/GPIO_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/EXTI_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/MyRTOS/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MyRTOS/CortexMx_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MyRTOS/MyRTOS_FIFO.o: ../MyRTOS/MyRTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/GPIO_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/EXTI_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/MyRTOS/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MyRTOS/MyRTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MyRTOS/Scheduler.o: ../MyRTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/GPIO_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/STM32F103C6_Drivers/EXTI_Driver" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/MyRTOS/Inc" -I"C:/Users/Aseel/STM32CubeIDE/workspace_1.4.0/Unit15_MyRTOS_Project/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MyRTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

