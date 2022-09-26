/*
 * LCD.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#include <stdio.h>
#include "LCD.h"

void LCD_Init()
{
	_delay_ms(20);
	LCD_CONTROL_DIR |= (1<<EN | 1<<RS | 1<<RW);
	LCD_CONTROL_PORT &= ~ (1<<EN | 1<<RS | 1<<RW);
	LCD_DATA_DIR = 0xFF;
	_delay_ms(15);
	LCD_Clear_Screen();

	#ifdef EIGHT_BIT_MODE
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_Write_Command(0x02);
	LCD_Write_Command(LCD_FUNCTION_4BIT_2LINES);
	#endif

	LCD_Write_Command(LCD_ENTRY_MODE);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_Write_Command(uint8_t command)
{
	#ifdef EIGHT_BIT_MODE
		LCD_CONTROL_PORT &= ~((1 << RS) | (1<<RW));
		LCD_DATA_PORT = command;
		_delay_ms(1);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		LCD_CONTROL_PORT &= ~ ((1<<RW)|(1<<RS));
		LCD_Kick ();
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command << DATA_SHIFT);
		LCD_CONTROL_PORT &= ~ ((1<<RW)|(1<<RS));
		LCD_Kick();
	#endif
}

void LCD_Write_Char(uint8_t character)
{
	#ifdef EIGHT_BIT_MODE
		LCD_DATA_PORT = character;
		LCD_CONTROL_PORT &= ~(1 << RW);
		LCD_CONTROL_PORT |= (1 << RS);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		LCD_CONTROL_PORT |= 1<<RS;     //turn RS ON for Data mode.
		LCD_CONTROL_PORT &= ~ (1<<RW); //turn RW off so you can write.
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character & 0xF0);
		LCD_Kick();
		LCD_CONTROL_PORT |= 1<<RS;     //turn RS ON for Data mode.
		LCD_CONTROL_PORT &= ~ (1<<RW); //turn RW off so you can write.
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character << DATA_SHIFT);
		LCD_Kick ();
	#endif
}

void LCD_Write_String(uint8_t* string)
{
	uint8_t count = 0;
	while (*string)
	{
		count++;
		LCD_Write_Char(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_Clear_Screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}

void LCD_Write_Number(uint16_t number)
{
	uint8_t str[10];
	sprintf((char*)str, "%u", number);
	LCD_Write_String(str);
}

void LCD_Write_RealNumber(float number)
{
	uint8_t str[15];
	char* tmpSign = (number < 0) ? "-" : "";
	float tmpVal = (number < 0) ? -number : number;

	uint16_t tmpInt1 = tmpVal;            //Get integer value
	float tmpFrac = tmpVal - tmpInt1;	  //Get fraction value
	uint16_t tmpInt2 = tmpFrac * 10000;   //Turn fraction into integer

	sprintf((char*)str, "%s%d.%4d", tmpSign, tmpInt1, tmpInt2);
	LCD_Write_String(str);
}

void LCD_Kick(){
	LCD_CONTROL_PORT |= (1 << EN);
	_delay_ms(5);
	LCD_CONTROL_PORT &= ~(1 << EN);
}

void LCD_Clear_Screen()
{
	LCD_Write_Command(LCD_CLEAR_SCREEN);
}

void LCD_GOTO_XY(uint8_t line, uint8_t position)
{
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}
