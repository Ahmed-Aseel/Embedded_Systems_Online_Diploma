/*
 * BitMath.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

/********** Header Protection **********/
#ifndef BITMATH_H_
#define BITMATH_H_

#define Read_Bit(reg, bit)   ((reg >> bit) & 1)
#define Clr_Bit(reg, bit)    (reg &= ~(1 << bit))
#define Set_Bit(reg, bit)    (reg |= (1 << bit))
#define Toggle_Bit(reg, bit) (reg ^= (1 << bit))

#endif /******** BITMATH_H_ ********/
