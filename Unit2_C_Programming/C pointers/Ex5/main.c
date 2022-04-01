/*
 * main.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Aseel
 *
 *  Description: show a pointer to an array which
 *  			 contents are pointer to structure.
 *
 */

#include "stdio.h"

struct Semployee
{
	char name[10];
	int id;
};

int main()
{
	struct Semployee emp1 = {"Alex", 1002};
	struct Semployee emp2 = {"Tom", 1003};
	struct Semployee* emps[] = {&emp1, &emp2};
	printf("Employee Name : %s\n", emps[0]->name);
	printf("Employee ID : %d", emps[0]->id);

	return 0;
}
