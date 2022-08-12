/*
 * US.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#include <stdio.h>
#include <stdlib.h>
#include "US.h"

// variables
int  US_distance = 0;

int US_Get_Rand_Distance(int min, int max);
// State pointer to function
void (*US_state)();

// functions definition

void US_init()
{
	// init US Driver
	printf("<< US_init >>\n");
}

State_Define(US_busy)
{
	// state name
	US_state_id = US_busy;

	// state action
	US_distance = US_Get_Rand_Distance(45,55);
	printf("US_busy State: distance = %d \n", US_distance);

	US_Set_Distance(US_distance);
	US_state = State(US_busy);
}

int US_Get_Rand_Distance(int low, int high)
{
	// this will generate random number between low & high
	int rand_dis = (rand() % (high - low + 1)) + low;
	return rand_dis;
}
