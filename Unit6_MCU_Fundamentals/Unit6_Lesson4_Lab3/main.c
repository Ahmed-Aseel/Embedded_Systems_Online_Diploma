/*
 * main.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Ahmed Aseel
 */

#include<stdint.h>

/*********** PORTD Registers ***********/
#define PORTD_REG  *((volatile uint8_t*)0x32)
#define DDRD_REG   *((volatile uint8_t*)0x31)

/*********  Status Register  *********/
#define SREG_REG  *((volatile uint8_t*)0x5F)

/** General Interrupt Control Register **/
#define GICR_REG     *((volatile uint8_t*)0x5B)

/********* MCU Control Register *********/
#define MCUCR_REG    *((volatile uint8_t*)0x55)

/*******************************************************************************************/
						  /**** Direction I/O Initialization ****/
void DIO_Init()
{
	/* set pin0 PortD direction as output */
	DDRD_REG |= (1<<0);
	// write 0V at pin0 PortD
	PORTD_REG &= ~(1<<0);

	/* set intr0 pin PortD direction as input */
	DDRD_REG &= ~(1<<2);
}

int main()
{
	DIO_Init();

	//ANY_CHANGE 01
	MCUCR_REG |= (1<<0);
	MCUCR_REG &= ~(1<<1);

	// enable global interrupt
	SREG_REG |= (1<<7);

	// enable INTR0
	GICR_REG |= (1<<6);

	while(1);

	return 0;
}

/*******************************************************************************************/
								/**** INTR0 VECTOR ****/
void __vector_1()__attribute__((signal));
void __vector_1()
{
	// toggle led on pin0 portD
	PORTD_REG ^= (1<<0);
}
