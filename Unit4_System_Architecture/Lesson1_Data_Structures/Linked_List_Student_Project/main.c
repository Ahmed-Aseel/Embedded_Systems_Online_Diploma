/*
 * main.c
 *
 *  Created on: Aug 5, 2022
 *      Author: Aseel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define Dprintf(...)     {fflush(stdin);\
						  fflush(stdout);\
						  printf(__VA_ARGS__);\
						  fflush(stdin);\
						  fflush(stdout);}

// effective data
typedef struct
{
	char Name[15];
	unsigned int ID;
	float hight;

}Sdata_t;

typedef struct Student
{
	Sdata_t Student;
	struct Student* pNextStudent;

}SStudent_t;

SStudent_t* gpFirstStudent = NULL;
SStudent_t* gpLastStudent = NULL;

void Add_Student()
{
	SStudent_t* pNewStudent;
	// create new record
	pNewStudent = (SStudent_t*) malloc(sizeof(SStudent_t));
	// check if the list empty ?
	if(gpFirstStudent == NULL)
	{
		// assign to gpFirstStudent
		gpFirstStudent = pNewStudent;
	}

	else // list contain records
	{
		// assign to  next of gpLastStudent
		gpLastStudent->pNextStudent = pNewStudent;
	}
	// make gpLastStudent point to the new record
	gpLastStudent = pNewStudent;

	// fill new record data
	Dprintf("Enter student ID: ");
	scanf("%u", &pNewStudent->Student.ID);
	Dprintf("Enter student name: ");
	gets(pNewStudent->Student.Name);
	Dprintf("Enter student height: ");
	scanf("%f", &pNewStudent->Student.hight);

	pNewStudent->pNextStudent = NULL;
}

int Delete_Student()
{
	unsigned int id;
	Dprintf("Enter student ID to be deleted: ");
	scanf("%u", &id);

	// check if the list empty ?
	if(gpFirstStudent)
	{
		SStudent_t* pSelectedStudent = gpFirstStudent;
		SStudent_t* pPrevStudent = NULL;

		// loop over all records
		while(pSelectedStudent)
		{
			// check if the current student id == selected id
			if(pSelectedStudent->Student.ID == id)
			{
				if(!pSelectedStudent->pNextStudent) // the last student is the selected
				{
					gpLastStudent = pPrevStudent;
				}

				if(pPrevStudent) // the 1st student is not the selected
				{
					pPrevStudent->pNextStudent = pSelectedStudent->pNextStudent;
				}

				else // the 1st student is the selected
				{
					gpFirstStudent = pSelectedStudent->pNextStudent;
				}

				free(pSelectedStudent);
				return 1;
			}

			pPrevStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->pNextStudent;
		}
	}

	Dprintf("Can not find student ID!!\n");
	return 0;
}

void View_Students()
{
	int count = 1;
	SStudent_t* pCurrentStudent = gpFirstStudent;
	// check if the list empty ?
	if(!pCurrentStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		// loop over all records
		while(pCurrentStudent)
		{
			Dprintf("record number %d\n", count);
			Dprintf("ID: %d\n", pCurrentStudent->Student.ID);
			Dprintf("Name: %s\n", pCurrentStudent->Student.Name);
			Dprintf("Height: %f\n", pCurrentStudent->Student.hight);
			Dprintf("-----------------------\n");

			pCurrentStudent = pCurrentStudent->pNextStudent;
			count++;
		}
	}
}

void Delete_All()
{
	SStudent_t* pCurrentStudent = gpFirstStudent;
	// check if the list empty ?
	if(!pCurrentStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		SStudent_t* pTempStudent = NULL;
		// loop over all records
		while(pCurrentStudent)
		{
			pTempStudent = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->pNextStudent;
			free(pTempStudent);
		}

		gpFirstStudent = NULL;
		gpLastStudent = NULL;
	}
}

void Get_Nth_Student()
{
	int index, count;
	/*	ask the user to input the index
		of the record wants to delete from the
		start of the list (index starts from 0)
	 */
	Dprintf("Enter the index : ");
	scanf("%d", &index);
	count = index;
	SStudent_t* pSelectedStudent = gpFirstStudent;
	// check if the list empty ?
	if(!pSelectedStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		// loop until count = 0 or reach end of the list
		while(count > 0 && pSelectedStudent)
		{
			count--;
			pSelectedStudent = pSelectedStudent->pNextStudent;
		}

		if(count == 0 && pSelectedStudent)
		{
			Dprintf("\nStudent at index %d Info \n", index);
			Dprintf("ID: %d\n", pSelectedStudent->Student.ID);
			Dprintf("Name: %s\n", pSelectedStudent->Student.Name);
			Dprintf("Height: %f\n", pSelectedStudent->Student.hight);
		}

		else // if the index is -ve or greater than the list length
		{
			Dprintf("Index does not exist\n");
		}
	}
}

void List_Length()
{
	int length = 0;
	SStudent_t* pTempStudent = gpFirstStudent;
	// loop over all records
	while(pTempStudent)
	{
		length++;
		pTempStudent = pTempStudent->pNextStudent;
	}

	Dprintf("Length of the list =  %d \n", length);
}

void Nth_Student_From_End()
{
	int index, count;
	/*	ask the user to input the index
		of the record wants to delete from the
		end of the list (index starts from 1)
	 */
	Dprintf("Enter the index : ");
	scanf("%d", &index);
	count = index - 1;
	SStudent_t* pRefStudent = gpFirstStudent;
	SStudent_t* pMainStudent = gpFirstStudent;
	// check if the list empty ?
	if(!pRefStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		/*	loop until count = 0 or reach end of the list
			make distance between pRefStudent & pMainStudent
			equal index - 1
		 */
		while(count > 0 && pRefStudent)
		{
			count--;
			pRefStudent = pRefStudent->pNextStudent;
		}

		// if we didn't reach the end of the list
		if(pRefStudent)
		{
			/*	loop until reach the last record
				increament the pRefStudent & pMainStudent
				keeping the same distance between them
			*/
			while(pRefStudent->pNextStudent)
			{
				pRefStudent = pRefStudent->pNextStudent;
				pMainStudent = pMainStudent->pNextStudent;

			}

			Dprintf("\nStudent %d from the end Info \n", index);
			Dprintf("ID: %d\n", pMainStudent->Student.ID);
			Dprintf("Name: %s\n", pMainStudent->Student.Name);
			Dprintf("Height: %f\n", pMainStudent->Student.hight);
		}

		else // if the index is -ve or greater than the list length
		{
			Dprintf("Index does not exist\n");
		}
	}
}

void Middle_Student()
{
	SStudent_t* pRefStudent = gpFirstStudent;
	SStudent_t* pMidStudent = gpFirstStudent;
	// check if the list empty ?
	if(!pRefStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		// loop until reach the last record or the end of the list
		while(pRefStudent && pRefStudent->pNextStudent)
		{
			// increase pRefStudent by 2 steps & pMidStudent by 1 step
			pRefStudent = pRefStudent->pNextStudent->pNextStudent;
			pMidStudent = pMidStudent->pNextStudent;
		}

		Dprintf("\nMiddle Student Info \n");
		Dprintf("ID: %d\n", pMidStudent->Student.ID);
		Dprintf("Name: %s\n", pMidStudent->Student.Name);
		Dprintf("Height: %f\n", pMidStudent->Student.hight);
	}
}

void Reverse_List()
{
	int set_last = 0;
	SStudent_t* pCurrentStudent = gpFirstStudent;
	SStudent_t* pNextStudent = gpFirstStudent;
	SStudent_t* pPrevStudent = NULL;
	// check if the list empty ?
	if(!pCurrentStudent)
	{
		Dprintf("List Is Empty\n");
	}

	else
	{
		while(pCurrentStudent)
		{
			/*	make gpLastStudent point to the first record
				we need to do that only 1 time so we make
				set_last = 1
			 */
			if(set_last == 0)
			{
				gpLastStudent = pCurrentStudent;
				set_last = 1;
			}

			pNextStudent = pCurrentStudent->pNextStudent;
			pCurrentStudent->pNextStudent = pPrevStudent;
			pPrevStudent = pCurrentStudent;
			pCurrentStudent = pNextStudent;
		}

		gpFirstStudent = pPrevStudent;
	}
}

int main()
{
	int choice;
	while(1)
	{
		Dprintf("-----------------------\n");
		Dprintf("Choose one of the following options \n");
		Dprintf("1: Add_Student \n");
		Dprintf("2: Delete_Student \n");
		Dprintf("3: View_Students \n");
		Dprintf("4: Delete_All \n");
		Dprintf("5: Get_Nth_Student \n");
		Dprintf("6: List_Length \n");
		Dprintf("7: Nth_Student_From_End \n");
		Dprintf("8: Middle_Student \n");
		Dprintf("9: Reverse_List \n");
		Dprintf("Enter your options : ");
		scanf("%d", &choice);
		Dprintf("-----------------------\n");

		switch(choice)
		{
		case 1:
			Add_Student();
			break;

		case 2:
			Delete_Student();
			break;

		case 3:
			View_Students();
			break;

		case 4:
			Delete_All();
			break;

		case 5:
			Get_Nth_Student();
			break;

		case 6:
			List_Length();
			break;

		case 7:
			Nth_Student_From_End();
			break;

		case 8:
			Middle_Student();
			break;

		case 9:
			Reverse_List();
			break;

		default:
			Dprintf("Wrong Choice!!!\n");
			break;
		}
	}
}
