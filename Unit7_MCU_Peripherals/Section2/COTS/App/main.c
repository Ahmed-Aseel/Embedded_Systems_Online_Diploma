/*
 * main.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#include "LCD.h"
#include "KeyPad.h"

int main()
{
	uint8_t key_pressed;

	LCD_Init();
	KEYPAD_Init();

	LCD_Write_String((uint8_t*)"Hello Embedded System Diploma");
	_delay_ms(2000);
	LCD_Clear_Screen();
	LCD_Write_String((uint8_t*)"By Eng: Ahmed Aseel");
	_delay_ms(2000);
	LCD_Clear_Screen();
	LCD_Write_String((uint8_t*)"Numbers Examples");
	LCD_Write_RealNumber(-85.45);
	LCD_Write_String((uint8_t*)"   ");
	LCD_Write_Number(5678);
	_delay_ms(2000);
	LCD_Clear_Screen();
	LCD_Write_String((uint8_t*)"Use KeyPad");
	_delay_ms(2000);
	LCD_Clear_Screen();

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
