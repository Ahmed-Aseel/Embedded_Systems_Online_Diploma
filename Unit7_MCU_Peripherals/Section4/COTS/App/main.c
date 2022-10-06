/*
 * main.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Ahmed Aseel
 */

#include <string.h>
#include "LCD.h"

int main()
{
	char str[] = "Learn In Depth";
	LCD_Init();

	LCD_Write_String((uint8_t*)"Hello Embedded System Diploma");
	_delay_ms(2000);
	LCD_Clear_Screen();
	LCD_Write_String((uint8_t*)"By Eng: Ahmed Aseel");
	_delay_ms(2000);

	LCD_Write_Command(LCD_DISP_ON);
	LCD_Shift_String((uint8_t*)str, strlen(str));

	while(1);

	return 0;
}
