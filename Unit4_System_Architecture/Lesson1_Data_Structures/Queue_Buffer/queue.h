/*
 * queue.h
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdINT.h>

// user
// select element data type (uint8, uint16, unit32, uint64)
#define element_type uint32_t

// type definitions
typedef struct
{
	uint32_t length;
	uint32_t count;
	element_type* base;
	element_type* head;
	element_type* tail;

}QUEUE_BUF_t;

typedef enum
{
	QUEUE_No_Error,
	QUEUE_Full,
	QUEUE_Empty,
	QUEUE_Null

}QUEUE_Status;

// APIs
QUEUE_Status QUEUE_Create(QUEUE_BUF_t* queue_buf, element_type* buf, uint32_t length);
QUEUE_Status QUEUE_Enqueue_Item(QUEUE_BUF_t* queue_buf, element_type item);
QUEUE_Status QUEUE_Dequeue_Item(QUEUE_BUF_t* queue_buf, element_type* item);
void QUEUE_Print(QUEUE_BUF_t* queue_buf);

#endif /* QUEUE_H_ */
