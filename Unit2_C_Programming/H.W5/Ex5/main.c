/*
 * main.c
 *
 *  Created on: Mar 19, 2022
 *      Author: Aseel
 *
 *  Description: Area of a circle by passing
 *  			 argument to macros
 */

#include "stdio.h"
#include "math.h"
#define area(r) M_PI*r*r

int main()
{
	float rad;
	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &rad);
	printf("\nArea = %0.2f", area(rad));

	return 0;
}
