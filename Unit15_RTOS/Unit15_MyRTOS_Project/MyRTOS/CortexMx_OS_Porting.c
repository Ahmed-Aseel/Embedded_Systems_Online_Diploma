/*
 * CortexMx_OS_Porting.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#include "CortexMx_OS_Porting.h"

void HardFault_Handler()
{
	while(1);
}

void MemManage_Handler()
{
	while(1);
}

void BusFault_Handler()
{
	while(1);
}

void UsageFault_Handler()
{
	while(1);
}

__attribute__ ((naked)) void SVC_Handler()
{
	__asm volatile ("TST LR,#0x04 \n\t"
					"ITE EQ \n\t"
					"MRSEQ R0,MSP \n\t"
					"MRSNE R0,PSP \n\t"
					"B OS_SVC");
}

void HW_Init()
{
	// Initialize Clock Tree (RCC -> SysTick Timer & CPU) 8MHz -> Default Values
	/* 8MHz
	 * 1 Count = 0.125us
	 * X counts = 1 ms -> X = 8000 counts
	 */

	/* Decrease PendSV interrupt priority to be smaller than SysTick timer
	 * SysTick timer has a priority 14
	 */
	__NVIC_SetPriority(PendSV_IRQn, 15);
}

void Trigger_OS_PendSV()
{
	// Set PendSv
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void Start_Ticker()
{
	/* This clock tree should be defined in HW_Init()
	 * 8MHz
	 * 1 Count = 0.125us
	 * X counts = 1 ms -> X = 8000 counts
	 */
	SysTick_Config(8000);
}
