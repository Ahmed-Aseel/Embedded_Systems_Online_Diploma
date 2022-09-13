/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Ahmed Aseel
 */

#include <stdint.h>
#include <util/delay.h>

/*********** PORTC Registers ***********/
#define PORTC_REG  *((volatile uint8_t*)0x35)
#define DDRC_REG   *((volatile uint8_t*)0x34)
#define PINC_REG   *((volatile uint8_t*)0x33)

/*******************************************************************************************/
						  /**** Direction I/O Initialization ****/
void DIO_Init()
{
	/* set  pins 2:7 PortC direction as output */
	DDRC_REG = 0xFC;
}

int main()
{
	uint8_t i, j;
	DIO_Init();

	while(1)
	{
		for(i = 0; i < 10; i++)
		{
			PORTC_REG = 0b1000 | (i<<4);
			_delay_ms(600);

			for(j = 0; j < 10; j++)
			{
				PORTC_REG = 0b0100 | (j<<4);
				_delay_ms(400);
			}
		}
	}

	return 0;
}
