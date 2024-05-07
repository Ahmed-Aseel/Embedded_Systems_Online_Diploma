/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

//-----------------------------
//Includes
//-----------------------------
#include "Scheduler.h"

Mutex_Ref Mutex_T1_T4;
Task_Ref Task1, Task2, Task3, Task4;
volatile uint8_t task1_flag, task2_flag, task3_flag, task4_flag;

void task1()
{
	static uint8_t count = 0;

	while(1)
	{
		// Task1 code
		task1_flag ^= 1;
		count++;
		if(count == 100)
		{
			MyRTOS_AcquireMutex(&Mutex_T1_T4, &Task1);
			MyRTOS_ActivateTask(&Task2);
		}
		else if(count == 200)
		{
			count = 0;
			MyRTOS_ReleaseMutex(&Mutex_T1_T4);
		}
	}
}

void task2()
{
	static uint8_t count = 0;

	while(1)
	{
		// Task2 code
		task2_flag ^= 1;
		count++;
		if(count == 100)
		{
			MyRTOS_ActivateTask(&Task3);
		}
		else if(count == 200)
		{
			count = 0;
			MyRTOS_TerminateTask(&Task2);
		}
	}
}

void task3()
{
	static uint8_t count = 0;

	while(1)
	{
		// Task3 code
		task3_flag ^= 1;
		count++;
		if(count == 100)
		{
			MyRTOS_ActivateTask(&Task4);
		}
		else if(count == 200)
		{
			count = 0;
			MyRTOS_TerminateTask(&Task3);
		}
	}
}

void task4()
{
	static uint8_t count = 0;

	while(1)
	{
		// Task4 code
		task4_flag ^= 1;
		count++;
		if(count == 3)
		{
			MyRTOS_AcquireMutex(&Mutex_T1_T4, &Task4);
		}
		else if(count == 200)
		{
			count = 0;
			MyRTOS_ReleaseMutex(&Mutex_T1_T4);
			MyRTOS_TerminateTask(&Task4);
		}
	}
}

int main(void)
{
	MyRTOS_errorID error_status = NoError;
	// Hardware_Init (Initialize Clock Tree , RestController)
	HW_Init();

	error_status = MyARTOS_Init();
	if(error_status != NoError)
		while(1);

	strcpy((char*)Mutex_T1_T4.MutexName, "Mutex_T1_T4");
	Mutex_T1_T4.PayloadSize = 0;
	Mutex_T1_T4.Payload_ptr = NULL;
	Mutex_T1_T4.CurrentTask = NULL;
	Mutex_T1_T4.NextTask = NULL;
	Mutex_T1_T4.MutexState = Released;

	strcpy((char*)Task1.TaskName, "Task1");
	Task1.Stack_Size = MIN_TASK_STACK_SIZE;
	Task1.p_TaskEntry = task1;
	Task1.Priority = 4;

	strcpy((char*)Task2.TaskName, "Task2");
	Task2.Stack_Size = MIN_TASK_STACK_SIZE;
	Task2.p_TaskEntry = task2;
	Task2.Priority = 3;

	strcpy((char*)Task3.TaskName, "Task3");
	Task3.Stack_Size = MIN_TASK_STACK_SIZE;
	Task3.p_TaskEntry = task3;
	Task3.Priority = 2;

	strcpy((char*)Task4.TaskName, "Task4");
	Task4.Stack_Size = MIN_TASK_STACK_SIZE;
	Task4.p_TaskEntry = task4;
	Task4.Priority = 1;

	error_status = MyRTOS_CreateTask(&Task1);
	error_status = MyRTOS_CreateTask(&Task2);
	error_status = MyRTOS_CreateTask(&Task3);
	error_status = MyRTOS_CreateTask(&Task4);

	error_status = MyRTOS_ActivateTask(&Task1);
//	error_status = MyRTOS_ActivateTask(&Task2);
//	error_status = MyRTOS_ActivateTask(&Task3);

	MyRTOS_StartOS();

	while(1);

	return 0;
}

