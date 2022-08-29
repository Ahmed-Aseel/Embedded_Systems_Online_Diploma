/*
 * AlmMon_Program.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

#include "Platform_Types.h"
#include "AlmAct_Interface.h"
#include "AlmMon_Interface.h"

/***************************** Functions Definition *****************************/

/*******************************************************************************/
void ALARM_INITIALIZATION()
{
    /* Stop alarm */
    Set_Alarm_Actuator(0);    
}

/*******************************************************************************/
void High_Pressure_Detected()
{
    /* Start alarm */
    Set_Alarm_Actuator(1);
    /* Wait for alarm time duration */
    Delay(ALARM_TiMER_DURATION);
    /* Stop alarm */
    Set_Alarm_Actuator(0);
}

/*******************************************************************************/
void Delay(uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}
/*******************************************************************************/