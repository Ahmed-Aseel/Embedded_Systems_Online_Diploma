/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *	Description: C Program to Multiply two Floating Point Numbers
 */

#include "stdio.h"

int main()
{
	float num1, num2;
	printf("Enter two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num1, &num2);
	printf("product: %f\n", num1 * num2);

	return 0;
}
