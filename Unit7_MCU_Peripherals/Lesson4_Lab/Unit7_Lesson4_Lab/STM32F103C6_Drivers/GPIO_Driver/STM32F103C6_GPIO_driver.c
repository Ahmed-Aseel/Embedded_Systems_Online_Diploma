/*
 * STM32F103C6_GPIO_driver.c
 *
 *  Created on: Sep 18, 2022
 *      Author: Ahmed Aseel
 */

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103C6_GPIO_driver.h"

/*
* ===============================================
* APIs Functions Definitions
* ===============================================
*/

/*=======================================================
* @Fn			: Get_CRLH_Position
* @brief		: Get the first bit position of the four bits that configure a specific pin
* @param [in]	: PinNumber specifies the port bit. Set by @ref GPIO_PINS_define
* @retval		: Position of the first bit for specific pin
* Note			: None
*/
uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	uint8_t position;
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		position = 0;
		break;

	case GPIO_PIN_1:
		position = 4;
		break;

	case GPIO_PIN_2:
		position = 8;
		break;

	case GPIO_PIN_3:
		position = 12;
		break;

	case GPIO_PIN_4:
		position = 16;
		break;

	case GPIO_PIN_5:
		position = 20;
		break;

	case GPIO_PIN_6:
		position = 24;
		break;

	case GPIO_PIN_7:
		position = 28;
		break;

	case GPIO_PIN_8:
		position = 0;
		break;

	case GPIO_PIN_9:
		position = 4;
		break;

	case GPIO_PIN_10:
		position = 8;
		break;

	case GPIO_PIN_11:
		position = 12;
		break;

	case GPIO_PIN_12:
		position = 16;
		break;

	case GPIO_PIN_13:
		position = 20;
		break;

	case GPIO_PIN_14:
		position = 24;
		break;

	case GPIO_PIN_15:
		position = 28;
		break;
	}

	return position;
}

/*=======================================================
* @Fn			: MCAL_GPIO_Init
* @brief		: Initialize the GPIOx piny according to the specified parameters in PinConfig
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: PinConfig: Pointer to a GPIO_PinConfig_t structure that contains the configuration
* 							 info for specified GPIO pin
* @retval		: None
* Note			: STM32F103C6 MCU has GPIO A:E modules
* 				  but LQFP48 has only GPIO A,B,part of C/D exported as external pins for MCU
*/
void MCAL_GPIO_Init	(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	volatile uint32_t* Configregister = NULL;
	uint8_t PIN_Config = 0;
	//Port configuration register low (GPIOx_CRL) Configure pins 0:7
	//Port configuration register high (GPIOx_CRH) Configure pins 8:15
	Configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH;

	//Clear CNFy[1:0] MODEy[1:0]
	*Configregister &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// if pin is output
	if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP ||
	   PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)
	{
		PIN_Config = ( (((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0F );
	}
	else
	{
		if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO || PinConfig->GPIO_MODE == GPIO_MODE_ANALOG)
		{
			PIN_Config = ( (PinConfig->GPIO_MODE << 2) & 0x0F );
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) //Consider it as input floating
		{
			PIN_Config = ( (GPIO_MODE_INPUT_FLO << 2) & 0x0F );
		}
		else //pull-up & pull-down
		{
			PIN_Config = ( (GPIO_MODE_INPUT_PU << 2) & 0x0F );
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//PxODR register = 1 Input pull-up : Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				//PxODR register = 0 Input pull-down : Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	//Write on CRL or CRH
	*Configregister |= ( PIN_Config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );
}

/*=======================================================
* @Fn			: MCAL_GPIO_DeInit
* @brief		: Reset all the GPIOx registers
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @retval		: None
* Note			: None
*/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx )
{
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set & Cleared by software
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2); //Bit 2 IOPARST: I/O port A reset
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3); //Bit 3 IOPBRST: IO port B reset
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4); //Bit 4 IOPCRST: IO port C reset
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5); //Bit 5 IOPDRST: I/O port D reset
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6); //Bit 6 IOPERST: I/O port E reset
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/*=======================================================
* @Fn			: MCAL_GPIO_ReadPin
* @brief		: Read a specific input pin
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: PinNumber specifies the port bit to read. Set by @ref GPIO_PINS_define
* @retval		: The input pin value (2 values based on @ref GPIO_PIN_State)
* Note			: None
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	if(GPIOx->IDR & PinNumber)
	{
		return GPIO_PIN_SET;
	}
	else
	{
		return GPIO_PIN_RESET;
	}
}

/*=======================================================
* @Fn			: MCAL_GPIO_ReadPort
* @brief		: Read a specific input port
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @retval		: The input port value
* Note			: None
*/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t port_value;
	port_value = (uint16_t)GPIOx->IDR;
	return port_value;
}

/*=======================================================
* @Fn			: MCAL_GPIO_WritePort
* @brief		: Write on specific output port
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: Value: Port value
* @retval		: None
* Note			: None
*/void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/*=======================================================
* @Fn			: MCAL_GPIO_WritePin
* @brief		: Write on a specific input pin
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: PinNumber specifies the port bit to write. Set by @ref GPIO_PINS_define
* @param [in]	: Value: Pin value
* @retval		: None
* Note			: None
*/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}

/*=======================================================
* @Fn			: MCAL_GPIO_TogglePin
* @brief		: Toggle a specified GPIO Pin
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: PinNumber specifies the port bit to toggle. Set by @ref GPIO_PINS_define
* @retval		: None
* Note			: None
*/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}

/*=======================================================
* @Fn			: MCAL_GPIO_LockPin
* @brief		: The locking allows the IO configuration to be frozen
* @param [in]	: GPIOx where x can be (A..G depending on device used) to select the GPIO peripheral
* @param [in]	: PinNumber specifies the port bit to lock. Set by @ref GPIO_PINS_define
* @retval		: Ok if the pin is locked or ERROR if not. Set by @ref GPIO_LOCK_State
* Note			: None
*/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked.

	//Set LCKK[16]
	volatile uint32_t temp = 1<<16;
	//Set Corresponding LCKy
	temp |= PinNumber;
	//Write 1
	GPIOx->LCKR = temp;
	//Write 0
	GPIOx->LCKR = PinNumber;
	//Write 1
	GPIOx->LCKR = temp;

	//Read 0
	temp = GPIOx->LCKR;

	//Read 1 (this read is optional but confirms that the lock is active)
	if(GPIOx->LCKR & (1<<16))
	{
		return GPIO_LOCK_ENABLED;
	}
	else
	{
		return GPIO_LOCK_ERROR;
	}
}
