/*
 * PreSen_Program.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

#include "Platform_Types.h"
#include "GPIO_Private.h"
#include "GPIO_Interface.h"
#include "PreSen_Interface.h"

/***************************** Functions Definition *****************************/

/*******************************************************************************/
uint32_t Get_Pressure_Val()
{
	return (GPIOA_IDR & 0xFF);
}
/*******************************************************************************/
