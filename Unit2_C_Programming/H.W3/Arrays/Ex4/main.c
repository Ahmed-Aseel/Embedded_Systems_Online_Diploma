/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to insert an element in an array
 */

#include "stdio.h"
#include "stdlib.h"

int main()
{
	int n, i, num, loc;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	int arr[n+1];

	for(i = 0; i < n; i++)
	{
		fflush(stdin); fflush(stdout);
		scanf("%d", &arr[i]);
	}

	printf("Enter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	printf("Enter the location: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &loc);
	if(loc < 1 || loc > n+1)
	{
		printf("Invalid location!!");
		exit(0);
	}

	for(i = n; i >= loc; i--)
	{
		arr[i] = arr[i-1];
	}

	arr[i] = num;
	for(i = 0; i < n+1; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}
