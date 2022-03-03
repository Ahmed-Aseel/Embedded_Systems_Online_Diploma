/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to find the factorial of a number
 */

#include "stdio.h"
#include "stdlib.h"

int main()
{
	int n;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	if(n < 0)
	{
		printf("Error!! Factorial of negative numbers doesn\'t exist");
		exit(0);
	}
	int i, fact = 1;
	for(i = 2; i <= n; i++)
	{
		fact *= i;
	}
	printf("Factorial = %d", fact);

	return 0;
}
