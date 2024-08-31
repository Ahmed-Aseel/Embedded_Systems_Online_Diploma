/*
 * STM32F103C6_I2C_driver.c
 *
 *  Created on: Mar 1, 2023
 *      Author: Ahmed Aseel
 */

#include <string.h>
#include "STM32F103C6_I2C_driver.h"
#include "STM32F103C6_RCC_driver.h"
#include "STM32F103C6_GPIO_driver.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
// 2 structures one for each I2C configuration
I2C_Config_t Global_I2C_Config[2] = {0};

/*
 * =======================================================================================
 * 							Generic APIs Declarations
 * =======================================================================================
 */
static void I2C_GenerateStart(I2C_TypeDef *I2Cx, FunctionalState NewState, Repeted_Start start);
static FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, Status flag);
static void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction direction);
static void I2C_GenerateStop(I2C_TypeDef *I2Cx, FunctionalState NewState);
static void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState);

/*
 * ===============================================
 * APIs Functions Definitions
 * ===============================================
 */

/*=======================================================
 * @Fn			: MCAL_I2C_Init
 * @brief		: Initialize the I2Cx according to the specified parameters in I2CConfig
 * @param[in]	: I2Cx where x can be (1..3 depending on device used)
 * @param[in]	: I2C_Config_t Pointer to a I2C_Config_t structure that contains the configuration
 * 							 info for specified I2C pin
 * @retval		: None
 * Note			:
 *
 */
void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Config_t *I2CConfig)
{
	uint16_t tempreg = 0, freqrange = 0, result = 0;
	uint32_t pclk1 = 8000000;

	if(I2Cx == I2C1)
	{
		Global_I2C_Config[0] = *I2CConfig;
		RCC_I2C1_CLK_EN();
	}
	else if(I2Cx == I2C2)
	{
		Global_I2C_Config[1] = *I2CConfig;
		RCC_I2C2_CLK_EN();
	}

	if(I2CConfig->Device_Mode == Device_Mode_I2C)
	{
		/*---------------- Init Timing ----------------*/
		// Program the peripheral input clock in I2C_CR2.FREQ[5:0]
		// Get I2C_CR2 value
		tempreg = I2Cx->CR2;
		// Clear FREQ[5:0] bits
		tempreg &= ~(0x3F << 0);
		// Get pclk1 frequency value
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		freqrange = (uint16_t)(pclk1 / 1000000);

		// Disable the selected I2C peripheral to configure time
		// Clear Bit 0 PE: Peripheral enable in CR1
		I2Cx->CR1 &= ~(1 << 0);

		// Set frequency bits depending on freqrange value
		tempreg |= freqrange;
		I2Cx->CR2 = tempreg;

		if(I2CConfig->Clock_Speed == I2C_SCLK_SM_50K || I2CConfig->Clock_Speed == I2C_SCLK_SM_100K)
		{
			// Standard mode speed calculation
			/* Tclk/2 = CCR * Tpclk1
			 * CCR = Tclk/(2*Tpclk1)
			 * CCR = Fpclk1/(2*I2C_ClockFreq)
			 */
			result = (uint16_t)(pclk1 / (I2CConfig->Clock_Speed << 1));
			tempreg = 0;
			tempreg |= result;

			// Bit 15 F/S: I2C master mode selection
			// 0: Sm mode I2C , 1: Fm mode I2C
			tempreg &= ~(1 << 15);

			// Configure the clock control registers I2C_CCR
			I2Cx->CCR = tempreg;

			// For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			// If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			// therefore the TRISE[5:0] bits must be programmed with 09h.
			I2Cx->TRISE = freqrange + 1;
		}
		else
		{
			// Fast mode not supported
		}

		/*---------------- I2C CR1 Configuration ----------------*/
		// Get I2C_CR1 value
		tempreg = I2Cx->CR1;
		tempreg |= (uint16_t)(I2CConfig->Ack_Control | I2CConfig->General_Call_Address_Detection |
				I2CConfig->Device_Mode | I2CConfig->Stretch_Mode);

		I2Cx->CR1 = tempreg;

		/*---------------- I2C OAR1,OAR2 Configuration ----------------*/
		tempreg = 0;
		tempreg |= I2CConfig->Slave_Address.I2C_Addressing_Slave_Mode;
		tempreg |= (I2CConfig->Slave_Address.Primary_Slave_Address << 1);
		I2Cx->OAR1 = tempreg;

		if(I2CConfig->Slave_Address.Dual_Address_Status == I2C_DUAL_ADDRESS_ENABLE)
		{
			tempreg = 0;
			// Bit 0 ENDUAL: Dual addressing mode enable
			tempreg |= (1 << 0);
			tempreg |= (I2CConfig->Slave_Address.Secondary_Slave_Address << 1);
			I2Cx->OAR2 = tempreg;
		}

		// Interrupt Mode (Slave Mode) -> Check callback function
		if(I2CConfig->p_Slave_Event_CallBack)
		{
			// Bit 8 ITERREN: Error interrupt enable
			// Bit 9 ITEVTEN: Event interrupt enable
			// Bit 10 ITBUFEN: Buffer interrupt enable
			I2Cx->CR2 |= (1 << 8) | (1 << 9) | (1 << 10);

			if(I2Cx == I2C1)
			{
				NVIC_IRQ31_I2C1_EV_Enable();
				NVIC_IRQ32_I2C1_ER_Enable();
			}
			else if(I2Cx == I2C2)
			{
				NVIC_IRQ33_I2C2_EV_Enable();
				NVIC_IRQ34_I2C2_ER_Enable();
			}
		}

		// Clear status registers
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;

		// Enable the selected I2C peripheral
		// Set Bit 0 PE: Peripheral enable in CR1
		I2Cx->CR1 |= (1 << 0);
	}
	else if(I2CConfig->Device_Mode == Device_Mode_SMBus)
	{
		//		SMBus not supported
	}
}

/*================================================================
 * @Fn			: MCAL_I2C_DeInit
 * @brief 		: Reset I2C registers and NVIC Corresponding IRQ Mask
 * @param[in] 	: I2Cx where x can be (1..3 depending on device used)
 * @retval 		: None
 * Note			: Reset the Model By RCC
 */
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx )
{
	if(I2Cx == I2C1)
	{
		RCC_I2C1_RESET();
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
		memset(&Global_I2C_Config[0], 0, sizeof(I2C_Config_t));
	}
	else if(I2Cx == I2C2)
	{
		RCC_I2C2_RESET();
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
		memset(&Global_I2C_Config[1], 0, sizeof(I2C_Config_t));
	}
}

/*=======================================================
 * * @Fn		: MCAL_I2C_GPIO_Set_Pins
 * @brief 		: Initialize GPIO Pins
 * @param[in] 	: I2Cx where x can be (1..3 depending on device used)
 * @retval 		: none
 * Note			: Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_I2C_Init()
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef *I2Cx)
{
	GPIO_PinConfig_t PinCfg;
	if(I2Cx == I2C1)
	{
		// PB6: I2C1 SCL Alternate function output Open-drain
		// PB7: I2C1 SDA Alternate function output Open-drain
		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
	else if(I2Cx == I2C2)
	{
		// PB10: I2C2 SCL Alternate function output Open-drain
		// PB11: I2C2 SDA Alternate function output Open-drain
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
}

/*=======================================================*/
void MCAL_I2CMaster_Transmite(I2C_TypeDef *I2Cx, uint16_t devAddr, uint8_t* data,
		uint8_t dataLen, Stop_Condition stop, Repeted_Start start)
{
	uint8_t i;

	// 1.Set start bit in CR1 to generate start condition
	I2C_GenerateStart(I2Cx, ENABLE, start);

	// 2.Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!(I2C_GetFlagStatus(I2Cx, EV5)));

	// 3.Send address with write mode
	I2C_SendAddress(I2Cx, devAddr, I2C_DIRECTION_WRITE);

	// 4.Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!(I2C_GetFlagStatus(I2Cx, EV6)));

	//5.TRA, BUSY, MSL, TXE flags
	while(!(I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING)));

	// 6.Send Data
	for(i = 0; i < dataLen; i++)
	{
		// 6.EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
		while(!(I2C_GetFlagStatus(I2Cx, EV8_1)));
		I2Cx->DR = data[i];
		// Wait EV8
		// EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!(I2C_GetFlagStatus(I2Cx, EV8)));
	}

	if(stop == WITH_STOP)
	{
		//7. Send stop condition
		I2C_GenerateStop(I2Cx , ENABLE);
	}
	else
	{
		I2C_GenerateStop(I2Cx, DISABLE);
	}
}

/*=======================================================*/
void MCAL_I2CMaster_Receive(I2C_TypeDef *I2Cx, uint16_t devAddr, uint8_t* data,
		uint8_t dataLen, Stop_Condition stop, Repeted_Start start)
{
	uint8_t i;
	uint8_t index = (I2Cx == I2C1 ? 0 : 1);

	// 1.Set start bit in CR1 to generate start condition
	I2C_GenerateStart(I2Cx, ENABLE, start);

	// 2.Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!(I2C_GetFlagStatus(I2Cx, EV5)));

	// 3.Send address with read mode
	I2C_SendAddress(I2Cx, devAddr, I2C_DIRECTION_READ);

	// 4.Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!(I2C_GetFlagStatus(I2Cx, EV6)));

	// Enable acking
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	if(dataLen)
	{
		// 5.Read data until length becomes zero
		for(i = 0; i < (dataLen-1); i++)
		{
			// Wait until RXNE becomes 1
			while(!(I2C_GetFlagStatus(I2Cx, EV7)));
			// Read data from data register into data buffer
			*(data+i) = I2Cx->DR;
		}

		// 6.Send not ack
		I2C_AcknowledgeConfig(I2Cx, DISABLE); // Not to receive
	}

	if(stop == WITH_STOP)
	{
		//7. Send stop condition
		I2C_GenerateStop(I2Cx , ENABLE);
	}
	else
	{
		I2C_GenerateStop(I2Cx, DISABLE);
	}

	// Re-enable acking
	if(Global_I2C_Config[index].Ack_Control == I2C_ACK_ENABLE)
	{
		I2C_AcknowledgeConfig(I2Cx, ENABLE);
	}
}

void MCAL_I2CSlave_Transmite(I2C_TypeDef *I2Cx, uint8_t data)
{
	I2Cx->DR = data;
}

uint8_t MCAL_I2CSlave_Receive(I2C_TypeDef *I2Cx)
{
	return ((uint8_t)(I2Cx->DR));
}

/*
 * =======================================================================================
 * 							Generic APIs Definitions
 * =======================================================================================
 */
static void I2C_GenerateStart(I2C_TypeDef *I2Cx, FunctionalState NewState, Repeted_Start start)
{
	if(start == START)
	{
		// Check if bus is idle
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}

	if(NewState == ENABLE)
	{
		// Generate start condition
		// CR1 Bit 8 START: Start generation
		// This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		// In Master Mode:
		// 0: No Start generation
		// 1: Repeated start generation
		// In Slave mode:
		// 0: No Start generation
		// 1: Start generation when the bus is free
		I2Cx->CR1 |= (1 << 8);
	}
	else
	{
		// Disable start condition generation
		I2Cx->CR1 &= ~(1 << 8);
	}
}

static FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, Status flag)
{
	volatile uint32_t dummyRead;
	FlagStatus bitStatus = RESET;
	uint32_t flag1 = 0, flag2 = 0;
	uint32_t lastEvent = 0;

	switch(flag)
	{
		case I2C_FLAG_BUSY:
			// SR2 Bit 1 BUSY: Bus busy
			// 0: No communication on the bus
			// 1: Communication ongoing on the bus
			// – Set by hardware on detection of SDA or SCL low
			// – cleared by hardware on detection of a Stop condition.
			// It indicates a communication in progress on the bus. This information is still updated when
			// the interface is disabled (PE=0)
			if((I2Cx->SR2 & (1<<1)))
			{
				bitStatus = SET;
			}
			break;

		case EV5:
			// SR1 Bit 0 SB: Start bit (Master mode)
			// 0: No Start condition
			// 1: Start condition generated.
			// – Set when a Start condition generated.
			// – Cleared by software by reading the SR1 register followed by writing the DR register, or by
			// hardware when PE=0
			if((I2Cx->SR1 & (1<<0)))
			{
				bitStatus = SET;
			}
			break;

		case EV6:
			// SR1 Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			// Address matched (Slave)
			// 0: Address mismatched or not received.
			// 1: Received address matched
			// Address sent (Master)
			// 0: No end of address transmission
			// 1: End of address transmission
			if((I2Cx->SR1 & (1<<1)))
			{
				bitStatus = SET;
			}
			// This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			// when PE=0.
			dummyRead = I2Cx->SR2;
			break;

		case EV7:
			// SR1 Bit 6 RxNE: Data register not empty (receivers)
			// 0: Data register empty
			// 1: Data register not empty
			// – Set when data register is not empty in receiver mode. RxNE is not set during address phase.
			// – Cleared by software reading or writing the DR register or by hardware when PE=0.
			// RxNE is not set in case of ARLO event.
			if((I2Cx->SR1 & (1<<6)))
			{
				bitStatus = SET;
			}
			break;

		case EV8:
		case EV8_1:
			// Bit 7 TxE: Data register empty (transmitters)
			// 0: Data register not empty
			// 1: Data register empty
			// – Set when DR is empty in transmission. TxE is not set during address phase.
			// – Cleared by software writing to the DR register or by hardware after a start or a stop condition
			// or when PE=0.
			if((I2Cx->SR1 & (1<<7)))
			{
				//Data register empty
				bitStatus = SET;
			}
			break;

		case MASTER_BYTE_TRANSMITTING:
			// Read I2Cx status registers
			flag1 = I2Cx->SR1;
			flag2 = I2Cx->SR2;
			flag2 <<= 16;

			// Get lastEvent value from I2C status register
			lastEvent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
			// Check whether the last event contains the I2C_EVENT
			if((lastEvent & flag) == flag)
			{
				// last event is equal to I2C_EVENT
				bitStatus = SET;
			}
			break;
	}

	return bitStatus;
}

static void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction direction)
{
	uint8_t index = (I2Cx == I2C1 ? 0:1);
	if(Global_I2C_Config[index].Slave_Address.I2C_Addressing_Slave_Mode == I2C_ADDRESSING_SLAVE_MODE_7BITS)
	{
		Address <<= 1;
		if(direction == I2C_DIRECTION_WRITE)
		{
			// Reset address bit0 for write
			Address &= ~(1<<0);
		}
		else
		{
			// Set address bit0 for read
			Address |= (1<<0);
		}

		// Send the address on SDA
		I2Cx->DR = Address;
	}
	else
	{
		// 10-BITS addressing not supported
	}
}

static void I2C_GenerateStop(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		// Generate stop condition
		// Bit 9 STOP: Stop generation
		// The bit is set and cleared by software, cleared by hardware when a Stop condition is
		// detected, set by hardware when a timeout error is detected.
		// In Master Mode:
		// 0: No Stop generation.
		// 1: Stop generation after the current byte transfer or after the current Start condition is sent
		I2Cx->CR1 |= (1 << 9);
	}
	else
	{
		// Disable stop condition generation
		I2Cx->CR1 &= ~(1 << 9);
	}
}

static void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		// Bit 10 ACK: Acknowledge enable
		// This bit is set and cleared by software and cleared by hardware when PE=0.
		// 0: No acknowledge returned
		// 1: Acknowledge returned after a byte is received (matched address or data)
		I2Cx->CR1 |= (1 << 10);
	}
	else
	{
		I2Cx->CR1 &= ~(1 << 10);
	}
}

/*
 * ===================================
 *                ISR
 * ===================================
 */
void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummyRead;
	I2C_TypeDef *I2Cx = I2C1;

	// Interrupt handling for both master and slave modes of a device
	uint32_t temp1, temp2, temp3;

	temp1 = I2Cx->CR2 & (1<<9);  // ITEVTEN
	temp2 = I2Cx->CR2 & (1<<10); // ITBUFEN
	temp3 = I2Cx->SR1 & (1<<4);  // STOPF

	// Handle stop condition event (applicable only in slave mode)
	if(temp1 && temp3)
	{
		// STOPF Cleared by software reading the SR1 register followed by a write in the CR1 register,
		// i have already read SR1 in temp3
		// then next statement i write to CR1
		I2C1->CR1 |= 0x0000;
		Global_I2C_Config[0].p_Slave_Event_CallBack(I2C_EV_STOP);
	}
	//----------------------------------------------------------
	// Handle received address matched.
	temp3 = I2C1->SR1 & (1<<1); //ADDR
	if(temp1 && temp3)
	{
		// clear ADDR flag
		// In slave mode, it is recommended to perform the complete clearing sequence (READ
		// SR1 then READ SR2) after ADDR is set.
		dummyRead = I2C1->SR1;
		dummyRead = I2C1->SR2;
		// Check master mode or slave mode
		if( I2C1->SR2 & (1<<0) )
		{
			// Master mode(using polling mechanism not interrupt)
		}
		else
		{
			// Slave mode
			Global_I2C_Config[0].p_Slave_Event_CallBack(I2C_EV_ADDR_MATCH);
		}
	}
	//----------------------------------------------------------
	// Handle TxE: Data register empty (master request data from slave)-->slave_transmitter
	temp3 = (I2C1->SR1 & (1<<7)); //TXE
	if(temp1 && temp2 && temp3)	//in case TXE=1, ITEVTEN=1, ITBUFEN=1
	{
		// Check master mode or slave mode
		if(I2C1->SR2 & (1<<0))
		{
			// Master mode(using polling mechanism not interrupt)
		}
		else
		{
			// Slave mode
			// Check if slave in transmit mode
			if(I2C1->SR2 & (1<<2)) //TRA: Transmitter/receiver: 1: Data bytes transmitted
			{
				Global_I2C_Config[0].p_Slave_Event_CallBack(I2C_EV_DATA_REQ);
			}
		}
	}
	//----------------------------------------------------------
	// Handle RxNE: Data register not empty (slave receive data)-->slave_Receiver
	temp3 = I2C1->SR1 & (1<<6);	//RXNE
	if(temp1 && temp2 && temp3)	//in case RXNE=1, ITEVTEN=1, ITBUFEN=1
	{
		// Check master mode or slave mode
		if(I2C1->SR2 & (1<<0))
		{
			// Master mode(using polling mechanism not interrupt)
		}
		else
		{
			// Slave mode
			if(!(I2C1->SR2 & (1<<2))) // Check receive mode TRA: Transmitter/receiver: 0: Data bytes received
			{
				Global_I2C_Config[0].p_Slave_Event_CallBack(I2C_EV_DATA_REC);
			}
		}
	}
}

void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}
