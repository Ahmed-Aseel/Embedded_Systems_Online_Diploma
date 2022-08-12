/*
 * US.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#ifndef US_H_
#define US_H_

#include "State.h"

enum
{
	US_busy

}US_state_id;

// declare states functions US
State_Define(US_busy);

// init func
void US_init();

// State pointer to function
extern void (*US_state)();

#endif /* US_H_ */
