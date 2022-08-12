/*
 * DC.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#include <stdio.h>
#include <stdlib.h>
#include "DC.h"

// variables
int DC_speed = 0;

// State pointer to function
void (*DC_state)();

// functions definition

void DC_init()
{
	// init PWM
	printf("<< DC_init >>\n");
}

void DC_Motor_Set_Speed(int speed)
{
	DC_speed = speed;
	DC_state = State(DC_busy);
	printf("CA -------- speed = %d --------> DC \n", DC_speed);
}

State_Define(DC_idle)
{
	// state name
	DC_state_id = DC_idle;

	// state action
	// call PWM to make speed = DC_speed

	printf("DC_idle State: speed = %d\n", DC_speed);
}

State_Define(DC_busy)
{
	// state name
	DC_state_id = DC_busy;

	// state action
	// call PWM to make speed = DC_speed

	DC_state = State(DC_idle);
	printf("DC_busy State: speed = %d\n", DC_speed);
}
