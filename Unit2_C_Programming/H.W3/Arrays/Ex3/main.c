/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Aseel
 *
 *  Description: C program to find the transpose of a matrix
 */

#include "stdio.h"

int main()
{
	int r, c, i, j;
	printf("Enter rows and columns of matrx: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &r, &c);
	int a[r][c];
	printf("Enter the elements of the matrix\n");
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("Enter element a%d%d: ", i+1, j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d", &a[i][j]);
		}
	}
	printf("Entered matrix:\n");
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d  ", a[i][j]);
		}
		printf("\n");
	}
	printf("transpose of matrix:\n");
	for(i = 0; i < c; i++)
	{
		for(j = 0; j < r; j++)
		{
			printf("%d  ", a[j][i]);
		}
		printf("\n");
	}

	return 0;
}
