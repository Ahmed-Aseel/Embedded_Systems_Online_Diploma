/*
 * STM32F103C6_USART_driver.c
 *
 *  Created on: Feb 12, 2023
 *      Author: Ahmed Aseel
 */

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103C6_USART_driver.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
// 3 pointers one for each USART configuration
USART_Config_t* Global_USART_Config[3]  = {NULL, NULL, NULL} ;

USART_Config_t* p_USARTCfg;

/*
* ===============================================
* APIs Functions Definitions
* ===============================================
*/

/*=======================================================
* @Fn			: MCAL_USART_Init
* @brief		: Initialize USART from specific GPIO Pin, specify the baud rate, data size,
* 				  parity, stop bits & IRQ CallBack func  (Supported feature Asynch Only)
* @param [in]	: USARTx where x can be (1..3 depending on device used)
* @param [in]	: USARTConfig Set by @ref USART_Mode_define, @ref BaudRate_define & @ref Payload_Length_define
*                 @ref Parity_define, @ref StopBits_define, @ref FlowControl_define, @ref IRQ_Enable_define
* @retval		: None
* Note			: Support for Now Asynch mode & Clock 8 MHZ S
*/
void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t *USARTConfig)
{
	uint32_t pclk, BRR;
	if(USARTx == USART1)
	{
		Global_USART_Config[0] = USARTConfig;
		RCC_USART1_CLK_EN();
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else if(USARTx == USART2)
	{
		Global_USART_Config[1] = USARTConfig;
		RCC_USART2_CLK_EN();
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
	else if(USARTx == USART3)
	{
		Global_USART_Config[2] = USARTConfig;
		RCC_USART3_CLK_EN();
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	//Enable USART Module
	//USART_CR1	Bit 13 UE: USART enable
	USARTx->CR1 |= 1 << 13;

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= USARTConfig->USART_Mode;

	//PAYLOAD Width
	//USARTx->CR1  Bit 12 M: Word length
	USARTx->CR1 |= USARTConfig->Payload_Length;

	//Configuration of parity control bit fields
	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR1 |= USARTConfig->Parity;

	//Configure the number of stop bits
	//USART_CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= USARTConfig->StopBits;

	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= USARTConfig->FlowControl;

	//Configuration of BRR(Baud rate register)
	BRR = USART_BRR_REG(pclk, USARTConfig->BaudRate);
	USARTx->BRR |= BRR;

	//ENABLE / DISABLE Interrupt
	//USART_CR1
	if(USARTConfig->IRQ_Enable != IRQ_Enable_NONE)
	{
		USARTx->CR1 |= USARTConfig->IRQ_Enable;

		//Enable NVIC For USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable();

		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable();

		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable();
	}
}

/*================================================================
* @Fn			: MCAL_USART_DeInit
* @brief 		: Reset USART registers and NVIC Corresponding IRQ Mask
* @param [in] 	: USARTx: where x can be (1..3 depending on device used)
* @retval 		: None
* Note			: Reset the Model By RCC
*/
void MCAL_USART_DeInit(USART_TypeDef *USARTx )
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable();
		Global_USART_Config[0] = NULL;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable();
		Global_USART_Config[1] = NULL;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable();
		Global_USART_Config[2] = NULL;
	}
}

/*================================================================
* @Fn			: MCAL_UART_GPIO_Set_Pins
* @brief 		: Initialize GPIO Pins
* @param [in] 	: USARTx: where x can be (1..3 depending on device used)
* @retval 		: none
* Note			: Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_UART_Init()
*/
void MCAL_USART_GPIO_Set_Pins(USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t PinCfg;

	if(USARTx == USART1)
	{
		p_USARTCfg = Global_USART_Config[0];

		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX: Alternative fun out push-pull
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 RX: Input floating
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(p_USARTCfg->FlowControl == FlowControl_CTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PA11 CTS: Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(p_USARTCfg->FlowControl == FlowControl_RTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PA12 RTS: Alternative fun out push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(USARTx == USART2)
	{
		p_USARTCfg = Global_USART_Config[1];

		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX: Alternative fun out push-pull
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 RX: Input floating
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(p_USARTCfg->FlowControl == FlowControl_CTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PA0 CTS: Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		if(p_USARTCfg->FlowControl == FlowControl_RTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PA1 RTS: Alternative fun out push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(USARTx == USART3)
	{
		p_USARTCfg = Global_USART_Config[2];

		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX: Alternative fun out push-pull
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 RX: Input floating
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if(p_USARTCfg->FlowControl == FlowControl_CTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PB13 CTS: Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		if(p_USARTCfg->FlowControl == FlowControl_RTS || p_USARTCfg->FlowControl == FlowControl_CTS_RTS)
		{
			//PB14 RTS: Alternative fun out push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}

/*================================================================
* @fn      		: MCAL_USART_SendData
* @brief        : Send Buffer on USART
* @param [in] 	: USARTx: where x can be (1..3 depending on device used)
* @param[in]    : pTxbuffer Buffer
* @param[in]    : pollingstate Enable polling or disable it
* @return       : None
* @Note         : Should initialize USART First
* 				  When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
*				  the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
*				  because it is replaced by the parity.
*				  When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
*/
void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t *pTxbuffer, enum pollingmechanism pollingstate)
{
	//wait until TXE in the SR flag is set if the polling is enabled
	if(pollingstate == enable)
		while(!(USARTx->SR & (1 << 7)));

	if(USARTx == USART1)
	{
		p_USARTCfg = Global_USART_Config[0];
	}
	else if(USARTx == USART2)
	{
		p_USARTCfg = Global_USART_Config[1];
	}
	else if(USARTx == USART3)
	{
		p_USARTCfg = Global_USART_Config[2];
	}

	//Check the USART_WordLength item is 9BIT or 8BIT in a frame
	if(p_USARTCfg->Payload_Length == Payload_Length_9B)
	{
		//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
		USARTx->DR = (*pTxbuffer) & 0x1FF;
	}
	else
	{
		//This is 8bit data transfer
		USARTx->DR = (*pTxbuffer) & 0xFF;
	}
}

void MCAL_USART_ReceiveData(USART_TypeDef *USARTx, uint16_t *pRxbuffer, enum pollingmechanism pollingstate)
{
	//wait until RXNE in the SR flag is set if the polling is enabled
	if(pollingstate == enable)
		while(!(USARTx->SR & (1 << 5)));

	if(USARTx == USART1)
	{
		p_USARTCfg = Global_USART_Config[0];
	}
	else if(USARTx == USART2)
	{
		p_USARTCfg = Global_USART_Config[1];
	}
	else if(USARTx == USART3)
	{
		p_USARTCfg = Global_USART_Config[2];
	}

	//Check the USART_WordLength item is 9BIT or 8BIT in a frame
	if(p_USARTCfg->Payload_Length == Payload_Length_9B)
	{
		if(p_USARTCfg->Parity == USART_Parity_NONE)
		{
			*pRxbuffer = USARTx->DR & 0x1FF;
		}
		else
		{
			*pRxbuffer = USARTx->DR & 0xFF;
		}
	}
	else
	{
		if(p_USARTCfg->Parity == USART_Parity_NONE)
		{
			*pRxbuffer = USARTx->DR & 0xFF;
		}
		else
		{
			*pRxbuffer = USARTx->DR & 0x7F;
		}
	}
}

void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx)
{
	//Loop till TC flag in RC is set
	while( !(USARTx->SR & (1 << 6)) );
}

/*
* ===================================
*                ISR
* ===================================
*/
void USART1_IRQHandler(void)
{
	Global_USART_Config[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Global_USART_Config[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_USART_Config[2]->P_IRQ_CallBack();
}
