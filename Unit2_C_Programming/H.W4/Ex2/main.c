/*
 * main.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Aseel
 *
 *  Description: Factorial of a number using recursion
 */

#include "stdio.h"
int factorial(int num);

int main()
{
	int num;
	printf("Enter a positive integer: ");
	fflush(stdin); 	fflush(stdout);
	scanf("%d", &num);
	printf("Factorial of %d = %d ", num, factorial(num));

	return 0;
}

int factorial(int num)
{
	if(num < 2)
		return 1;

	int fact = num * factorial(num - 1);
	return fact;
}
