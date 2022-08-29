/*
 * main.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

#include "Platform_Types.h"
#include "BitMath.h"
#include "GPIO_Interface.h"
#include "PreSen_Interface.h"
#include "AlmMon_Interface.h"

int main ()
{
	int PreVal;
	/* Initialize GPIO */
	GPIO_INITIALIZATION();
	/* Initialize Alarm ---> stop alarm */
	ALARM_INITIALIZATION();

	while (1)
	{
		/* Read pressure sensor value */
		PreVal = Get_Pressure_Val();
		/* Check if high pressure occures */
		if (PreVal > THRESHOLD)
		{
			High_Pressure_Detected();
		}

		/* Delay between pressure sensor values */
		Delay(PRESEN_PULL_TIME);
	}
}
