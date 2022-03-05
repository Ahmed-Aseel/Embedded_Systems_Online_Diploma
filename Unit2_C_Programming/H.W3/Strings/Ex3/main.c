/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to reverse a string
 */

#include "stdio.h"
#include "string.h"

int main()
{
	char str[25];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	printf("Reverse string: ");
	int i;
	for(i = strlen(str)-1; i >= 0; i--)
	{
		printf("%c", str[i]);
	}

	return 0;
}
