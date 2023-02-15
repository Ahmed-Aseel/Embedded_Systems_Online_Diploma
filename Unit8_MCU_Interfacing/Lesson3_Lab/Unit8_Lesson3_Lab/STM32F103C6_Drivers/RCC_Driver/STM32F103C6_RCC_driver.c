/*
 * STM32F103C6_RCC_driver.c
 *
 *  Created on: Feb 12, 2023
 *      Author: Ahmed Aseel
 */

#include "STM32F103C6_RCC_driver.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

//Bits 7:4 HPRE: AHB prescaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
uint8_t AHBPresc_Table[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};

//PPRE1: APB low-speed prescaler (APB1).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
uint8_t APBPresc_Table[] = {0,0,0,0,1,2,3,4};

/*
* ===============================================
* APIs Functions Definitions
* ===============================================
*/

uint32_t MCAL_RCC_Getsys_CLKFreq(void)
{
//	Bits 3:2 SWS: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: not applicable
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLOCK;
		break;
	case 1:
		return HSE_CLOCK;
		break;
//TODO
//	case 2:
//		return PLL_clock;
//		break;
	}
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	return ((MCAL_RCC_Getsys_CLKFreq() >> AHBPresc_Table[(RCC->CFGR >> 4) & 0xF]));
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	return ((MCAL_RCC_GetHCLKFreq() >> APBPresc_Table[(RCC->CFGR >> 8) & 0b111]));
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	return ((MCAL_RCC_GetHCLKFreq() >> APBPresc_Table[(RCC->CFGR >> 11) & 0b111]));
}
