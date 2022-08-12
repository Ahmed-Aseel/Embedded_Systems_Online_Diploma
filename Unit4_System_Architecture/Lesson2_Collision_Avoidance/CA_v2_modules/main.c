/*
 * main.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	// init all drivers
	// init IRQ....
	// init HAL US_Driver DC_Driver
	// init Block
	US_init();
	DC_init();
	// set states pointers for each Block
	CA_state = State(CA_waiting);
	US_state = State(US_busy);
	DC_state = State(DC_idle);
}

int main()
{
	volatile int i;
	setup();
	while(1)
	{
		// call state for each block
		US_state();
		CA_state();
		DC_state();
		// delay
		for(i = 0; i < 1000; i++);
	}

	return 0;
}

