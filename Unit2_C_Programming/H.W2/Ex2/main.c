/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to check vowel or consonant
 */

#include "stdio.h"

int main()
{
	char ch;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &ch);
	if(ch == 'A' || ch == 'a' || ch == 'E' || ch == 'e' ||
	   ch == 'I' || ch == 'i' || ch == 'O' || ch == 'o' ||
	   ch == 'U' || ch == 'u')

		printf("%c is vowel.", ch);
	else
		printf("%c is consonant.", ch);

	return 0;
}
