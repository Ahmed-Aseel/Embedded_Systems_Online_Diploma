/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_driver.h"
#include "STM32F103C6_USART_driver.h"

uint16_t data;

void USART_IRQ_Callback(void)
{
	MCAL_USART_ReceiveData(USART1, &data, disable);
	MCAL_USART_SendData(USART1, &data, enable);
}

void Clock_Init(void)
{
	// IO port A clock enable
	RCC_GPIOA_CLK_EN();
	// IO port B clock enable
	RCC_GPIOB_CLK_EN();
	// AFIO clock enable
	RCC_AFIO_CLK_EN();
}


int main(void)
{
	Clock_Init();

	USART_Config_t usartcfg;
	usartcfg.USART_Mode = USART_Mode_TX_RX;
	usartcfg.Payload_Length = Payload_Length_8B;
	usartcfg.Parity = USART_Parity_NONE;
	usartcfg.StopBits = USART_StopBits_1;
	usartcfg.BaudRate = USART_BaudRate_115200;
	usartcfg.FlowControl = FlowControl_NONE;
	usartcfg.IRQ_Enable = IRQ_Enable_RXNE;
	usartcfg.P_IRQ_CallBack = USART_IRQ_Callback;

	MCAL_USART_Init(USART1, &usartcfg);
	MCAL_USART_GPIO_Set_Pins(USART1);

	while(1);
	return 0;
}
