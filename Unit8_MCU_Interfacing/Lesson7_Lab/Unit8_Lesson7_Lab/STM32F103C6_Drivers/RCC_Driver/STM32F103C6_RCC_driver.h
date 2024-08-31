/*
 * STM32F103C6_RCC_driver.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Ahmed Aseel
 */

#ifndef STM32F103C6_RCC_DRIVER_H_
#define STM32F103C6_RCC_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

//-----------------------------
//Macros Configuration References
//-----------------------------
#define HSI_RC_CLOCK		(uint32_t)8000000
#define HSE_CLOCK			(uint32_t)16000000

/*
* ===============================================
* APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/

uint32_t MCAL_RCC_Getsys_CLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* STM32F103C6_RCC_DRIVER_H_ */
