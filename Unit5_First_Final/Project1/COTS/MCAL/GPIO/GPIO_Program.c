/*
 * GPIO_Program.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

#include "Platform_Types.h"
#include "BitMath.h"
#include "GPIO_Private.h"
#include "GPIO_Interface.h"

/***************************** Functions Definition *****************************/

/*******************************************************************************/
void GPIO_INITIALIZATION()
{
    Set_Bit(APB2ENR, 2);
    GPIOA_CRL &= 0xFF0FFFFF;
    GPIOA_CRL |= 0x00000000;
    GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0x22222222;
}
/*******************************************************************************/