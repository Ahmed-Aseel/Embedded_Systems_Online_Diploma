/*
 * CA.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#ifndef CA_H_
#define CA_H_

#include "State.h"

enum
{
	CA_waiting,
	CA_driving

}CA_state_id;

// declare states functions CA
State_Define(CA_waiting);
State_Define(CA_driving);

// State pointer to function
extern void (*CA_state)();

#endif /* CA_H_ */
