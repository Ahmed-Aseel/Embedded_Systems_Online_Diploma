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
static void MyRTOS_Update_TaskWaiting();
static void MyRTOS_Decide_WhatNext();
static void bubble_sort();
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
		MyRTOS_IdleTask.Stack_Size = IDLE_TASK_STACK_SIZE;

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
	Os_Control.PSP_Task_Locator = Tref->E_PSP_Task - INTERTASK_SPACE;

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

	if(Tref->TimeWaiting.blocking_state != Blocking_Enable || Tref->TaskState != Waiting)
	{
		Tref->TaskState = Waiting;
		MyRTOS_OS_SVC_Set(SVC_ActivateTask);
	}
	else
	{
		error_status = Task_Already_Activated;
	}

	return error_status;
}

MyRTOS_errorID MyRTOS_TerminateTask(Task_Ref *Tref)
{
	MyRTOS_errorID error_status = NoError;

	Tref->TaskState = Suspend;

	MyRTOS_OS_SVC_Set(SVC_TerminateTask);

	return error_status;
}

MyRTOS_errorID MyRTOS_TaskWait(Task_Ref *Tref, uint32_t ticks)
{
	MyRTOS_errorID error_status = NoError;

	Tref->TimeWaiting.blocking_state = Blocking_Enable;
	Tref->TimeWaiting.Ticks_Count = ticks;
	// Task should be blocked/suspended
	Tref->TaskState = Suspend;

	MyRTOS_OS_SVC_Set(SVC_TerminateTask);

	return error_status;
}

MyRTOS_errorID MyRTOS_AcquireMutex(Mutex_Ref *Mref, Task_Ref *Tref)
{
	MyRTOS_errorID error_status = NoError;

	// Check that mutex not taken by any task
	if(Mref->CurrentTask == NULL && Mref->MutexState == Released)
	{
		Mref->CurrentTask = Tref;
		Mref->MutexState = Acquired;
	}
	else
	{
		// Check if there is pending request by any other task
		if(Mref->NextTask == NULL)
		{
			Mref->NextTask = Tref;
			// Move to suspend state till mutex released
			Tref->TaskState = Suspend;
			MyRTOS_OS_SVC_Set(SVC_TerminateTask);
		}
		else
		{
			error_status = Mutex_Reached_MaxUsers;
		}
	}

	return error_status;
}

MyRTOS_errorID MyRTOS_ReleaseMutex(Mutex_Ref *Mref)
{
	MyRTOS_errorID error_status = NoError;

	// Check that mutex not taken by any task
	if(Mref->CurrentTask != NULL && Mref->MutexState == Acquired)
	{
		// To achieve ownership only task that acquire mutex will release it
		if(Os_Control.CurrentTask == Mref->CurrentTask)
		{
			Mref->CurrentTask = Mref->NextTask;
			if(Mref->CurrentTask == NULL)
			{
				Mref->MutexState = Released;
			}
			Mref->NextTask = NULL;
			Mref->CurrentTask->TaskState = Waiting;
			MyRTOS_OS_SVC_Set(SVC_TaskWaitingTime);
		}
		else
		{
			error_status = Not_Mutext_Owner;
		}
	}
	else
	{
		error_status = Mutext_IsNot_Acquired;
	}

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
	Os_Control.PSP_Task_Locator = Os_Control.E_MSP_Task - INTERTASK_SPACE;

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
		// Wait for event
		__asm volatile("WFE");
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
static void MyRTOS_Update_TaskWaiting()
{
	for(int i = 0; i < Os_Control.NoOfCreatedTasks; ++i)
	{
		// Check if task is blocked until meet the time line
		if(Os_Control.OSTasks[i]->TaskState == Suspend)
		{
			if(Os_Control.OSTasks[i]->TimeWaiting.blocking_state == Blocking_Enable)
			{
				Os_Control.OSTasks[i]->TimeWaiting.Ticks_Count--;
				if(Os_Control.OSTasks[i]->TimeWaiting.Ticks_Count == 0)
				{
					Os_Control.OSTasks[i]->TimeWaiting.blocking_state = Blocking_Disable;
					Os_Control.OSTasks[i]->TaskState = Waiting;
					MyRTOS_OS_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
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
			// Update scheduler table, ready queue
			MyRTOS_Update_ScheduleTable();
			break;
		case SVC_AcquireMutex: // Acquire Mutex

			break;
		case SVC_ReleaseMutex: // Acquire Mutex

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
		case SVC_AcquireMutex: // Acquire Mutex
			__asm volatile ("SVC #0x04");
			break;
		case SVC_ReleaseMutex: // Acquire Mutex
			__asm volatile ("SVC #0x05");
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
	__asm volatile ("MOV R0,%0" : : "r" (Os_Control.CurrentTask->Current_PSP));
	__asm volatile ("SUB R0,R0,#32");

	__asm volatile ("STR R4,[R0,#28]");
	__asm volatile ("STR R5,[R0,#24]");
	__asm volatile ("STR R6,[R0,#20]");
	__asm volatile ("STR R7,[R0,#16]");
	__asm volatile ("STR R8,[R0,#12]");
	__asm volatile ("STR R9,[R0,#8]");
	__asm volatile ("STR R10,[R0,#4]");
	__asm volatile ("STR R11,[R0,#0]");

	__asm volatile ("MOV %0,R0" : "=r" (Os_Control.CurrentTask->Current_PSP));

	/* Save current value of PSP
	 * already saved in Current_PSP
	 */

	if(Os_Control.NextTask)
	{
		Os_Control.CurrentTask = Os_Control.NextTask;
		Os_Control.NextTask = NULL;
	}

	/*
	 * Restore context of next task
	 */
	__asm volatile ("MOV R0,%0" : : "r" (Os_Control.CurrentTask->Current_PSP));

	__asm volatile ("LDR R4,[R0,#28]");
	__asm volatile ("LDR R5,[R0,#24]");
	__asm volatile ("LDR R6,[R0,#20]");
	__asm volatile ("LDR R7,[R0,#16]");
	__asm volatile ("LDR R8,[R0,#12]");
	__asm volatile ("LDR R9,[R0,#8]");
	__asm volatile ("LDR R10,[R0,#4]");
	__asm volatile ("LDR R11,[R0,#0]");

	__asm volatile ("ADD R0,R0,#32");
	__asm volatile ("MOV %0,R0" : "=r" (Os_Control.CurrentTask->Current_PSP));

	// Update PSP with the stack of the task to be run
	OS_SET_PSP(Os_Control.CurrentTask->Current_PSP);
	__asm volatile ("BX LR");
}

void SysTick_Handler()
{
	Systick_flag ^= 1;

	// Update Waiting tasks time
	MyRTOS_Update_TaskWaiting();
	// Decide what's next
	MyRTOS_Decide_WhatNext();
	// trigger OS_PendSV (context switching / restore)
	Trigger_OS_PendSV();
}

