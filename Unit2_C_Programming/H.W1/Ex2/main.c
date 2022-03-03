/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to Print a Integer Entered by a User
 *
 */

#include "stdio.h"

int main()
{
	int num;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	printf("You entered: %d\n", num);

	return 0;
}
