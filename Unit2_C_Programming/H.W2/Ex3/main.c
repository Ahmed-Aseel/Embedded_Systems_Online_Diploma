/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to find the largest number
 */

#include "stdio.h"

int main()
{
	float num1, num2, num3;
	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f", &num1, &num2, &num3);

	if(num1 > num2)
	{
		if(num1 > num3)
			printf("Largest number = %f", num1);
		else
			printf("Largest number = %f", num3);
	}

	else
	{
		if(num2 > num3)
			printf("Largest number = %f", num2);
		else
			printf("Largest number = %f", num3);
	}

	return 0;
}

