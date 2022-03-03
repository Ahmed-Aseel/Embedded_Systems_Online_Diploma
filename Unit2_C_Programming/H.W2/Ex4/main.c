/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to check the number is positive or negative
 */

#include "stdio.h"

int main()
{
	float num;
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &num);
	if(num > 0)
		printf("%f is positive.", num);
	else if(num < 0)
		printf("%f is negative.", num);
	else
		printf("You entered zero");

	return 0;
}
