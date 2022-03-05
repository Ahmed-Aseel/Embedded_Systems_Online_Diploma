/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to find the frequency of characters in a string
 */

#include "stdio.h"

int main()
{
	char str[25];
	char ch;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &ch);
	int count, i;
	count = i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == ch)
			count++;
		i++;
	}
	printf("Frequency of %c = %d", ch, count);

	return 0;
}
