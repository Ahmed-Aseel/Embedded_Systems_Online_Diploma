/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: metro
 *
 *  Description: C program to calculate the average using arrays
 */

#include "stdio.h"

int main()
{
	int n, i;
	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	float arr[n];
	float sum = 0.0;
	for(i = 0; i < n; i++)
	{
		printf("Enter number: ");
		fflush(stdin); fflush(stdout);
		scanf("%f", &arr[i]);
		sum += arr[i];
	}
	printf("Average = %f", sum / n);

	return 0;
}
