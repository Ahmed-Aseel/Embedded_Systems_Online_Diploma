/*
 * AlmMon_Interface.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

/********** Header Protection **********/
#ifndef ALMMON_INTERFACE_H_
#define ALMMON_INTERFACE_H_

#define ALARM_TiMER_DURATION  200000 // assume 10sec

/***************************** Functions Prototype *****************************/
void ALARM_INITIALIZATION();
void High_Pressure_Detected();
void Delay(uint32_t nCount);

#endif /******** ALMMON_INTERFACE_H_ ********/
