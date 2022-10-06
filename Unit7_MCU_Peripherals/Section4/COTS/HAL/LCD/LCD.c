/*
 * LCD.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Ahmed Aseel
 */

#include <stdio.h>
#include "LCD.h"

void LCD_Init()
{
	_delay_ms(20);
	DIO_SetPinDirection(LCD_CONTROL_PORT, RS, PIN_OUTPUT);
	DIO_SetPinDirection(LCD_CONTROL_PORT, RW, PIN_OUTPUT);
	DIO_SetPinDirection(LCD_CONTROL_PORT, EN, PIN_OUTPUT);

	DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_LOW);
	DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
	DIO_SetPinValue(LCD_CONTROL_PORT, EN, PIN_LOW);

	DIO_SetPortDirection(LCD_DATA_PORT, ALLPORTOUTPUT);
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
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_LOW);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		DIO_SetPortValue(LCD_DATA_PORT, command);
		_delay_ms(1);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		volatile uint8_t* DATA_PORT;
		switch(LCD_DATA_PORT)
		{
		case PORTA_ID: // port A
			DATA_PORT = &PORTA_REG;
			break;

		case PORTB_ID: // port B
			DATA_PORT = &PORTB_REG;
			break;

		case PORTC_ID: // port C
			DATA_PORT = &PORTC_REG;
			break;

		case PORTD_ID:	// port D
			DATA_PORT = &PORTD_REG;
			break;
		}
		*DATA_PORT = (*DATA_PORT & 0x0F) | (command & 0xF0);
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_LOW);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		LCD_Kick ();
		*DATA_PORT = (*DATA_PORT & 0x0F) | (command << DATA_SHIFT);
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_LOW);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		LCD_Kick();
	#endif
}

void LCD_Write_Char(uint8_t character)
{
	#ifdef EIGHT_BIT_MODE
		DIO_SetPortValue(LCD_DATA_PORT, character);
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_HIGH);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		volatile uint8_t* DATA_PORT;
		switch(LCD_DATA_PORT)
		{
		case PORTA_ID: // port A
			DATA_PORT = &PORTA_REG;
			break;

		case PORTB_ID: // port B
			DATA_PORT = &PORTB_REG;
			break;

		case PORTC_ID: // port C
			DATA_PORT = &PORTC_REG;
			break;

		case PORTD_ID:	// port D
			DATA_PORT = &PORTD_REG;
			break;
		}
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_HIGH);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		*DATA_PORT = (*DATA_PORT & 0x0F) | (character & 0xF0);
		LCD_Kick();
		DIO_SetPinValue(LCD_CONTROL_PORT, RS, PIN_HIGH);
		DIO_SetPinValue(LCD_CONTROL_PORT, RW, PIN_LOW);
		*DATA_PORT = (*DATA_PORT & 0x0F) | (character << DATA_SHIFT);
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

void LCD_Shift_String(uint8_t* string, uint8_t length)
{
	int8_t i;

	/* This loop to display last i chars
	 * till display whole string
	 * first display last char then last 2 chars
	 * and so on
	 */
	for(i = length - 1; i >= 0; i--)
	{
		LCD_Clear_Screen();
		/******* display last i chars *******/
		LCD_Write_String(string + i);
		_delay_ms(200);
	}

	/* This loop to display and
	 * shift whole string
	 */
	for(i = 1; i <= 16; i++)
	{
		LCD_Clear_Screen();
		/* send cursor to line 2 position i */
		LCD_GOTO_XY(1, i);
		/**** display whole string ****/
		LCD_Write_String(string);
		_delay_ms(200);
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
	DIO_SetPinValue(LCD_CONTROL_PORT, EN, PIN_HIGH);
	_delay_ms(15);
	DIO_SetPinValue(LCD_CONTROL_PORT, EN, PIN_LOW);
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
