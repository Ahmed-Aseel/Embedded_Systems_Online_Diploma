/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to calculate the sum of natural numbers
 */

#include "stdio.h"

int main()
{
	int n;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	int i, sum = 0;
	for(i = 1; i <= n; i++)
	{
		sum += i;
	}
	printf("Sum = %d", sum);
	return 0;
}
