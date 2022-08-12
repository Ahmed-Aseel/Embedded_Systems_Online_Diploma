/*
 * CA.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#include <stdio.h>
#include <stdlib.h>
#include "CA.h"

// variables
int CA_speed = 0, CA_distance = 0, CA_threshold = 50;

int US_Get_Rand_Distance(int min, int max);
// State pointer to function
void (*CA_state)();

// functions definition
State_Define(CA_waiting)
{
	// state name
	CA_state_id = CA_waiting;

	// state action
	CA_speed = 0;
	// DC_Motor(CA_speed);

	// event check
	CA_distance = US_Get_Rand_Distance(45,55);
	(CA_distance <= 50)? (CA_state = State(CA_waiting)) : (CA_state = State(CA_driving));
	printf("CA_waiting State: distance = %d  speed = %d\n", CA_distance, CA_speed);
}

State_Define(CA_driving)
{
	// state name
	CA_state_id = CA_driving;

	// state action
	CA_speed = 30;
	// DC_Motor(CA_speed);

	// event check
	CA_distance = US_Get_Rand_Distance(45,55);
	(CA_distance <= 50)? (CA_state = State(CA_waiting)) : (CA_state = State(CA_driving));
	printf("CA_driving State: distance = %d  speed = %d\n", CA_distance, CA_speed);
}

int US_Get_Rand_Distance(int low, int high)
{
	// this will generate random number between low & high
	int rand_dis = (rand() % (high - low + 1)) + low;
	return rand_dis;
}
