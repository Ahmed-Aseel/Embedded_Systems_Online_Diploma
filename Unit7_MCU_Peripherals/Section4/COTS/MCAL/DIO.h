/*
 * DIO.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Ahmed Aseel
 */

#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

/*********** PORTA Registers ***********/
#define PORTA_REG	  *((volatile uint8_t*)0x3B)
#define DDRA_REG 	  *((volatile uint8_t*)0x3A)
#define PINA_REG 	  *((volatile uint8_t*)0x39)

/*********** PORTB Registers ***********/
#define PORTB_REG	  *((volatile uint8_t*)0x38)
#define DDRB_REG 	  *((volatile uint8_t*)0x37)
#define PINB_REG 	  *((volatile uint8_t*)0x36)

/*********** PORTC Registers ***********/
#define PORTC_REG	  *((volatile uint8_t*)0x35)
#define DDRC_REG 	  *((volatile uint8_t*)0x34)
#define PINC_REG 	  *((volatile uint8_t*)0x33)

/*********** PORTD Registers ***********/
#define PORTD_REG	  *((volatile uint8_t*)0x32)
#define DDRD_REG 	  *((volatile uint8_t*)0x31)
#define PIND_REG 	  *((volatile uint8_t*)0x30)

/*** PORTS ID Macros ***/
#define PORTA_ID  	  0x00
#define PORTB_ID  	  0x01
#define PORTC_ID  	  0x02
#define PORTD_ID  	  0x03

/*** PINS ID Macros ***/
#define PIN0_ID  	  0x00
#define PIN1_ID  	  0x01
#define PIN2_ID  	  0x02
#define PIN3_ID  	  0x03
#define PIN4_ID  	  0x04
#define PIN5_ID  	  0x05
#define PIN6_ID  	  0x06
#define PIN7_ID  	  0x07

/*** PIN Direction Macros ***/
#define PIN_INPUT     	0x00
#define PIN_OUTPUT    	0x01

/** PIN Output Values **/
#define PIN_LOW   	  	0x00
#define PIN_HIGH  	  	0x01

/*** PORT Output Value ***/
#define ALLPORTINPUT  	0x00
#define ALLPORTOUTPUT	0xFF

#define Read_Bit(reg, bit)   	((reg >> bit) & 1)
#define Clr_Bit(reg, bit)    	(reg &= ~(1 << bit))
#define Set_Bit(reg, bit)    	(reg |= (1 << bit))
#define Toggle_Bit(reg, bit)	(reg ^= (1 << bit))

/***************************** Functions Prototype *****************************/
void DIO_SetPinDirection(uint8_t Port_ID, uint8_t Pin_Number, uint8_t Pin_Dir);
void DIO_SetPinValue(uint8_t Port_ID, uint8_t Pin_Number, uint8_t Pin_Value);
uint8_t DIO_GetPinValue(uint8_t Port_ID, uint8_t Pin_Number);
void DIO_TogglePin(uint8_t Port_ID, uint8_t Pin_Number);
void DIO_SetPortDirection(uint8_t Port_ID, uint8_t Port_Dir);
void DIO_SetPortValue(uint8_t Port_ID, uint8_t Port_Value);

#endif /* DIO_H_ */
