/*
 * LCD.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA_PORT			PORTA
#define LCD_DATA_DIR			DDRA
#define LCD_CONTROL_PORT		PORTB
#define LCD_CONTROL_DIR			DDRB

#define RS				0
#define RW				1
#define EN				2
#define DATA_SHIFT		4  // data shift = 4 in 4-bit mode

//#define FOUR_BIT_MODE
#define EIGHT_BIT_MODE

#define LCD_CLEAR_SCREEN						0x01
#define LCD_RETURN_HOME     					0x02
#define LCD_ENTRY_DEC   						0x04
#define LCD_ENTRY_DEC_SHIFT   					0x05
#define LCD_ENTRY_MODE							0x06
#define LCD_ENTRY_INC_SHIFT   					0x07
#define LCD_DISP_OFF   							0x08
#define LCD_DISP_ON   							0x0C
#define LCD_DISP_ON_BLINK   					0x0D
#define LCD_DISP_ON_CURSOR   					0x0E
#define LCD_DISP_ON_CURSOR_BLINK   				0x0F
#define LCD_MOVE_CURSOR_LEFT 	  				0x10
#define LCD_MOVE_CURSOR_RIGHT   				0x14
#define LCD_MOVE_DISP_LEFT   					0x18
#define LCD_MOVE_DISP_RIGHT       				0x1C
#define LCD_FUNCTION_4BIT_2LINES   				0x28
#define LCD_FUNCTION_8BIT_2LINES				0x38
#define LCD_RESET           					0x30
#define LCD_BEGIN_AT_FIRST_ROW					0x80
#define LCD_BEGIN_AT_SECOND_ROW					0xC0


void LCD_Init();
void LCD_Write_Command(uint8_t command);
void LCD_Write_Char(uint8_t character);
void LCD_Write_String(uint8_t* string);
void LCD_Write_Number(uint16_t number);
void LCD_Write_RealNumber(float number);
void LCD_Kick(void);
void LCD_Clear_Screen();
void LCD_GOTO_XY(uint8_t line, uint8_t position);

#endif /* LCD_H_ */
