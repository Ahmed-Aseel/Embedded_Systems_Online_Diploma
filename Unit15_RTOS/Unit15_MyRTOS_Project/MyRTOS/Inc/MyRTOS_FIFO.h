/*
 * MyRTOS_FIFO.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#ifndef INC_MYRTOS_FIFO_H_
#define INC_MYRTOS_FIFO_H_

#include <stdio.h>
#include <stdlib.h>
#include "Scheduler.h"

// User select element data type (uint8, uint16, unit32, uint64)
#define element_type Task_Ref*

// type definitions
typedef struct
{
	uint32_t length;
	uint32_t count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_BUF_t;

typedef enum
{
	FIFO_No_Error,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null
}FIFO_Status;

// APIs
FIFO_Status FIFO_Create(FIFO_BUF_t* fifo, element_type* buf, uint32_t length);
FIFO_Status FIFO_Enqueue(FIFO_BUF_t* fifo, element_type item);
FIFO_Status FIFO_Dequeue(FIFO_BUF_t* fifo, element_type* item);
FIFO_Status FIFO_Is_Full(FIFO_BUF_t* fifo);
FIFO_Status FIFO_Is_Empty(FIFO_BUF_t* fifo);
void FIFO_Print(FIFO_BUF_t* fifo);

#endif /* INC_MYRTOS_FIFO_H_ */
