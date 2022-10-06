/*
 * DIO.c
 *
 *  Created on: Oct 5, 2022
 *      Author: Ahmed Aseel
 */

#include "DIO.h"

/***************************** Functions Definition *****************************/

void DIO_SetPinDirection(uint8_t Port_ID, uint8_t Pin_Number, uint8_t Pin_Dir)
{
	if(Pin_Dir == PIN_OUTPUT) // Output
	{
		switch(Port_ID)
		{
		case PORTA_ID: // port A
			Set_Bit(DDRA_REG, Pin_Number);
			break;

		case PORTB_ID: // port B
			Set_Bit(DDRB_REG, Pin_Number);
			break;

		case PORTC_ID: // port C
			Set_Bit(DDRC_REG, Pin_Number);
			break;

		case PORTD_ID:	// port D
			Set_Bit(DDRD_REG, Pin_Number);
			break;
		}
	}

	else if(Pin_Dir == PIN_INPUT) // Input
	{
		switch(Port_ID)
		{
		case PORTA_ID: // port A
			Clr_Bit(DDRA_REG, Pin_Number);
			break;

		case PORTB_ID: // port B
			Clr_Bit(DDRB_REG, Pin_Number);
			break;

		case PORTC_ID: // port C
			Clr_Bit(DDRC_REG, Pin_Number);
			break;

		case PORTD_ID:	// port D
			Clr_Bit(DDRD_REG, Pin_Number);
			break;
		}
	}
}

void DIO_SetPinValue(uint8_t Port_ID, uint8_t Pin_Number, uint8_t Pin_Value)
{
	if(Pin_Value == PIN_HIGH) // High
	{
		switch(Port_ID)
		{
		case PORTA_ID: // port A
			Set_Bit(PORTA_REG, Pin_Number);
			break;

		case PORTB_ID: // port B
			Set_Bit(PORTB_REG, Pin_Number);
			break;

		case PORTC_ID: // port C
			Set_Bit(PORTC_REG, Pin_Number);
			break;

		case PORTD_ID:	// port D
			Set_Bit(PORTD_REG, Pin_Number);
			break;
		}
	}

	else if(Pin_Value == PIN_LOW) // Low
	{
		switch(Port_ID)
		{
		case PORTA_ID: // port A
			Clr_Bit(PORTA_REG, Pin_Number);
			break;

		case PORTB_ID: // port B
			Clr_Bit(PORTB_REG, Pin_Number);
			break;

		case PORTC_ID: // port C
			Clr_Bit(PORTC_REG, Pin_Number);
			break;

		case PORTD_ID:	// port D
			Clr_Bit(PORTD_REG, Pin_Number);
			break;
		}
	}
}

uint8_t DIO_GetPinValue(uint8_t Port_ID, uint8_t Pin_Number)
{
	uint8_t PinVal;
	switch(Port_ID)
	{
	case PORTA_ID: // port A
		PinVal = Read_Bit(PINA_REG, Pin_Number);
		break;

	case PORTB_ID: // port B
		PinVal = Read_Bit(PINB_REG, Pin_Number);
		break;

	case PORTC_ID: // port C
		PinVal = Read_Bit(PINC_REG, Pin_Number);
		break;

	case PORTD_ID:	// port D
		PinVal = Read_Bit(PIND_REG, Pin_Number);
		break;
	}

	return PinVal;
}

void DIO_TogglePin(uint8_t Port_ID, uint8_t Pin_Number)
{
	switch(Port_ID)
	{
	case PORTA_ID: // port A
		Toggle_Bit(PORTA_REG, Pin_Number);
		break;

	case PORTB_ID: // port B
		Toggle_Bit(PORTB_REG, Pin_Number);
		break;

	case PORTC_ID: // port C
		Toggle_Bit(PORTC_REG, Pin_Number);
		break;

	case PORTD_ID:	// port D
		Toggle_Bit(PORTD_REG, Pin_Number);
		break;
	}
}

void DIO_SetPortDirection(uint8_t Port_ID, uint8_t Port_Dir)
{
	switch(Port_ID)
	{
	case PORTA_ID: // port A
		DDRA_REG = Port_Dir;
		break;

	case PORTB_ID: // port B
		DDRB_REG = Port_Dir;
		break;

	case PORTC_ID: // port C
		DDRC_REG = Port_Dir;
		break;

	case PORTD_ID:	// port D
		DDRD_REG = Port_Dir;
		break;
	}
}

void DIO_SetPortValue(uint8_t Port_ID, uint8_t Port_Value)
{
	switch(Port_ID)
	{
	case PORTA_ID: // port A
		PORTA_REG = Port_Value;
		break;

	case PORTB_ID: // port B
		PORTB_REG = Port_Value;
		break;

	case PORTC_ID: // port C
		PORTC_REG = Port_Value;
		break;

	case PORTD_ID:	// port D
		PORTD_REG = Port_Value;
		break;
	}
}
