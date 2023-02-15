/*
 * STM32F103C6_GPIO_driver.h
 *
 *  Created on: Sep 18, 2022
 *      Author: Ahmed Aseel
 */

#ifndef STM32F103C6_GPIO_DRIVER_H_
#define STM32F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PINS_define
#define GPIO_PIN_0					((uint16_t)0x0001)   // Pin 0   Selected
#define GPIO_PIN_1					((uint16_t)0x0002)   // Pin 1   Selected
#define GPIO_PIN_2					((uint16_t)0x0004)   // Pin 2   Selected
#define GPIO_PIN_3					((uint16_t)0x0008)   // Pin 3   Selected
#define GPIO_PIN_4					((uint16_t)0x0010)   // Pin 4   Selected
#define GPIO_PIN_5					((uint16_t)0x0020)   // Pin 5   Selected
#define GPIO_PIN_6					((uint16_t)0x0040)   // Pin 6   Selected
#define GPIO_PIN_7					((uint16_t)0x0080)   // Pin 7   Selected
#define GPIO_PIN_8					((uint16_t)0x0100)   // Pin 8   Selected
#define GPIO_PIN_9					((uint16_t)0x0200)   // Pin 9   Selected
#define GPIO_PIN_10					((uint16_t)0x0400)   // Pin 10  Selected
#define GPIO_PIN_11					((uint16_t)0x0800)   // Pin 11  Selected
#define GPIO_PIN_12					((uint16_t)0x1000)   // Pin 12  Selected
#define GPIO_PIN_13					((uint16_t)0x2000)   // Pin 13  Selected
#define GPIO_PIN_14					((uint16_t)0x4000)   // Pin 14  Selected
#define GPIO_PIN_15					((uint16_t)0x8000)   // Pin 15  Selected
#define GPIO_PIN_ALL				((uint16_t)0xFFFF    // All Pins Selected
#define GPIO_PIN_MASK				0x0000FFFFU          // Pins mask for assert test

/*  @ref GPIO_MODE_define
	0: Analog mode
	1: Floating input (reset state)
	2: Input with pull-up
	3: Input with pull-down
	4: General purpose output push-pull
	5: General purpose output Open-drain
	6: Alternate function output Push-pull
	7: Alternate function output Open-drain
	8: Alternate function INPUT
*/
#define GPIO_MODE_ANALOG				0x00000000U   //Analog mode
#define GPIO_MODE_INPUT_FLO				0x00000001U   //Floating input
#define GPIO_MODE_INPUT_PU				0x00000002U   //Input with pull-up
#define GPIO_MODE_INPUT_PD				0x00000003U   //Input with pull-down
#define GPIO_MODE_OUTPUT_PP				0x00000004U   //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD				0x00000005U   //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006U   //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007U   //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT				0x00000008U   //Alternate function INPUT

/*  @ref GPIO_SPEED_define
	01: Output mode, max speed 10 MHz.
	10: Output mode, max speed 2 MHz.
	11: Output mode, max speed 50 MHz.
*/
#define GPIO_SPEED_10M					0x00000001U   //Output mode, max speed 10 MHz
#define GPIO_SPEED_2M					0x00000002U   //Output mode, max speed 2  MHz
#define GPIO_SPEED_50M					0x00000003U   //Output mode, max speed 50 MHz

//@ref GPIO_PIN_State
#define GPIO_PIN_RESET					0
#define GPIO_PIN_SET					1

//@ref GPIO_LOCK_State
#define GPIO_LOCK_ERROR		 			0
#define GPIO_LOCK_ENABLED    			1


//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	uint16_t GPIO_PinNumber    ; // Specifies the GPIO pins to be configured.
							    // This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE         ; // Specifies the operating mode for the selected pins
								// This parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed ; // Specifies the speed for the selected pins
								// This parameter can be a value of @ref GPIO_SPEED_define
}GPIO_PinConfig_t;

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx );

//READ APIs
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

//WRITE APIS
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value);
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

#endif /* STM32F103C6_GPIO_DRIVER_H_ */
