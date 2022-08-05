/*
 * queue.c
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#include "queue.h"

// APIs
QUEUE_Status QUEUE_Create(QUEUE_BUF_t* queue_buf, element_type* buf, uint32_t length)
{
	if(buf == NULL)
		return QUEUE_Null;

	queue_buf->base = buf;
	queue_buf->head = buf;
	queue_buf->tail = buf;
	queue_buf->length = length;
	queue_buf->count = 0;

	return QUEUE_No_Error;
}

QUEUE_Status QUEUE_Enqueue_Item(QUEUE_BUF_t* queue_buf, element_type item)
{
	// check if queue is valid
	if(!queue_buf->base || !queue_buf->head || !queue_buf->tail)
		return QUEUE_Null;

	// check if queue is full
	if(queue_buf->count == queue_buf->length)
		return QUEUE_Full;

	// enqueue item
	*(queue_buf->tail) = item;
	queue_buf->count++;

	if(queue_buf->tail == (queue_buf->base + queue_buf->length * sizeof(element_type)))
		queue_buf->tail = queue_buf->base;
	else
		queue_buf->tail++;

	return QUEUE_No_Error;
}

QUEUE_Status QUEUE_Dequeue_Item(QUEUE_BUF_t* queue_buf, element_type* item)
{
	// check if queue is valid
	if(!queue_buf->base || !queue_buf->head || !queue_buf->tail)
		return QUEUE_Null;

	// check if queue is empty
	if(queue_buf->count == 0)
		return QUEUE_Empty;

	// dequeue item
	*item = *(queue_buf->head);
	queue_buf->count--;

	if(queue_buf->head == (queue_buf->base + queue_buf->length * sizeof(element_type)))
		queue_buf->head = queue_buf->base;
	else
		queue_buf->head++;

	return QUEUE_No_Error;
}

void QUEUE_Print(QUEUE_BUF_t* queue_buf)
{
	uint32_t i;
	element_type* temp;

	// check if queue is valid
	if(!queue_buf->base || !queue_buf->head || !queue_buf->tail)
		printf("<<< QUEUE Is Not Valid >>>\n");

	// check if queue is empty
	else if(queue_buf->count == 0)
		printf("<<< QUEUE Is Empty >>>\n");

	else
	{
		temp = queue_buf->head;
		printf("<<< Printing QUEUE >>>\n");
		for(i = 0; i < queue_buf->count; i++)
		{
			printf("\t %d \n", *temp);
			temp++;
		}
	}
}
