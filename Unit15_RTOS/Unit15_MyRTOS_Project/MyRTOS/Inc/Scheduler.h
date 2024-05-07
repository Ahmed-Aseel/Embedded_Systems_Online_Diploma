/*
 * Scheduler.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <string.h>
#include "CortexMx_OS_Porting.h"

#define NUMBER_OF_TASKS    5

typedef enum
{
	NoError,
	Ready_Queue_Init_Error,
	Task_Exceeded_Stack,
	Task_Already_Activated,
	Mutex_Reached_MaxUsers,
	Mutext_IsNot_Acquired,
	Not_Mutext_Owner
}MyRTOS_errorID;

typedef enum
{
	SVC_ActivateTask = 1,
	SVC_TerminateTask,
	SVC_TaskWaitingTime,
	SVC_AcquireMutex,
	SVC_ReleaseMutex
}SVC_ID;

typedef enum
{
	Suspend,
	Waiting,
	Ready,
	Running
}task_state_t;

typedef struct
{
	enum
	{
		Blocking_Disable,
		Blocking_Enable
	}blocking_state;
	uint32_t Ticks_Count;
}time_wating_t;

typedef struct
{
	uint32_t Stack_Size;
	uint8_t Priority;
	void (*p_TaskEntry)(void); // Pointer to Task C function
	uint8_t AutoStart;
	uint32_t S_PSP_Task; // Not entered by the user
	uint32_t E_PSP_Task; // Not entered by the user
	uint32_t *Current_PSP; // Not entered by the user (Current Stack Top)
	uint8_t TaskName[30];
	task_state_t TaskState; // Not entered by the user
	time_wating_t TimeWaiting;
}Task_Ref;

typedef enum
{
	Acquired,
	Released
}mutex_state_t;

typedef struct
{
	uint8_t *Payload_ptr; // Pointer to buffer for data exchange
	uint16_t PayloadSize;
	Task_Ref *CurrentTask;
	Task_Ref *NextTask;
	uint8_t MutexName[30];
	mutex_state_t MutexState; // Not entered by the user
}Mutex_Ref;

// APIs
MyRTOS_errorID MyARTOS_Init();
MyRTOS_errorID MyRTOS_CreateTask(Task_Ref *Tref);
MyRTOS_errorID MyRTOS_ActivateTask(Task_Ref *Tref);
MyRTOS_errorID MyRTOS_TerminateTask(Task_Ref *Tref);
MyRTOS_errorID MyRTOS_TaskWait(Task_Ref *Tref, uint32_t ticks);
MyRTOS_errorID MyRTOS_AcquireMutex(Mutex_Ref *Mref, Task_Ref *Tref);
MyRTOS_errorID MyRTOS_ReleaseMutex(Mutex_Ref *Mref);
void MyRTOS_StartOS();

#endif /* INC_SCHEDULER_H_ */
