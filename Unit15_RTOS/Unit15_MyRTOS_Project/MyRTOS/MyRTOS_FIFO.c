/*
 * MyRTOS_FIFO.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Aseel
 */

#include "MyRTOS_FIFO.h"

// APIs
FIFO_Status FIFO_Create(FIFO_BUF_t* fifo, element_type* buf, uint32_t length)
{
	if(buf == NULL)
		return FIFO_Null;

	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Enqueue(FIFO_BUF_t* fifo, element_type item)
{
	// check if queue is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	// check if FIFO is full
	if(fifo->count == fifo->length)
		return FIFO_Full;

	// enqueue item
	*(fifo->tail) = item;
	fifo->count++;

	if(fifo->tail == (element_type*)(fifo->base + fifo->length))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Dequeue(FIFO_BUF_t* fifo, element_type* item)
{
	// check if FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	// check if FIFO is empty
	if(fifo->count == 0)
		return FIFO_Empty;

	// dequeue item
	*item = *(fifo->head);
	fifo->count--;

	if(fifo->head == (element_type*)(fifo->base + fifo->length))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Is_Full(FIFO_BUF_t* fifo)
{
	// check if FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	// check if FIFO is full
	if(fifo->count == fifo->length)
		return FIFO_Full;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Is_Empty(FIFO_BUF_t* fifo)
{
	// check if FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	// check if FIFO is empty
	if(fifo->count == 0)
		return FIFO_Empty;

	return FIFO_No_Error;
}

void FIFO_Print(FIFO_BUF_t* fifo)
{
	uint32_t i;
	element_type* temp;

	// check if FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		printf("<<< FIFO Is Not Valid >>>\n");

	// check if FIFO is empty
	else if(fifo->count == 0)
		printf("<<< FIFO Is Empty >>>\n");

	else
	{
		temp = fifo->head;
		printf("<<< Printing FIFO >>>\n");
		for(i = 0; i < fifo->count; i++)
		{
//			printf("\t %d \n", *temp);
			temp++;
		}
	}
}
