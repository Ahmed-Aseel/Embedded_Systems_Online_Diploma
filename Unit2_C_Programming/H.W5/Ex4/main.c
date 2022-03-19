/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Aseel
 *
 *  Description: Store information of students
 *  			 using structure
 */

#include "stdio.h"

struct Sstudent
{
	char name[15];
	int roll;
	float marks;
};

struct Sstudent getinfo()
{
	struct Sstudent s;
	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	gets(s.name);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &s.marks);

	return s;
}

void displayinfo(struct Sstudent students[])
{
	int i;
	for(i = 0; i < 10; i++)
	{
		printf("Information for roll number %d\n", students[i].roll);
		printf("Name: %s\n", students[i].name);
		printf("Marks: %0.2f\n", students[i].marks);
	}
}

int main()
{
	struct Sstudent students[10];
	int i;

	printf("Enter information of students:\n");
	for(i = 0; i < 10; i++)
	{
		printf("For roll number %d\n", i + 1);
		students[i] = getinfo();
		students[i].roll = i + 1;
	}

	printf("\nDisplaying information of students:\n");
	displayinfo(students);

	return 0;
}
