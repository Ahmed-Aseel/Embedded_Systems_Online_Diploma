/*
 * main.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#include "CA.h"

void setup()
{
	// init all drivers
	// init IRQ....
	// init HAL US_Driver DC_Driver
	// init Block
	// set states pointers for each Block
	CA_state = State(CA_waiting);
}

int main()
{
	volatile int i;
	setup();
	while(1)
	{
		// call state for each block
		CA_state();
		// delay
		for(i = 0; i < 1000; i++);
	}

	return 0;
}

