/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *  Author: Ahmed Aseel
 *  Description: C program to implement Student Management System
 */

#include <stdio.h>
#include <stdlib.h>
#include "Platform_Types.h"
#include "queue.h"

int main()
{
	uint32_t choice;
	Queue q;
	Create_Queue(&q);

	/* Asking the user to choose one of the options */
	Dprintf("Welcome to the Student Management System \n");
	while (1)
	{
		Dprintf("Choose The Task that you want to perform \n");
		Dprintf("1. Add the Student Details From Text File \n");
		Dprintf("2. Add the Student Details Manually \n");
		Dprintf("3. Find the Student Details by Roll Number \n");
		Dprintf("4. Find the Student Details by First Name \n");
		Dprintf("5. Find the Student Details by Course Id \n");
		Dprintf("6. Find the Total number of Students \n");
		Dprintf("7. Delete the Students Details by Roll Number \n");
		Dprintf("8. Update the Students Details by Roll Number \n");
		Dprintf("9. Show all information \n");
		Dprintf("0. Exit \n");
		Dprintf("Enter your choice to perform the task: ");
		scanf("%d", &choice);
		Dprintf("----------------------- \n");

		/* switch user choice and call
		 * the corresponding function
		 */
		switch(choice)
		{
		case 1:
			Add_Student_File(&q);
			break;

		case 2:
			Add_Student_Manually(&q);
			break;

		case 3:
			Find_By_RollNumber(&q);
			break;

		case 4:
			Find_By_FirstName(&q);
			break;

		case 5:
			Find_By_CourseID(&q);
			break;

		case 6:
			Total_Students_Number(&q);
			break;

		case 7:
			Delete_By_RollNumber(&q);
			break;

		case 8:
			Update_By_RollNumber(&q);
			break;

		case 9:
			Show_AllStudent(&q);
			break;

		case 0:
			Clear_Queue(&q); // free dynamic allocation
			Dprintf("<<< THANK YOU >>>\n");
			exit(0);
			break;

		default: // in case the user input wrong number
			Dprintf("[ERROR] Wrong Choice!!! \n");
			break;
		}
	}

	return 0;
}
