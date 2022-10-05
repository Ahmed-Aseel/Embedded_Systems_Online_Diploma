/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

#include "../GPIO_Driver/STM32F103C6_GPIO_driver.h"
#include "../KeyPad_Driver/KeyPad.h"
#include "../LCD_Driver/LCD.h"

#define ZERO		0x40
#define ONE			0x79
#define TWO			0x24
#define THREE		0x30
#define FOUR		0x19
#define FIVE		0x12
#define SIX			0x02
#define SEVEN		0x78
#define EIGHT		0x00
#define NINE		0x10


void Clock_Init(void)
{
	// IO port A clock enable
	RCC_GPIOA_CLK_EN();
	// IO port B clock enable
	RCC_GPIOB_CLK_EN();
}

void GPIO_Init(void)
{
	uint8_t i;
	GPIO_PinConfig_t *PinCfg = NULL;

	// SET PINS 9:15 PORTB As OUTPUT For 7Seg
	for(i = 9; i < 16; i++)
	{
		// Pin(i) Port B: 00 General purpose output push-pull
		// Pin(i) Port B: 01 Output mode, max speed 10 MHz.
		PinCfg->GPIO_PinNumber = (uint16_t)(1<<i);
		PinCfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg->GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, PinCfg);
	}
}

static void delay_ms(uint8_t time_ms)
{
	uint8_t i,j;
	for(i = 0; i < time_ms; i++)
		for(j = 0; j < 255; j++);
}

int main(void)
{
	uint8_t key_pressed, i;
	uint8_t LCD_Display[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint8_t SevSeg_Display[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

	Clock_Init();
	LCD_Init();

	LCD_Write_String((uint8_t*)"Welcome");
	delay_ms(255);
	LCD_Clear_Screen();

	GPIO_Init();

	for (i = 0; i < 10; i++) {
		LCD_Write_Char(LCD_Display[i]);
		MCAL_GPIO_WritePort(GPIOB, SevSeg_Display[i] << 9);
		delay_ms(100); /* wait for 1 second */
	}

	LCD_Clear_Screen();
	LCD_Write_String((uint8_t*)"KeyPad Is Ready");
	delay_ms(255);
	LCD_Clear_Screen();
	KEYPAD_Init();

	while(1)
	{
		key_pressed = KEYPAD_GetKey();
		switch(key_pressed)
		{
		case 'A':
			break;
		case 'C':
			LCD_Clear_Screen();
			break;
		default:
			LCD_Write_Char(key_pressed);
			break;
		}
	}
	return 0;
}
