/*
 * STM32F103C6_EXTI_driver.C
 *
 *  Created on: Sep 27, 2022
 *      Author: Ahmed Aseel
 */

#include "STM32F103C6_EXTI_driver.h"

/*
* ===============================================
* Generic Variables
* ===============================================
*/
void (*GP_IRQ_CallBack[15])(void);

/*
* ===============================================
* Generic Functions
* ===============================================
*/

static void NVIC_Enable(uint8_t IRQ_Number)
{
	switch(IRQ_Number)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI9_5_Enable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI15_10_Enable();
		break;
	}
}

static void NVIC_Disable(uint8_t IRQ_Number)
{
	switch(IRQ_Number)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI9_5_Disable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI15_10_Disable();
		break;
	}

}

/*=======================================================
* @Fn			: Update_EXTI
* @brief		: Initialize EXTI from specific GPIO Pin, specify the Mask/Trigger conditions & IRQ CallBack func
* @param [in]	: EXTI_Config Set by @ref EXTI_define, @ref EXTI_Trigger_define & @ref EXTI_IRQ_define
* @retval		: None
* Note			: None
*/
static void Update_EXTI(EXTI_PinConfig_t *EXTI_Config)
{
	//1- Configure GPIO to be AF input -> Floating input
	GPIO_PinConfig_t PinConfig;

	//Update GPIO Pin to be Floating input
	PinConfig.GPIO_PinNumber = EXTI_Config->EXTI_Pin.GPIO_Pin;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port, &PinConfig);

	//2- Update AFIO to route between EXTI line with Port A | B | C | D
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_Pin.ETI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_position = (EXTI_Config->EXTI_Pin.ETI_InputLineNumber % 4) * 4;

	//Clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position);
	AFIO->EXTICR[AFIO_EXTICR_index] |= (AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_Pin.GPIO_Port) << AFIO_EXTICR_position);

	//3- Update Rising/Falling edge
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_RISING_FALLING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	}

	//4- Update IRQ Handling CallBack
	GP_IRQ_CallBack[EXTI_Config->EXTI_Pin.ETI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//5- Enable/Disable IRQ EXTI & NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
		NVIC_Enable(EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	}
	else if(EXTI_Config->IRQ_EN == EXTI_IRQ_DISABLE)
	{
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
		NVIC_Disable(EXTI_Config->EXTI_Pin.ETI_InputLineNumber);
	}
}

/*
* ===============================================
* APIs Functions Definitions
* ===============================================
*/

/*=======================================================
* @Fn			: MCAL_EXTI_GPIO_Init
* @brief		: Initialize EXTI from specific GPIO Pin, specify the Mask/Trigger conditions & IRQ CallBack func
* @param [in]	: EXTI_Config Set by @ref EXTI_define, @ref EXTI_Trigger_define & @ref EXTI_IRQ_define
* @retval		: None
* Note			: STM32F103C6 MCU has GPIO A:E modules
* 				  but LQFP48 has only GPIO A,B,part of C/D exported as external pins for MCU
* 				  also mandatory to enable RCC Clock for AFIO & the corresponding GPIO
*/
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/*=======================================================
* @Fn			: MCAL_EXTI_GPIO_DeInit
* @brief		: Reset EXTI Registers and NVIC Corresponding IRQ Mask
* @retval		: None
* Note			: None
*/
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	//rc_w1 cleared by writing '1' into the bit
	EXTI->PR    = 0xFFFFFFFF;

	//Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable();
	NVIC_IRQ7_EXTI1_Disable();
	NVIC_IRQ8_EXTI2_Disable();
	NVIC_IRQ9_EXTI3_Disable();
	NVIC_IRQ10_EXTI4_Disable();
	NVIC_IRQ23_EXTI9_5_Disable();
	NVIC_IRQ40_EXTI15_10_Disable();
}

/*=======================================================
* @Fn			: MCAL_EXTI_GPIO_Update
* @brief		: Initialize EXTI from specific GPIO Pin, specify the Mask/Trigger conditions & IRQ CallBack func
* @param [in]	: EXTI_Config Set by @ref EXTI_define, @ref EXTI_Trigger_define & @ref EXTI_IRQ_define
* @retval		: None
* Note			: STM32F103C6 MCU has GPIO A:E modules
* 				  but LQFP48 has only GPIO A,B,part of C/D exported as external pins for MCU
* 				  also mandatory to enable RCC Clock for AFIO & the corresponding GPIO
*/
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/*
* ===============================================
* ISR Functions
* ===============================================
*/
void EXTI0_IRQHandler(void)  /* EXTI Line0 interrupt */
{
	//Cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= (1 << 0);

	//Call IRQ CallBack
	GP_IRQ_CallBack[0]();
}
void EXTI1_IRQHandler(void)  /* EXTI Line1 interrupt */
{
	//Cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= (1 << 1);

	//Call IRQ CallBack
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)  /* EXTI Line2 interrupt */
{
	//Cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= (1 << 2);

	//Call IRQ CallBack
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)  /* EXTI Line3 interrupt  */
{
	//Cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= (1 << 3);

	//Call IRQ CallBack
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)  /* EXTI Line4 interrupt  */
{
	//Cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= (1 << 4);

	//Call IRQ CallBack
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void) /* EXTI Line[9:5] interrupts */
{
	if(EXTI->PR & (1 << 5)) { EXTI->PR |= (1 << 5);	GP_IRQ_CallBack[5](); }
	if(EXTI->PR & (1 << 6)) { EXTI->PR |= (1 << 6);	GP_IRQ_CallBack[6](); }
	if(EXTI->PR & (1 << 7)) { EXTI->PR |= (1 << 7);	GP_IRQ_CallBack[7](); }
	if(EXTI->PR & (1 << 8)) { EXTI->PR |= (1 << 8);	GP_IRQ_CallBack[8](); }
	if(EXTI->PR & (1 << 9)) { EXTI->PR |= (1 << 9);	GP_IRQ_CallBack[9](); }
}
void EXTI15_10_IRQHandler(void) /* EXTI Line[15:10] interrupts */
{
	if(EXTI->PR & (1 << 10)) { EXTI->PR |= (1 << 10);	GP_IRQ_CallBack[10](); }
	if(EXTI->PR & (1 << 11)) { EXTI->PR |= (1 << 11);	GP_IRQ_CallBack[11](); }
	if(EXTI->PR & (1 << 12)) { EXTI->PR |= (1 << 12);	GP_IRQ_CallBack[12](); }
	if(EXTI->PR & (1 << 13)) { EXTI->PR |= (1 << 13);	GP_IRQ_CallBack[13](); }
	if(EXTI->PR & (1 << 14)) { EXTI->PR |= (1 << 14);	GP_IRQ_CallBack[14](); }
	if(EXTI->PR & (1 << 15)) { EXTI->PR |= (1 << 15);	GP_IRQ_CallBack[15](); }
}
