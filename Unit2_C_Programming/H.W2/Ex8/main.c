/*
 * main.c
 *
 *  Created on: Mar 2, 2022
 *      Author: Aseel
 *
 *  Description: C Program to make a simple calculator
 */

#include "stdio.h"
#include "stdlib.h"

int main()
{
	char operation;
	float operand1, operand2;
	printf("Enter operation either + or -or * or /: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &operation);
	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &operand1, &operand2);
	switch(operation)
	{
	case '+':
		printf("%f + %f = %f", operand1, operand2, operand1 + operand2);
		break;
	case '-':
		printf("%f - %f = %f", operand1, operand2, operand1 - operand2);
		break;
	case '*':
		printf("%f * %f = %f", operand1, operand2, operand1 * operand2);
		break;
	case '/':
		if(operand2 == 0)
		{
			printf("Error!! Devision by zero.");
			exit(0);
		}
		printf("%f / %f = %f", operand1, operand2, operand1 / operand2);
		break;
	default:
		printf("Error!! Wrong operation.");
		break;
	}

	return 0;
}
