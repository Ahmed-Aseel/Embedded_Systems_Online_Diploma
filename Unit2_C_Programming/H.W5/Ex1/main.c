/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Aseel
 *
 *  Description: Store information of a student
 *  			 using structure
 */

#include "stdio.h"

struct Sstudent
{
	char name[25];
	int roll;
	float marks;
};

int main()
{
	struct Sstudent s1;
	printf("Enter information of students:\n");
	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	gets(s1.name);
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &s1.roll);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &s1.marks);

	printf("\nDisplaying Information\n");
	printf("Name: %s\n", s1.name);
	printf("Roll: %d\n", s1.roll);
	printf("Marks: %0.2f", s1.marks);

	return 0;
}
