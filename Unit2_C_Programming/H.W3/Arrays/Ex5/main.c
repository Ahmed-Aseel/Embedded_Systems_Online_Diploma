/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to search an element in an array
 */

#include "stdio.h"

int main()
{
	int n, i, num;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	int arr[n];

	for(i = 0; i < n; i++)
	{
		fflush(stdin); fflush(stdout);
		scanf("%d", &arr[i]);
	}

	printf("Enter the element to be searched: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	for(i = 0; i < n; i++)
	{
		if(arr[i] == num)
		{
			printf("Number found at the location = %d", i+1);
			break;
		}
	}
	if(i == n)
		printf("Number not found");
	return 0;
}
