/*
 * CortexMx_OS_Porting.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"

#define OS_SWITCH_ACCESS_TO_UNPRIVILEGED() __asm volatile ("MRS R0,CONTROL \n\t"\
											  	  	  	   "ORR R0,R0,#0x01 \n\t"\
														   "MSR CONTROL,R0")

#define OS_SWITCH_ACCESS_TO_PRIVILEGED()   __asm volatile ("MRS R0,CONTROL \n\t"\
											  	  	  	 "LSR R0,R0,#0x01 \n\t"\
											  	  	  	 "LSL R0,R0,#0x01 \n\t"\
														 "MSR CONTROL,R0")

#define OS_SWITCH_SP_TO_MSP() 			   __asm volatile ("MRS R0,CONTROL \n\t"\
														   "AND R0,R0,#0x05 \n\t"\
											  	  	  	   "MSR CONTROL,R0")

#define OS_SWITCH_SP_TO_PSP()  			   __asm volatile ("MRS R0,CONTROL \n\t"\
														   "ORR R0,R0,#0x02 \n\t"\
														   "MSR CONTROL,R0")

#define OS_SET_PSP(add) 		 __asm volatile ("MOV R0,%0 \n\t MSR PSP,R0" : : "r" (add))
#define OS_GET_PSP(add) 		 __asm volatile ("MRS R0,PSP \n\t MOV %0,R0"   : "=r" (add))

#define OS_GENERATE_EXCEPTION()  __asm volatile ("SVC 0x03")

// All sizes are in bytes
#define MAIN_STACK_SIZE 		3072
#define MIN_TASK_STACK_SIZE		512
#define IDLE_TASK_STACK_SIZE	100
#define INTERTASK_SPACE			8

extern uint32_t _estack;
extern uint32_t _eheap;

// APIs
void HW_Init();
void Trigger_OS_PendSV();
void Start_Ticker();

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
