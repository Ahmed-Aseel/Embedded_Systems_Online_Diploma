/*
 * KeyPad.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Ahmed Aseel
 */

#include "KeyPad.h"

int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3}; //columns

void KEYPAD_Init()
{
	KEYPAD_DATA_DIR &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
	KEYPAD_DATA_DIR |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
	KEYPAD_PORT = 0xFF;
}

uint8_t KEYPAD_GetKey()
{
	uint8_t i,j;
	for (i = 0; i < 4; i++)
	{
		KEYPAD_PORT |= ((1<<Key_padCol[0]) | (1<<Key_padCol[1]) | (1<<Key_padCol[2]) | (1<<Key_padCol[3]));
		KEYPAD_PORT &= ~(1<<Key_padCol[i]);
		for(j = 0; j < 4; j++)
		{
			if (!(KEYPAD_PIN & (1 << Key_padRow[j])))
			{
				while(!(KEYPAD_PIN & (1 << Key_padRow[j])));
				switch(i)
				{
				case 0:
					if 		(j == 0) return '7';
					else if (j == 1) return '4';
					else if (j == 2) return '1';
					else if (j == 3) return 'C';
					break;

				case 1:
					if 		(j == 0) return '8';
					else if (j == 1) return '5';
					else if (j == 2) return '2';
					else if (j == 3) return '0';
					break;

				case 2:
					if 		(j == 0) return '9';
					else if (j == 1) return '6';
					else if (j == 2) return '3';
					else if (j == 3) return '=';
					break;

				case 3:
					if 		(j == 0) return '/';
					else if (j == 1) return '*';
					else if (j == 2) return '-';
					else if (j == 3) return '+';
					break;
				}
			}
		}
	}

	return 'A';
}
