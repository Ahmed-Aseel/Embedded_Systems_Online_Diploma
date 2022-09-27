/*
 * LCD.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#include <stdio.h>
#include "LCD.h"

static GPIO_PinConfig_t *PinCfg = NULL;

static void delay_ms(uint8_t time_ms)
{
	uint8_t i,j;
	for(i = 0; i < time_ms; i++)
		for(j = 0; j < 255; j++);
}

void LCD_Init()
{
	uint8_t i;
	delay_ms(20);

	// Pin8 Port A: 00 General purpose output push-pull
	// Pin8 Port A: 01 Output mode, max speed 10 MHz.
	PinCfg->GPIO_PinNumber = RS;
	PinCfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, PinCfg);

	// Pin9 Port A: 00 General purpose output push-pull
	// Pin* Port A: 01 Output mode, max speed 10 MHz.
	PinCfg->GPIO_PinNumber = RW;
	PinCfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, PinCfg);

	// Pin10 Port A: 00 General purpose output push-pull
	// Pin10 Port A: 01 Output mode, max speed 10 MHz.
	PinCfg->GPIO_PinNumber = EN;
	PinCfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, PinCfg);

	// RESET RS, RW, EN
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN, GPIO_PIN_RESET);

	// SET PINS 0:7 AS OUTPUT For LCD Data
	for(i = 0; i < 8; i++)
	{
		// Pin(i) LCD_DATA_PORT: 00 General purpose output push-pull
		// Pin(i) LCD_DATA_PORT: 01 Output mode, max speed 10 MHz.
		PinCfg->GPIO_PinNumber = (uint16_t)(1<<i);
		PinCfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg->GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(LCD_DATA_PORT, PinCfg);
	}

	delay_ms(15);
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
		MCAL_GPIO_WritePort(LCD_DATA_PORT, command);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
		delay_ms(1);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
		LCD_Kick ();
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command << DATA_SHIFT);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
		LCD_Kick();
	#endif
}

void LCD_Write_Char(uint8_t character)
{
	#ifdef EIGHT_BIT_MODE
		MCAL_GPIO_WritePort(LCD_DATA_PORT, character);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
		delay_ms(1);
		LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character & 0xF0);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
		LCD_Kick();
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character << DATA_SHIFT);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
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
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN, GPIO_PIN_SET);
	delay_ms(5);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN, GPIO_PIN_RESET);
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
