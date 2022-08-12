/*
 * State.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Aseel
 */

#ifndef STATE_H_
#define STATE_H_

// Automatic State Function Generated

#define State_Define(_StateFun_) void ST_##_StateFun_()
#define State(_StateFun_) ST_##_StateFun_

// States Connection
void US_Set_Distance(int distance);
void DC_Motor_Set_Speed(int speed);

#endif /* STATE_H_ */
