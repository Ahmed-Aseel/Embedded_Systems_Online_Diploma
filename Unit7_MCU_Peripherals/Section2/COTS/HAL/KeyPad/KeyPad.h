/*
 * KeyPad.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include<avr/io.h>
#include<util/delay.h>

#define KEYPAD_PORT					PORTD
#define KEYPAD_DATA_DIR				DDRD
#define KEYPAD_PIN					PIND

#define R0		0
#define R1		1
#define R2		2
#define R3		3
#define C0		4
#define C1		5
#define C2		6
#define C3		7

void KEYPAD_Init();
uint8_t KEYPAD_GetKey();

#endif /* KEYPAD_H_ */
