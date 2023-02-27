/*
 * STM32F103C6_SPI_driver.c
 *
 *  Created on: Feb 17, 2023
 *      Author: Ahmed Aseel
 */

#include "STM32F103C6_SPI_driver.h"
#include "STM32F103C6_GPIO_driver.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
// 3 pointers one for each SPI configuration
SPI_Config_t* Global_SPI_Config[2]  = {NULL, NULL} ;

/*
* ===============================================
* APIs Functions Definitions
* ===============================================
*/

/*=======================================================
* @Fn			: MCAL_SPI_Init
* @brief		: Initialize the SPIx according to the specified parameters in SPIConfig
* @param[in]	: SPIx where x can be (1..3 depending on device used)
* @param[in]	: SPI_Config_t Pointer to a SPI_Config_t structure that contains the configuration
* 							 info for specified SPI pin
* @retval		: None
* Note			: Support full Duplex Master/Slave only & NSS HW only for slave
* 				  in case of Master you have to configure the pin and drive it
*/
void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t *SPIConfig)
{
	//Safety for registers
	uint16_t temp_CR1 = 0;
	uint16_t temp_CR2 = 0;

	if(SPIx == SPI1)
	{
		Global_SPI_Config[0] = SPIConfig;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[1] = SPIConfig;
		RCC_SPI2_CLK_EN();
	}

	//Enable SPI CR1 Bit 6 SPE: SPI enable
	temp_CR1 |= (1<<6);
	temp_CR1 |= SPIConfig->Device_Mode;	//Master or Slave
	temp_CR1 |= SPIConfig->Communication_Mode;	//Direction
	temp_CR1 |= SPIConfig->Frame_Formate;	//LSB or MSB
	temp_CR1 |= SPIConfig->Data_Size;
	temp_CR1 |= SPIConfig->CLK_Polarity;
	temp_CR1 |= SPIConfig->CLK_Phase;

	//NSS
	if(SPIConfig->NSS == SPI_NSS_Hard_MASTER_SS_Output_Disable)
	{
		temp_CR2 &= SPIConfig->NSS;
	}
	else if(SPIConfig->NSS == SPI_NSS_Hard_MASTER_SS_Output_Enable)
	{
		temp_CR2 |= SPIConfig->NSS;
	}
	else
	{
		temp_CR1 |= SPIConfig->NSS;
	}

	temp_CR1 |= SPIConfig->BaudRate_Control;  //Baud rate prescaler

	if(SPIConfig->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		temp_CR2 |= SPIConfig->IRQ_Enable;
		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable();
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable();
		}
	}

	SPIx->CR1 = temp_CR1;
	SPIx->CR2 = temp_CR2;
}

/*================================================================
* @Fn			: MCAL_SPI_DeInit
* @brief 		: Reset SPI registers and NVIC Corresponding IRQ Mask
* @param[in] 	: SPIx where x can be (1..3 depending on device used)
* @retval 		: None
* Note			: Reset the Model By RCC
*/
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx )
{
	if(SPIx == SPI1)
	{
		RCC_SPI1_RESET();
		NVIC_IRQ35_SPI1_Disable();
	}
	else if(SPIx == SPI2)
	{
		RCC_SPI2_RESET();
		NVIC_IRQ36_SPI2_Disable();
	}
}

/*================================================================
* @Fn			: MCAL_SPI_GPIO_Set_Pins
* @brief 		: Initialize GPIO Pins
* @param[in] 	: SPIx where x can be (1..3 depending on device used)
* @retval 		: none
* Note			: Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_SPI_Init()
*/
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	SPI_Config_t* p_SPICfg = NULL;
	GPIO_PinConfig_t PinCfg;

	if(SPIx == SPI1)
	{
		p_SPICfg = Global_SPI_Config[0];
		//PA4 NSS
		//PA5 SCK
		//PA6 MISO
		//PA7 MOSI

		if(p_SPICfg->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PA4 NSS
			if(p_SPICfg->NSS == SPI_NSS_Hard_MASTER_SS_Output_Disable)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			else if(p_SPICfg->NSS == SPI_NSS_Hard_MASTER_SS_Output_Enable)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA5 SCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6 MISO (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7 MOSI (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		else if(p_SPICfg->Device_Mode == SPI_Device_Mode_SLAVE)
		{
			//PA4 NSS
			if(p_SPICfg->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA5 SCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6 MISO (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7 MOSI (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if(SPIx == SPI2)
	{
		p_SPICfg = Global_SPI_Config[1];
		//PB12 NSS
		//PB13 SCK
		//PB14 MISO
		//PB15 MOSI

		if(p_SPICfg->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PB12 NSS
			if(p_SPICfg->NSS == SPI_NSS_Hard_MASTER_SS_Output_Disable)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			else if(p_SPICfg->NSS == SPI_NSS_Hard_MASTER_SS_Output_Enable)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			//PB13 SCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14 MISO (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15 MOSI (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

		else if(p_SPICfg->Device_Mode == SPI_Device_Mode_SLAVE)
		{
			//PB12 NSS
			if(p_SPICfg->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			//PB13 SCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14 MISO (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed =  GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15 MOSI (supported only full duplex)
			//TODO support half duplex & simplex
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}

/*================================================================
* @fn      		: MCAL_SPI_SendData
* @brief        : Send Buffer on SPI
* @param[in] 	: SPIx where x can be (1..3 depending on device used)
* @param[in]    : pTxbuffer Buffer
* @param[in]    : pollingstate Enable polling or disable it
* @return       : None
* @Note         : Should initialize SPI First
*/
void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxbuffer, enum polling_mechanism pollingstate)
{
// TODO receive only
	//wait until TXE in the SR flag is set if the polling is enabled
	if(pollingstate == polling_enable)
		while(!(SPIx->SR & (1 << 1)));

	SPIx->DR = *pTxbuffer;
}

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxbuffer, enum polling_mechanism pollingstate)
{
// TODO transmit only
	//wait until RXNE in the SR flag is set if the polling is enabled
	if(pollingstate == polling_enable)
		while(!(SPIx->SR & (1 << 0)));

	*pRxbuffer = SPIx->DR;
}

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pBuffer, enum polling_mechanism pollingstate)
{
	//check if the polling is enabled
	if(pollingstate == polling_enable)
		while(!(SPIx->SR & (1 << 1))); 	//wait until TXE in the SR flag is set

	SPIx->DR = *pBuffer;

	//check if the polling is enabled
	if(pollingstate == polling_enable)
		while(!(SPIx->SR & (1 << 0)));  //wait until RXNE in the SR flag is set

	*pBuffer = SPIx->DR;
}

/*
* ===================================
*                ISR
* ===================================
*/
void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI1->SR >> 1) & 1);
	irq_src.RXNE = (SPI1->SR & 1);
	irq_src.ERRI = ((SPI1->SR >> 4) & 1);

	Global_SPI_Config[0]->P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI2->SR >> 1) & 1);
	irq_src.RXNE = (SPI2->SR & 1);
	irq_src.ERRI = ((SPI2->SR >> 4) & 1);

	Global_SPI_Config[1]->P_IRQ_CallBack(irq_src);
}
