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

//#define MCU_ACT_AS_MASTER
#define MCU_ACT_AS_SLAVE

#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_driver.h"
#include "STM32F103C6_USART_driver.h"
#include "STM32F103C6_SPI_driver.h"

uint16_t data;

void SPI1_IRQ_Callback(struct S_IRQ_SRC irq_scr)
{
	#ifdef MCU_ACT_AS_SLAVE
		if(irq_scr.RXNE)
		{
			data = 0xF;
			MCAL_SPI_TX_RX(SPI1, &data, polling_disable);
			MCAL_USART_SendData(USART1, &data, enable);
		}
	#endif
}

void USART_IRQ_Callback(void)
{
	#ifdef MCU_ACT_AS_MASTER
		MCAL_USART_ReceiveData(USART1, &data, disable);
		MCAL_USART_SendData(USART1, &data, enable);

		//Send to SPI
		//Activate slave select
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		MCAL_SPI_TX_RX(SPI1, &data, polling_enable);
		//Deactivate slave select
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	#endif
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
	USART_Config_t usartcfg;
	SPI_Config_t spicfg;
	GPIO_PinConfig_t pincfg;

	Clock_Init();

	//============= USART INIT ==================
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

	//============= SPI1 INIT ==================
	//Common Configurations
	spicfg.CLK_Phase = SPI_CLK_Phase_SecondEdge_Capturedata;
	spicfg.CLK_Polarity = SPI_CLK_Polarity_Idle_High;
	spicfg.Data_Size = SPI_Data_Size_8B;
	spicfg.Frame_Formate = SPI_Frame_Formate_MSB_FIRST;
	//Assume by default pclk2 = 8MHZ
	spicfg.BaudRate_Control = SPI_BaudRate_PreScaler_8;
	spicfg.Communication_Mode = SPI_Direction_2Lines;

	#ifdef MCU_ACT_AS_MASTER
		spicfg.Device_Mode = SPI_Device_Mode_MASTER;
		spicfg.IRQ_Enable = SPI_IRQ_Enable_NONE;
		spicfg.NSS = SPI_NSS_Soft_NSSInternalSoft_Set;
		spicfg.P_IRQ_CallBack = NULL;

		MCAL_SPI_Init(SPI1, &spicfg);
		MCAL_SPI_GPIO_Set_Pins(SPI1);

		//Configure SS on PA.4 by GPIO
		pincfg.GPIO_PinNumber = GPIO_PIN_4;
		pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		pincfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		//Force Slave Select HIGH (Idle Mode)
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	#endif

	#ifdef MCU_ACT_AS_SLAVE
		spicfg.Device_Mode = SPI_Device_Mode_SLAVE;
		spicfg.IRQ_Enable = SPI_IRQ_Enable_RXNE;
		spicfg.NSS = SPI_NSS_Hard_Slave;
		spicfg.P_IRQ_CallBack = SPI1_IRQ_Callback;

		MCAL_SPI_Init(SPI1, &spicfg);
		MCAL_SPI_GPIO_Set_Pins(SPI1);
	#endif

	while(1);
	return 0;
}