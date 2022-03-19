/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Aseel
 *
 *  Description: Add 2 complex by passing struct to function
 *
 */

#include "stdio.h"

struct Scomplex
{
	float real;
	float img;
};

struct Scomplex getcomplex(void)
{
	struct Scomplex c;
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &c.real, &c.img);

	return c;
}

struct Scomplex sum2complex(struct Scomplex c1, struct Scomplex c2)
{
	struct Scomplex sum;
	sum.real = c1.real + c2.real;
	sum.img = c1.img + c2.img;
	return sum;
}

int main()
{
	struct Scomplex c1, c2, sum;
	printf("For 1st complex number\n");
	c1 = getcomplex();
	printf("\nFor 2nd complex number\n");
	c2 = getcomplex();

	sum = sum2complex(c1, c2);
	printf("\nSum = %0.1f + %0.1fi", sum.real, sum.img);
	return 0;
}
