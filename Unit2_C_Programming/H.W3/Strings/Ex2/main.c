/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: aseel
 *
 *  Description: C program to find the length of a string
 */

#include "stdio.h"

int main()
{
	char str[25];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	int i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	printf("Length of string = %d", i);

	return 0;
}
