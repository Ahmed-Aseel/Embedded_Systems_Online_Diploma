/*
 * main.c
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#include "queue.h"
// buffer size
#define SIZE 5

int main()
{
	uint32_t i;
	element_type temp;
	element_type uart_buf[SIZE];
	QUEUE_BUF_t uart_queue, I2C_queue;

	// static allocation
	if( QUEUE_Create(&uart_queue, uart_buf, SIZE) == QUEUE_No_Error)
		printf("<<< QUEUE Creation Is Done >>>\n");

	// dynamic allocation
	element_type* I2C_buf = (element_type*)malloc(SIZE * sizeof(element_type));
	if( QUEUE_Create(&I2C_queue, I2C_buf, SIZE) == QUEUE_No_Error)
		printf("<<< QUEUE Creation Is Done >>>\n");

	printf("<<< Enqueue To The QUEUE >>>\n");
	for(i = 0; i < SIZE; i++)
	{
		if( QUEUE_Enqueue_Item(&uart_queue, i) == QUEUE_No_Error )
			printf("uart_queue enqueue : %d\n", i);
		else
			printf("Failed to enqueue %d\n", i);
	}

	QUEUE_Print(&uart_queue);

	printf("<<< Dequeue From The QUEUE >>>\n");
	for(i = 0; i < SIZE; i++)
	{
		if( QUEUE_Dequeue_Item(&uart_queue, &temp) == QUEUE_No_Error )
			printf("uart_queue dequeue : %d\n", temp);
		else
			printf("Failed to dequeue\n");
	}

	QUEUE_Print(&uart_queue);

	free(I2C_buf);
	QUEUE_Print(&I2C_queue);


	return 0;
}
