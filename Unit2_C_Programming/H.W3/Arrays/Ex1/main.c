/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to calculate Sum of 2-D arrays (2x2)
 */

#include "stdio.h"

int main()
{
	float a[2][2];
	float b[2][2];
	int i, j;
	printf("Enter the elements of the 1st matrix\n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j <2; j++)
		{
			printf("Enter a%d%d: ", i+1, j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f", &a[i][j]);
		}
	}

	printf("Enter the elements of the 2nd matrix\n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			printf("Enter b%d%d: ", i+1, j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f", &b[i][j]);
		}
	}

	printf("Sum of the matrices:\n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			float sum = a[i][j] + b[i][j];
			printf("%f  ", sum);
		}
		printf("\n");
	}

	return 0;
}
