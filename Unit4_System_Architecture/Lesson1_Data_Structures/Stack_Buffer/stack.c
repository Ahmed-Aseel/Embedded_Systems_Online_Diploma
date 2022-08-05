/*
 * stack.c
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#include "stack.h"

// APIs
STACK_Status STACK_Create(STACK_BUF_t* stack_buf, element_type* buf, uint32_t length)
{
	if(buf == NULL)
		return STACK_Null;

	stack_buf->base = buf;
	stack_buf->head = buf;
	stack_buf->length = length;
	stack_buf->count = 0;

	return STACK_No_Error;
}

STACK_Status STACK_Push_Item(STACK_BUF_t* stack_buf, element_type item)
{
	// check if stack is valid
	if(!stack_buf->base || !stack_buf->head)
		return STACK_Null;

	// check if stack is full
	if(stack_buf->count == stack_buf->length)
		return STACK_Full;

	// push item
	*(stack_buf->head) = item;
	stack_buf->head++;
	stack_buf->count++;

	return STACK_No_Error;
}

STACK_Status STACK_Pop_Item(STACK_BUF_t* stack_buf, element_type* item)
{
	// check if stack is valid
	if(!stack_buf->base || !stack_buf->head)
		return STACK_Null;

	// check if stack is empty
	if(stack_buf->count == 0)
		return STACK_Empty;

	// pop item
	stack_buf->head--;
	stack_buf->count--;
	*item = *(stack_buf->head);

	return STACK_No_Error;
}

void STACK_Print(STACK_BUF_t* stack_buf)
{
	uint32_t i;
	element_type* temp;

	// check if stack is valid
	if(!stack_buf->base || !stack_buf->head)
		printf("<<< STACK Is Not Valid >>>\n");

	// check if stack is empty
	else if(stack_buf->count == 0)
		printf("<<< STACK Is Empty >>>\n");

	else
	{
		temp = stack_buf->head - 1;
		printf("<<< Printing STACK >>>\n");
		for(i = 0; i < stack_buf->count; i++)
		{
			printf("\t %d \n", *temp);
			temp--;
		}
	}
}
