/*
 * main.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Aseel
 *
 *  Description: demonstrate how to handle the
 *  			 pointers in the program
 */

#include "stdio.h"

int main()
{
	int m = 29;
	printf("Address of m : %p\n", &m);
	printf("Value of m : %d\n\n", m);

	int *ab = &m;
	printf("Address of pointer ab : %p\n", ab);
	printf("Content of pointer ab : %d\n\n", *ab);

	m = 34;
	printf("Address of pointer ab : %p\n", ab);
	printf("Content of pointer ab : %d\n\n", *ab);

	*ab = 7;
	printf("Address of m : %p\n", &m);
	printf("Value of m : %d\n", m);

	return 0;
}
