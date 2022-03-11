/*
 * main.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Aseel
 *
 *  Description: Prime numbers between interval
 */

#include "stdio.h"
void Is_Prime(int num);

int main()
{
	int start, end;
	printf("Enter two numbers(intervals): ");
	fflush(stdin); 	fflush(stdout);
	scanf("%d %d", &start, &end);
	printf("Prime numbers between %d and %d are: ", start, end);
	int i;
	for(i = start; i <= end; i++)
	{
		Is_Prime(i);
	}
	return 0;
}

void Is_Prime(int num)
{
	int i, count = 0;
	for(i = 2; i <= num / 2; i++)
	{
		if(num % i == 0)
			count++;
	}
	if(count == 0)
		printf("%d ", num);
}
