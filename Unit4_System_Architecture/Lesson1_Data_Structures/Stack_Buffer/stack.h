/*
 * stack.h
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#ifndef STACK_H_
#define STACK_H_

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

}STACK_BUF_t;

typedef enum
{
	STACK_No_Error,
	STACK_Full,
	STACK_Empty,
	STACK_Null

}STACK_Status;

// APIs
STACK_Status STACK_Create(STACK_BUF_t* stack_buf, element_type* buf, uint32_t length);
STACK_Status STACK_Push_Item(STACK_BUF_t* stack_buf, element_type item);
STACK_Status STACK_Pop_Item(STACK_BUF_t* stack_buf, element_type* item);
void STACK_Print(STACK_BUF_t* stack_buf);

#endif /* STACK_H_ */
