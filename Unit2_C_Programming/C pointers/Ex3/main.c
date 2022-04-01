/*
 * main.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Aseel
 *
 *  Description: print a string in reverse using a pointer
 *
 */

#include "stdio.h"
#include "string.h"

int main()
{
	char str[15];
	int i;
	printf("Input a string : ");
	fflush(stdin); fflush(stdout);
	scanf("%s", str);
	printf("Reverse of the string is : ");
	for(i = strlen(str) - 1; i >= 0; i--)
	{
		printf("%c", *(str + i));
	}

	return 0;
}
