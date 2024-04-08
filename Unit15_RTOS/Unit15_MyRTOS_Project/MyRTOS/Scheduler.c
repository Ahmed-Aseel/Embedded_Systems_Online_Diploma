/*
 * Scheduler.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#include "Scheduler.h"
#include "MyRTOS_FIFO.h"

struct
{
	Task_Ref* OSTasks[NUMBER_OF_TASKS];
	uint32_t S_MSP_Task;
	uint32_t E_MSP_Task;
	uint32_t PSP_Task_Locator;
	uint32_t NoOfCreatedTasks;
	Task_Ref *CurrentTask;
	Task_Ref *NextTask;
	enum
	{
		OS_Suspend,
		OS_Running
	}OS_Mode;
}Os_Control;

static FIFO_BUF_t Ready_Queue;
static Task_Ref* Ready_Queue_Buf[NUMBER_OF_TASKS];
static Task_Ref MyRTOS_IdleTask;
volatile uint8_t IdleTask_flag, Systick_flag;

static MyRTOS_errorID MyRTOS_Create_MainStack();
static void MyRTOS_Init_TaskStack(Task_Ref *Tref);
static void MyRTOS_Idle_Task();
static void MyRTOS_OS_SVC_Set(SVC_ID ID);
static void MyRTOS_Update_ScheduleTable();
static void bubble_sort();
static void MyRTOS_Decide_WhatNext();
/* ============================================= */
MyRTOS_errorID MyARTOS_Init()
{
	MyRTOS_errorID error_status = NoError;

	// Update OS Mode (OS_Suspend)
	Os_Control.OS_Mode = OS_Suspend;

	// Specify Main Stack For OS
	error_status = MyRTOS_Create_MainStack();

	// Create OS Ready Queue
	if(FIFO_Create(&Ready_Queue, Ready_Queue_Buf, NUMBER_OF_TASKS) != FIFO_No_Error)
	{
		error_status = Ready_Queue_Init_Error;
	}
	else
	{
		// Configure Idle Task
		strcpy((char*)MyRTOS_IdleTask.TaskName, "Idle_Task");
		MyRTOS_IdleTask.Priority = 255;
		MyRTOS_IdleTask.p_TaskEntry = MyRTOS_Idle_Task;
		MyRTOS_IdleTask.Stack_Size = 100;

		error_status = MyRTOS_CreateTask(&MyRTOS_IdleTask);
	}

	return error_status;
}

MyRTOS_errorID MyRTOS_CreateTask(Task_Ref *Tref)
{
	MyRTOS_errorID error_status = NoError;

	// Create task PSP stack
	/* - S_PSP_Task -
	 * - Task stack -
	 * - E_PSP_Task -
	 * -  8 bytes   -
	 */
	Tref->S_PSP_Task = Os_Control.PSP_Task_Locator;
	Tref->E_PSP_Task = Tref->S_PSP_Task - Tref->Stack_Size;
	// Aligned 8 bytes space between task PSP and other
	Os_Control.PSP_Task_Locator = Tref->E_PSP_Task - 8;

	// Check if task stack size exceed the available PSP stack size
	if(Tref->E_PSP_Task < (uint32_t)&_eheap)
	{
		// Error exceed the available stack size
		error_status = Task_Exceeded_Stack;
	}
	else
	{
		// Initialize task PSP stack
		MyRTOS_Init_TaskStack(Tref);

		// TAsk state update --> suspended
		Tref->TaskState = Suspend;

		// Add task to schedule table
		Os_Control.OSTasks[Os_Control.NoOfCreatedTasks] = Tref;
		Os_Control.NoOfCreatedTasks++;
	}

	return error_status;
}
MyRTOS_errorID MyRTOS_ActivateTask(Task_Ref *Tref)
{
	MyRTOS_errorID error_status = NoError;

	Tref->TaskState = Waiting;

	MyRTOS_OS_SVC_Set(SVC_ActivateTask);

	return error_status;
}

MyRTOS_errorID MyRTOS_TerminateTask(Task_Ref *Tref)
{
	MyRTOS_errorID error_status = NoError;

	MyRTOS_OS_SVC_Set(SVC_TerminateTask);

	return error_status;
}

void MyRTOS_StartOS()
{
	Os_Control.OS_Mode = OS_Running;
	// Set default/current task --> MyRTOS_IdleTask
	Os_Control.CurrentTask = &MyRTOS_IdleTask;
	// Activate MyRTOS_IdleTask
	MyRTOS_ActivateTask(&MyRTOS_IdleTask);
	// Start Ticker --> tick = 1ms
	Start_Ticker();
	// Set PSP with CurrentTask/MyRTOS_IdleTask PSP
	OS_SET_PSP(Os_Control.CurrentTask->S_PSP_Task);
	// Switch thread mode from MSP to PSP
	OS_SWITCH_SP_TO_PSP();
	// Switch thread mode to unprivileged
	OS_SWITCH_ACCESS_TO_UNPRIVILEGED();
	// Call CurrentTask/MyRTOS_IdleTask
	Os_Control.CurrentTask->p_TaskEntry();

	while(1);
}

/* ============================================== */
static MyRTOS_errorID MyRTOS_Create_MainStack()
{
	MyRTOS_errorID error_status = NoError;

	Os_Control.S_MSP_Task = (uint32_t)&_estack;
	Os_Control.E_MSP_Task = Os_Control.S_MSP_Task - MAIN_STACK_SIZE;
	// Aligned 8 bytes space between MSP & PSP
	Os_Control.PSP_Task_Locator = Os_Control.E_MSP_Task - 8;

	if(Os_Control.E_MSP_Task < (uint32_t)&_eheap)
	{
		// Error exceed the available stack size
		error_status = Task_Exceeded_Stack;
	}

	return error_status;
}

static void MyRTOS_Idle_Task()
{
	while(1)
	{
		IdleTask_flag ^= 1;
		__asm volatile("NOP");
	}
}

static void MyRTOS_Init_TaskStack(Task_Ref *Tref)
{
	/* Task Stack Frame --> done by default by processor
	 * xPSR
	 * PC : next instruction to be run
	 * LR : return register saved in CPU while Tref is running before task switching
	 * R12
	 * R3:R0
	 * ------> done manually
	 * R4:R11
	 */

	Tref->Current_PSP = (uint32_t*)Tref->S_PSP_Task;

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0x01000000; // Dummy xPSR T bit should be 1
	Tref->Current_PSP--;
	*(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry; // Dummy PC
	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0xFFFFFFFD; // Dummy LR EXC_RETURN to thread mode with PSP

	// Dummy values for R12:R0
	for (int i = 0; i < 13; ++i)
	{
		Tref->Current_PSP--;
		*(Tref->Current_PSP) = 0;
	}
}

// Handler mode
static void bubble_sort()
{
    uint32_t i = 0, j = 0, n;
    uint8_t sorted_flag = 1;
    Task_Ref *temp;

    n = Os_Control.NoOfCreatedTasks;

    for(i = 0; i < n-1; i++)
    {
    	/* Set sorted_flag before inner loop
    	 * the value of sorted_flag changes only if there is swap
    	 */
    	sorted_flag = 1;

        for(j = 0; j < n-1-i; j++)
        {
            if(Os_Control.OSTasks[j]->Priority > Os_Control.OSTasks[j+1]->Priority)
            {
            	// Swap 2 elements
            	temp = Os_Control.OSTasks[j];
            	Os_Control.OSTasks[j] = Os_Control.OSTasks[j+1];
            	Os_Control.OSTasks[j+1] = temp;
                // Clear sorted_flag indicating array is not sorted
                sorted_flag = 0;
            }
        }

        /* If there is no swap the array is already sorted
		 * no need to iterate again
		 */
        if(sorted_flag == 1)
        {
            return;
        }
    }
}

// Handler mode
static void MyRTOS_Update_ScheduleTable()
{
	uint32_t i = 0;
    Task_Ref *temp, *ptask, *pnext_task;

    /* 1- bubble sort schedule table(Os_Control.OSTasks[NUMBER_OF_TASKS])
	 * 	  high priority then low
	 */
	bubble_sort();

	/* 2- Free ready queue */
	while(FIFO_Dequeue(&Ready_Queue, &temp) != FIFO_Empty);

	/* 3- Update ready queue */
	while(i < Os_Control.NoOfCreatedTasks)
	{
		ptask = Os_Control.OSTasks[i];
		pnext_task = Os_Control.OSTasks[i+1];
		if(ptask->TaskState != Suspend)
		{
			// In case we reached the end of available tasks
			if(pnext_task->TaskState == Suspend)
			{
				FIFO_Enqueue(&Ready_Queue, ptask);
				ptask->TaskState = Ready;
				break;
			}
			// If ptask priority > pnext_task (highest priority means lower value)
			if(ptask->Priority < pnext_task->Priority)
			{
				FIFO_Enqueue(&Ready_Queue, ptask);
				ptask->TaskState = Ready;
				break;
			}
			else if(ptask->Priority == pnext_task->Priority)
			{
				FIFO_Enqueue(&Ready_Queue, ptask);
				ptask->TaskState = Ready;
			}
			else
			{
				/* Not allowed ptask->Priority > pnext_task->Priority
				 * as we already reordered it using bubble sort
				 */
				break;
			}
		}

		i++;
	}
}

// Handler mode
static void MyRTOS_Decide_WhatNext()
{
	// If ready queue is empty and Os_Control.CurrentTask != suspend
	if(Ready_Queue.count == 0 && Os_Control.CurrentTask->TaskState != Suspend)
	{
		Os_Control.CurrentTask->TaskState = Running;
		// Add current task again(round robin)
		FIFO_Enqueue(&Ready_Queue, Os_Control.CurrentTask);
		Os_Control.NextTask = Os_Control.CurrentTask;
	}
	else
	{
		FIFO_Dequeue(&Ready_Queue, &Os_Control.NextTask);
		Os_Control.NextTask->TaskState = Running;
		if(Os_Control.CurrentTask->Priority == Os_Control.NextTask->Priority
							&& Os_Control.CurrentTask->TaskState != Suspend)
		{
			FIFO_Enqueue(&Ready_Queue, Os_Control.CurrentTask);
			Os_Control.CurrentTask->TaskState = Ready;
		}
	}
}

// Handler mode
void OS_SVC(uint32_t* Stack_Frame)
{
	// R0 is a pointer to OS_SVC_Set stack frame
	// R0, R1, R2, R3, R12, LR, Return Address (PC), xPSR
	uint8_t SVC_Number;

	SVC_Number = *((uint8_t*)(((uint8_t*)Stack_Frame[6]) - 2));

	switch(SVC_Number)
	{
		case SVC_ActivateTask: // Activate Task
		case SVC_TerminateTask:  // Terminate Task
			// Update scheduler table, ready queue
			MyRTOS_Update_ScheduleTable();
			// OS is in running state
			if(Os_Control.OS_Mode == OS_Running)
			{
				if(strcmp((char*)Os_Control.CurrentTask->TaskName, "Idle_Task"))
				{
					// Decide what's next
					MyRTOS_Decide_WhatNext();
					// trigger OS_PendSV (context switching / restore)
					Trigger_OS_PendSV();
				}
			}
			break;
		case SVC_TaskWaitingTime: // Waiting Time
			break;
	}
}

// Tread mode
static void MyRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch(ID)
	{
		case SVC_ActivateTask: // Activate Task
			__asm volatile ("SVC #0x01");
			break;
		case SVC_TerminateTask:  // Terminate Task
			__asm volatile ("SVC #0x02");
			break;
		case SVC_TaskWaitingTime: // Waiting Time
			__asm volatile ("SVC #0x03");
			break;
	}
}

__attribute__ ((naked)) void PendSV_Handler()
{
	/*
	 * Save context of current task
	 */
	// Get the current task PSP from CPU register as CPU pushes(xPSR,LR,...,R0)
	OS_GET_PSP(Os_Control.CurrentTask->Current_PSP);

	// Using this Current_PSP pointer to save R4:R11
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R4" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R5" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R6" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R7" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R8" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R9" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R10" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %0,R11" : "=r" (*(Os_Control.CurrentTask->Current_PSP)));

	/* Save current value of PSP
	 * already saved in Current_PSP
	 */

	/*
	 * Restore context of next task
	 */
	Os_Control.CurrentTask = Os_Control.NextTask;
	Os_Control.NextTask = NULL;

	__asm volatile ("MOV R11,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R10,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R9,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R8,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R7,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R6,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R5,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;
	__asm volatile ("MOV R4,%0" : : "r" (*(Os_Control.CurrentTask->Current_PSP)));
	Os_Control.CurrentTask->Current_PSP++;

	// Update PSP with the stack of the task to be run
	OS_SET_PSP(Os_Control.CurrentTask->Current_PSP);
	__asm volatile ("BX LR");
}

void SysTick_Handler()
{
	Systick_flag ^= 1;

	// Decide what's next
	MyRTOS_Decide_WhatNext();
	// trigger OS_PendSV (context switching / restore)
	Trigger_OS_PendSV();
}

