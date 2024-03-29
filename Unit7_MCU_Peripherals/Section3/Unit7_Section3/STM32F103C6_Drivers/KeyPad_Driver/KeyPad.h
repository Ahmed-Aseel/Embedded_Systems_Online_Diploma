/*
 * KeyPad.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_driver.h"

#define KEYPAD_PORT					GPIOB

#define R0		GPIO_PIN_0
#define R1		GPIO_PIN_1
#define R2		GPIO_PIN_3
#define R3		GPIO_PIN_4
#define C0		GPIO_PIN_5
#define C1		GPIO_PIN_6
#define C2		GPIO_PIN_7
#define C3		GPIO_PIN_8

void KEYPAD_Init();
uint8_t KEYPAD_GetKey();

#endif /* KEYPAD_H_ */
