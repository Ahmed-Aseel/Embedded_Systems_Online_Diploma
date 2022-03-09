/*
 * main.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Aseel
 *
 *  Description: Reverse a sentence using recursion
 */

#include "stdio.h"
#include "string.h"
void reverse(char *str, int start, int end);

int main()
{
	char str[25];
	printf("Enter a sentence: ");
	fflush(stdin); 	fflush(stdout);
	gets(str);
	reverse(str, 0, strlen(str) - 1);
	printf("%s", str);
	return 0;
}

void reverse(char *str, int start, int end)
{
	if(start >= end || str[start] == '\0')
		return;
	char temp = str[start];
	str[start] = str[end];
	str[end] = temp;
	reverse(str, start + 1, end - 1);
}
