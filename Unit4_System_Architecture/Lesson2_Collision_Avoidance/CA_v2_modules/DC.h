/*
 * DC.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#ifndef DC_H_
#define DC_H_

#include "State.h"

enum
{
	DC_idle,
	DC_busy

}DC_state_id;

// declare states functions DC
State_Define(DC_idle);
State_Define(DC_busy);

// init func
void DC_init();

// State pointer to function
extern void (*DC_state)();

#endif /* DC_H_ */
