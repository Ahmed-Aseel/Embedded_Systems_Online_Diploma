/*
 * main.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Aseel
 *
 *  Description: print the elements of an array
 *  			 in reverse order.
 *
 */

#include "stdio.h"

int main()
{
	int n, i;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	int arr[n];
	printf("Input %d number of elements in the array :\n", n);
	fflush(stdin); fflush(stdout);

	for(i = 0; i < n; i++)
	{
		printf("element -%d : ", i + 1);
		fflush(stdin); fflush(stdout);
		scanf("%d", arr + i);
	}

	printf("\nThe elements of array in reverse order are :\n");
	for(i = n - 1; i >= 0; i--)
	{
		printf("element -%d : %d\n", i + 1, *(arr + i));
	}

	return 0;
}
