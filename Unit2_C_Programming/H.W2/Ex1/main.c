/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to check whether a number
 *  			 is even or odd
 */

#include "stdio.h"

int main()
{
	int num;
	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	if(num % 2 == 0)
		printf("%d is even.", num);
	else
		printf("%d is odd.", num);

	return 0;
}
