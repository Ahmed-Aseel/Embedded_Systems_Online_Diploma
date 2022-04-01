/*
 * main.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Aseel
 *
 *  Description: print all the alphabets using a pointer
 *
 */

#include "stdio.h"
#include "stdlib.h"

int main()
{
	char *c = (char*)malloc(sizeof(char));
	*c = 'A';
	printf("The Alphabets are:\n");
	while(*c <= 'Z')
	{
		printf("%c ", *c);
		*c += 1;
	}
	free(c);
	return 0;
}
