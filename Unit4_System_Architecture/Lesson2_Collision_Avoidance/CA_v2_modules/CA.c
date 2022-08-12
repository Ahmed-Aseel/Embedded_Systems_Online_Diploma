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

// State pointer to function
void (*CA_state)();

// functions definition
void US_Set_Distance(int distance)
{
	CA_distance = distance;
	(CA_distance <= 50)? (CA_state = State(CA_waiting)) : (CA_state = State(CA_driving));
	printf("US -------- distance = %d --------> CA \n", CA_distance);
}

State_Define(CA_waiting)
{
	// state name
	CA_state_id = CA_waiting;

	// state action
	CA_speed = 0;
	printf("CA_waiting State: distance = %d  speed = %d\n", CA_distance, CA_speed);

	// DC_Motor(CA_speed);
	DC_Motor_Set_Speed(CA_speed);
}

State_Define(CA_driving)
{
	// state name
	CA_state_id = CA_driving;

	// state action
	CA_speed = 30;
	printf("CA_driving State: distance = %d  speed = %d\n", CA_distance, CA_speed);

	// DC_Motor(CA_speed);
	DC_Motor_Set_Speed(CA_speed);
}
