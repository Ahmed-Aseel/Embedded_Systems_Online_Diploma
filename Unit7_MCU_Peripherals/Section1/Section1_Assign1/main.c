/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Ahmed Aseel
 */

#include <stdint.h>
#include <util/delay.h>

/*********** PORTD Registers ***********/
#define PORTD_REG  *((volatile uint8_t*)0x32)
#define DDRD_REG   *((volatile uint8_t*)0x31)
#define PIND_REG   *((volatile uint8_t*)0x30)

/*******************************************************************************************/
						  /**** Direction I/O Initialization ****/
void DIO_Init()
{
	/* set pins 5,6,7 PortD direction as output */
	DDRD_REG |= (7<<5);
}

int main()
{
	uint8_t i;
	DIO_Init();
	for(i = 5; i < 8; i++)
	{
		PORTD_REG |= (1<<i);
		_delay_ms(500);
	}

	for(i = 7; i > 4; i--)
	{
		PORTD_REG &= ~(1<<i);
		_delay_ms(500);
	}

	while(1)
	{
		if((PIND_REG & 1) == 1)
		{
			PORTD_REG |= (1<<5);
		}
		else
		{
			PORTD_REG &= ~(1<<5);
		}

		if((PIND_REG & 3) == 3)
		{
			PORTD_REG |= (1<<6);
		}
		else
		{
			PORTD_REG &= ~(1<<6);
		}

		if((PIND_REG & 7) == 7)
		{
			PORTD_REG |= (1<<7);
		}
		else
		{
			PORTD_REG &= ~(1<<7);
		}

	}

	return 0;
}
