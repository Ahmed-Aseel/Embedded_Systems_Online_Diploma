/*
 * main.c
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#include "stack.h"
// buffer size
#define SIZE 5

int main()
{
	uint32_t i;
	element_type temp;
	element_type uart_buf[SIZE];
	STACK_BUF_t uart_stack, I2C_stack;

	// static allocation
	if( STACK_Create(&uart_stack, uart_buf, SIZE) == STACK_No_Error)
		printf("<<< STACK Creation Is Done >>>\n");

	// dynamic allocation
	element_type* I2C_buf = (element_type*)malloc(SIZE * sizeof(element_type));
	if( STACK_Create(&I2C_stack, I2C_buf, SIZE) == STACK_No_Error)
		printf("<<< STACK Creation Is Done >>>\n");

	printf("<<< Pushing To The STACK >>>\n");
	for(i = 0; i < SIZE; i++)
	{
		if( STACK_Push_Item(&uart_stack, i) == STACK_No_Error )
			printf("UART_STACK push : %d\n", i);
		else
			printf("Failed to push %d\n", i);
	}

	STACK_Print(&uart_stack);

	printf("<<< Popping From The STACK >>>\n");
	for(i = 0; i < SIZE; i++)
	{
		if( STACK_Pop_Item(&uart_stack, &temp) == STACK_No_Error )
			printf("UART_STACK pop : %d\n", temp);
		else
			printf("Failed to pop\n");
	}

	STACK_Print(&uart_stack);

	free(I2C_buf);
	STACK_Print(&I2C_stack);

	return 0;
}
