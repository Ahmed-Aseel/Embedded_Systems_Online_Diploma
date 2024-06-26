/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_driver.h"
#include "STM32F103C6_EXTI_driver.h"

#define OS_SWITCH_ACCESS_TO_UNPRIVILEGED() __asm volatile ("MRS R0,CONTROL \n\t"\
											  	  	  	   "ORR R0,R0,#0x01 \n\t"\
														   "MSR CONTROL,R0")

#define OS_SWITCH_ACCESS_TO_PRIVILEGED() __asm volatile ("MRS R0,CONTROL \n\t"\
											  	  	  	 "LSR R0,R0,#0x01 \n\t"\
											  	  	  	 "LSL R0,R0,#0x01 \n\t"\
														 "MSR CONTROL,R0")

#define OS_SWITCH_SP_TO_MSP() __asm volatile ("MRS R0,CONTROL \n\t"\
											  "AND R0,R0,#0x05 \n\t"\
											  "MSR CONTROL,R0")

#define OS_SWITCH_SP_TO_PSP() __asm volatile ("MRS R0,CONTROL \n\t"\
											  "ORR R0,R0,#0x02 \n\t"\
											  "MSR CONTROL,R0")

#define OS_SET_PSP(add) __asm volatile ("MOV R0,%0 \n\t MSR PSP,R0" : : "r" (add))

#define OS_GENERATE_EXCEPTION()  __asm volatile ("SVC 0x03")

#define MAIN_STACK_SIZE     512 // 512 Bytes
#define TASKA_STACK_SIZE    100 // 100 Bytes
#define TASKB_STACK_SIZE    100 // 100 Bytes

extern uint32_t _estack;

// Main Stack
uint32_t _S_MSP = (uint32_t)&_estack;
uint32_t _E_MSP;

// Process Stack TaskA
uint32_t _S_PSP_TA;
uint32_t _E_PSP_TA;

// Process Stack TaskB
uint32_t _S_PSP_TB;
uint32_t _E_PSP_TB;

uint8_t TaskA_flag = 0, TaskB_flag = 0, IRQ_flag = 0;

void Clock_Init(void)
{
	// IO port B clock enable
	RCC_GPIOB_CLK_EN();
	// AFIO clock enable
	RCC_AFIO_CLK_EN();
}

void EXTI9_CallBack(void)
{
	if(IRQ_flag == 0)
	{
		TaskA_flag = 1;
		IRQ_flag = 1;
	}
	else if(IRQ_flag == 1)
	{
		TaskB_flag = 1;
		IRQ_flag = 0;
	}
}

void SVC_Handler()
{
	OS_SWITCH_ACCESS_TO_PRIVILEGED();
}

uint32_t TaskA(uint32_t a, uint32_t b, uint32_t c)
{
	return a+b+c;
}

uint32_t TaskB(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	return a+b+c+d;
}

void MainOS()
{
	// MAin Stack
	_E_MSP = _S_MSP - MAIN_STACK_SIZE;

	// TaskA Stack
	_S_PSP_TA = _E_MSP - 8;
	_E_PSP_TA = _S_PSP_TA - TASKA_STACK_SIZE;

	// TaskB Stack
	_S_PSP_TB = _E_PSP_TA - 8;
	_E_PSP_TB = _S_PSP_TB - TASKB_STACK_SIZE;

	while(1)
	{
		if(TaskA_flag == 1)
		{
			// Set PSP reg to _S_PSP_TA
			OS_SET_PSP(_S_PSP_TA);
			// Set SP to PSP
			OS_SWITCH_SP_TO_PSP();
			// Switch from privileged to unprivileged access level
			OS_SWITCH_ACCESS_TO_UNPRIVILEGED();

			TaskA_flag = TaskA(1, 2, 3);

			// Switch from unprivileged to privileged access level
			OS_GENERATE_EXCEPTION();
			// Set SP to MSP
			OS_SWITCH_SP_TO_MSP();
		}
		else if(TaskB_flag == 1)
		{
			// Set PSP reg to _S_PSP_TB
			OS_SET_PSP(_S_PSP_TB);
			// Set SP to PSP
			OS_SWITCH_SP_TO_PSP();
			// Switch from privileged to unprivileged access level
			OS_SWITCH_ACCESS_TO_UNPRIVILEGED();

			TaskB_flag = TaskB(1, 2, 3, 4);

			// Switch from unprivileged to privileged access level
			OS_GENERATE_EXCEPTION();
			// Set SP to MSP
			OS_SWITCH_SP_TO_MSP();
		}
	}
}

int main(void)
{
	Clock_Init();

	EXTI_PinConfig_t EXTI_Config;
	// EXTI9 PortB Pin9, Falling edge trigger
	EXTI_Config.EXTI_Pin = EXTI9PB9;
	EXTI_Config.Trigger_Case = EXTI_TRIGGER_RISING;
	EXTI_Config.P_IRQ_CallBack = EXTI9_CallBack;
	EXTI_Config.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_GPIO_Init(&EXTI_Config);

	MainOS();

	return 0;
}

