/*
 * AlmAct_Program.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

#include "Platform_Types.h"
#include "BitMath.h"
#include "GPIO_Private.h"
#include "GPIO_Interface.h"
#include "AlmAct_Interface.h"

/***************************** Functions Definition *****************************/

/*******************************************************************************/
void Set_Alarm_Actuator(uint8_t i)
{
    if (i == 1)
    {
        Start_Alarm();
    }
    else if (i == 0)
    {
        Stop_Alarm();
    }
}

/*******************************************************************************/
void Start_Alarm()
{
    Clr_Bit(GPIOA_ODR,13);    
}

/*******************************************************************************/
void Stop_Alarm()
{
    Set_Bit(GPIOA_ODR,13);    
}
/*******************************************************************************/
