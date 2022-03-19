/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Aseel
 *
 *  Description: Add 2 distance in (inch-feet)
 *  			 using structure
 */

#include "stdio.h"

struct Sdistance
{
	int feet;
	float inch;
};

struct Sdistance getdistance(void)
{
	struct Sdistance d;
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &d.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &d.inch);

	return d;
}

struct Sdistance sum2distances(struct Sdistance d1, struct Sdistance d2)
{
	struct Sdistance sum;
	sum.feet = d1.feet + d2.feet;
	sum.inch = d1.inch + d2.inch;

	if(sum.inch >= (float)12)
	{
		sum.feet++;
		sum.inch -= 12;
	}

	return sum;
}

int main()
{
	struct Sdistance d1, d2, sum;
	printf("Enter information of 1st distance:\n");
	d1 = getdistance();
	printf("\nEnter information of 2nd distance:\n");
	d2 = getdistance();

	sum = sum2distances(d1, d2);
	printf("Sum of distances = %d'%0.1f\"", sum.feet, sum.inch);
	return 0;
}

