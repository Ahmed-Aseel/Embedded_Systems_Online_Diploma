/*
 * main.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Aseel
 *
 *  Description: Power of a number using recursion
 */

#include "stdio.h"
int power(int base, int pow);

int main()
{
	int base, pow;
	printf("Enter base number: ");
	fflush(stdin); 	fflush(stdout);
	scanf("%d", &base);
	printf("Enter power number(positive integer): ");
	fflush(stdin); 	fflush(stdout);
	scanf("%d", &pow);
	printf("%d^%d = %d", base, pow, power(base, pow));

	return 0;
}

int power(int base, int pow)
{
	if(pow == 0)
		return 1;

	int result = base * power(base, pow-1);
	return result;
}


