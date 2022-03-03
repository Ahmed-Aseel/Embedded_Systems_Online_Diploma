/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to Find ASCII Value of a Character
 */

#include "stdio.h"

int main()
{
	char character;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &character);
	printf("ASCII value of %c = %d\n", character, character);

	return 0;
}
