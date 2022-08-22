/*
 * queue.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Aseel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Platform_Types.h"
#include "queue.h"

/**************** APIs definitions ****************/

/* ================================================================================ */
void Create_Queue(Queue *pq)
{
	/* initialize Front & Rear with NULL
	 * initialize Length with zero
	 */
    pq->Front=NULL;
    pq->Rear=NULL;
    pq->Length = 0;
}

/* ================================================================================ */
void Clear_Queue(Queue* pq)
{
	// loop over all queue nodes
    while(pq->Front)
    {
    	/* make Rear points to the next node to the Front
    	 * free Front node
    	 * make Front points to Rear
    	 */
        pq->Rear = pq->Front->Next;
        free(pq->Front);
        pq->Front = pq->Rear;
    }

    // eventually make Length = zero
    pq->Length = 0;
}

/* ================================================================================ */
uint8_t Is_Queue_Empty(Queue *pq)
{
	/* if Front points to NULL return 1
	 * else return 0
	 */
    if(pq->Front == NULL) // or check if Length == 0
        return 1;
    else
        return 0;
}

/* ================================================================================ */
void Add_Student_File(Queue *pq)
{
	FILE* fptr = NULL;
	char_t filename[25], line[100];

	/* Asking the user to enter the file name with its extension
	 * and if the file name is not correct or failed to open it
	 * ask the user to enter it again
	 */
	do
	{
		Dprintf("Enter file name (ex: xyz.txt): ");
		scanf("%s", filename);
		// open file in read mode
		fptr = fopen(filename, "r");
		// check if the file is opened successfully or not
		if(fptr == NULL)
		{
			Dprintf("No Such File Or Directory!! \n");
			Dprintf("----------------------- \n");
		}

	}while(fptr == NULL);

	// read the info from the file into an array
	while(fgets(line, 100, fptr))
	{
	    QueueNode* pn=(QueueNode*)malloc(sizeof(QueueNode));
		// load the values into variable of type struct queuenode
		sscanf(line, "%d %s %s %f %d %d %d %d %d \n", &pn->RollNumber,
				pn->FirstName, pn->LastName, &pn->GPA, &pn->Courses[0],
				&pn->Courses[1], &pn->Courses[2], &pn->Courses[3], &pn->Courses[4]);
		// make next of the node points to NULL
	    pn->Next = NULL;

	    // check if the roll number exist or not?
		if(Is_RollNumber_Exist(pq, pn->RollNumber))
		{
			// if exist free pn and continue to read next student info
			Dprintf("[ERORR] Roll Number Is Already Taken!! \n");
			free(pn);
			continue;
		}

		// check if the queue is empty?
	    if(Is_Queue_Empty(pq))
	    {
	    	// if true make Front points to pn node
	        pq->Front = pn;
	    }
	    else
	    {
	    	// if false make Rear Next points to pn node
	        pq->Rear->Next = pn;
	    }
	    /* make Rear points to pn node
	     * increament Length
	     */
	    pq->Rear = pn;
	    pq->Length++;
		Dprintf("[INFO] ROll Number %d Is Added Successfully \n", pn->RollNumber);
	}

	Dprintf("[INFO] Student Details Is Added Successfully \n\n");
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
void Add_Student_Manually(Queue *pq)
{
    uint8_t i;
    QueueNode* pn=(QueueNode*)malloc(sizeof(QueueNode));
    // ask the user to input roll number of the new student
	Dprintf("Add Student Details \n");
	Dprintf("Enter Student Roll Number: ");
	scanf("%d", &pn->RollNumber);

    // check if the roll number exist or not?
	if(Is_RollNumber_Exist(pq, pn->RollNumber))
	{
		// if exist free pn and return to main
		Dprintf("[ERORR] Roll Number Is Already Taken!! \n");
		Dprintf("----------------------- \n");
		free(pn);
		return; // return to main
	}

	// if not exist ask the user to input remaining data
	Dprintf("Enter Student First Name: ");
	scanf("%s", pn->FirstName);
	Dprintf("Enter Student Last Name: ");
	scanf("%s", pn->LastName);
	Dprintf("Enter Student GPA: ");
	scanf("%f", &pn->GPA);

	Dprintf("Enter the course ID for each course \n");
    for(i = 0; i < 5; i++)
    {
        Dprintf("Course %d ID: ", i + 1);
    	scanf("%d", &pn->Courses[i]);
    }
    // make next of the node points to NULL
    pn->Next = NULL;

    // check if the queue is empty?
    if(Is_Queue_Empty(pq))
    {
    	// if true make Front points to pn node
    	pq->Front = pn;
    }
    else
    {
    	// if false make Rear Next points to pn node
    	pq->Rear->Next = pn;
    }
    /* make Rear points to pn node
     * increament Length
     */
    pq->Rear = pn;
    pq->Length++;
	Dprintf("[INFO] Student Details Is Added Successfully \n\n");
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
uint8_t Is_RollNumber_Exist(Queue *pq, uint32_t rollnumber)
{
    QueueNode* pn = pq->Front;
	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		return 0;
	}

	// loop over all queue nodes
    while(pn)
    {
    	/* check if roll number of the current student
    	 * equals current roll number
    	 */
    	if(pn->RollNumber == rollnumber)
    	{
    		// if true return 1
    		return 1;
    	}
    	// make pn points to next node
    	pn = pn->Next;
    }

	/* if reached the end of the queue
	 * and not found roll number return 0
	 */
	return 0;
}

/* ================================================================================ */
void Find_By_RollNumber(Queue *pq)
{
	uint32_t rollnumber;
	uint8_t i;
    QueueNode* pn = pq->Front;
	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		// if true return to main
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return; // return to main
	}

	// ask the user to input roll number
	Dprintf("Enter Roll Number of the student: ");
	scanf("%d", &rollnumber);
	// loop over all queue nodes
    while(pn)
    {
    	/* check if roll number of the current student
    	 * equals input roll number
    	 */
    	if(pn->RollNumber == rollnumber)
    	{
    		// if true print this student info
    		Dprintf("The Student Details are \n");
    		Dprintf("Student first name: %s \n", pn->FirstName);
            Dprintf("Student last name: %s \n", pn->LastName);
            Dprintf("Student roll number: %d \n", pn->RollNumber);
            Dprintf("Student GPA: %0.2f \n", pn->GPA);

            for(i = 0; i < 5; i++)
            {
                Dprintf("Course %d ID: %d \n", i + 1, pn->Courses[i]);
            }
    		Dprintf("----------------------- \n");
            return; // return to main
    	}
    	// make pn points to next node
    	pn = pn->Next;
    }

	/* if reached the end of the queue
	 * and not found roll number
	 */
	Dprintf("[ERROR] Roll Number %d Not Found!! \n\n", rollnumber);
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
void Find_By_FirstName(Queue *pq)
{
	char_t firstname[10];
	uint8_t i, found = 0;
    QueueNode* pn = pq->Front;
	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return;
	}

	// ask the user to input first name
	Dprintf("Enter First Name of the student: ");
	scanf("%s", firstname);
	// loop over all queue nodes
    while(pn)
    {
    	/* check if first name of the current student
    	 * equals input first name
    	 */
    	if(strcmp(pn->FirstName, firstname) == 0)
    	{
    		// if true set found flag and print this student info
    		found = 1;
    		Dprintf("The Student Details are \n");
    		Dprintf("Student first name: %s \n", pn->FirstName);
            Dprintf("Student last name: %s \n", pn->LastName);
            Dprintf("Student roll number: %d \n", pn->RollNumber);
            Dprintf("Student GPA: %0.2f \n", pn->GPA);

            for(i = 0; i < 5; i++)
            {
                Dprintf("Course %d ID: %d \n", i + 1, pn->Courses[i]);
            }
    		Dprintf("----------------------- \n");
    	}
    	// make pn points to next node
    	pn = pn->Next;
    }

    /* check if there is no such first name */
    if(found == 0)
	{
    	Dprintf("[ERROR] First Name %s Not Found!! \n\n", firstname);
		Dprintf("----------------------- \n");
	}
}

/* ================================================================================ */
void Find_By_CourseID(Queue *pq)
{
	uint32_t course_ID;
	uint8_t i, found = 0;
    QueueNode* pn = pq->Front;
	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return; // return to main
	}

	// ask the user to input course ID
	Dprintf("Enter The Course ID: ");
	scanf("%d", &course_ID);
	// loop over all queue nodes
    while(pn)
    {
    	// loop over all student courses
        for(i = 0; i < 5; i++)
        {
        	/* check if any course ID of the current student
        	 * equals input course ID
        	 */
			if(pn->Courses[i] == course_ID)
			{
	    		// if true set found flag and print this student info
				found = 1;
				Dprintf("The Student Details are \n");
				Dprintf("Student first name: %s \n", pn->FirstName);
				Dprintf("Student last name: %s \n", pn->LastName);
				Dprintf("Student roll number: %d \n", pn->RollNumber);
				Dprintf("Student GPA: %0.2f \n", pn->GPA);
     		    Dprintf("----------------------- \n");
				break; // break for loop and jump to the next student
			}
        }
    	// make pn points to next node
    	pn = pn->Next;
    }

    /* check if there is no such course ID */
    if(found == 0)
    {
    	Dprintf("[ERROR] Course ID %d Not Found!! \n\n", course_ID);
		Dprintf("----------------------- \n");
    }
}

/* ================================================================================ */
void Total_Students_Number(Queue *pq)
{
	// print queue Length
	Dprintf("[INFO] The Total Number Of Student : %d \n\n", pq->Length);
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
void Delete_By_RollNumber(Queue *pq)
{
	uint32_t rollnumber;
    QueueNode* current = pq->Front;
    QueueNode* prev = NULL;

	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return; // return to main
	}

	// ask the user to input roll number
	Dprintf("Enter Roll Number you want to delete: ");
	scanf("%d", &rollnumber);
	// loop over all queue nodes
    while(current)
    {
    	/* check if roll number of the current student
    	 * equals input roll number
    	 */
    	if(current->RollNumber == rollnumber)
    	{
    		if(!current->Next) // if the last node is to be deleted
    		{
    			// make Rear point to the previous node
    			pq->Rear = prev;
    		}
    		// if the first & last node are not the current
    		if(prev)
    		{
    			// make next of the previous node point to the next of the current node
    			prev->Next = current->Next;
    		}

    		else // if the first node is to be deleted
    		{
    			// make Front point to the next node
    			pq->Front = current->Next;
    		}
    		// free current node
			free(current);
			// decreament Length
			pq->Length--;
			Dprintf("[INFO] Roll Number Deleted Successfully. \n\n");
			Dprintf("----------------------- \n");
    		return; // return to main
    	}
    	/* make pre points to current node
    	 * and make current points to the next node
    	 */
    	prev = current;
    	current = current->Next;
	}

    // if there is no such roll number
	Dprintf("[ERROR] Roll Number %d Not Found!! \n\n", rollnumber);
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
void Update_By_RollNumber(Queue *pq)
{
	char_t input[10];
	uint32_t rollnumber;
    QueueNode* pn = pq->Front;
	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return; // return to main
	}

	// ask the user to input roll number
	Dprintf("Enter Roll Number of the student: ");
	scanf("%d", &rollnumber);
	// loop over all queue nodes
	while(pn)
	{
		/* check if roll number of the current student
		 * equals input roll number
		 */
		if(pn->RollNumber == rollnumber)
		{
			do
			{
				// ask the user to choose member to update
				Dprintf("1. First Name \n");
				Dprintf("2. Last Name \n");
				Dprintf("3. Roll Number \n");
				Dprintf("4. GPA \n");
				Dprintf("5. Courses \n");
				Dprintf("Enter your choice: ");
				scanf("%s", input);

				uint8_t i;
				/* switch user input after
				 * converting input string to integer
				 */
				switch(atoi(input))
				{
				case 1:
					/* ask user to input new first name
					 * then replace old first name
					 */
					Dprintf("Enter The New First Name: ");
					scanf("%s", input);
					strcpy(pn->FirstName, input);
					Dprintf("[INFO] UPDATED SUCCESSFULLY. \n\n");
					Dprintf("----------------------- \n");
					break;

				case 2:
					/* ask user to input new last name
					 * then replace old last name
					 */
					Dprintf("Enter The New Last Name: ");
					scanf("%s", input);
					strcpy(pn->LastName, input);
					Dprintf("[INFO] UPDATED SUCCESSFULLY. \n\n");
					Dprintf("----------------------- \n");
					break;

				case 3:
					// ask user to input new roll number
					Dprintf("Enter The New Roll Number: ");
					scanf("%s", input);

					/* convert input string to integer
					 * and check if the roll number exist or not?
					 */
					if(Is_RollNumber_Exist(pq, atoi(input)))
					{
						Dprintf("[ERORR] Roll Number Is Already Taken!! \n");
						Dprintf("----------------------- \n");
						break;
					}

					//  replace old roll number
					pn->RollNumber = atoi(input);
					Dprintf("[INFO] UPDATED SUCCESSFULLY. \n\n");
					Dprintf("----------------------- \n");
					break;

				case 4:
					/* ask user to input new GPA
					 * then convert input string to float
					 * finally replace old GPA
					 */
					Dprintf("Enter The New GPA: ");
					scanf("%s", input);
					pn->GPA = atof(input);
					Dprintf("[INFO] UPDATED SUCCESSFULLY. \n\n");
					Dprintf("----------------------- \n");
					break;

				case 5:
					// ask user to input all new courses ID
					Dprintf("Enter the new course ID for each course \n");
					for(i = 0; i < 5; i++)
					{
						Dprintf("Course %d ID: ", i + 1);
						scanf("%d", &pn->Courses[i]);
					}
					Dprintf("[INFO] UPDATED SUCCESSFULLY. \n\n");
					Dprintf("----------------------- \n");
					break;

				default: // in case the user input wrong number
					Dprintf("[ERROR] Wrong Choice!!! \n");
					Dprintf("----------------------- \n");
					break;
				}
				Dprintf("Do You Want To Update Anything Else? (y/n): ");
				scanf("%s", input);
				Dprintf("\n----------------------- \n");

			// keep asking user to update till user enter 'n'
			}while(input[0] == 'y');

			return; // return to main
		}

		// make pn points to next node
		pn = pn->Next;
	}

	/* if reached the end of the queue
	 * and not found roll number
	 */
	Dprintf("[ERROR] Roll Number %d Not Found!! \n\n", rollnumber);
	Dprintf("----------------------- \n");
}

/* ================================================================================ */
void Show_AllStudent(Queue *pq)
{
    uint8_t i;
    QueueNode* pn = pq->Front;

	// check if the queue is empty?
	if(Is_Queue_Empty(pq))
	{
		Dprintf("[ERROR] Queue Is Empty!! \n\n");
		Dprintf("----------------------- \n");
		return; // return to main
	}

	Dprintf("All Students Info \n\n");
	// loop over all queue nodes
	while(pn)
    {
        Dprintf("Student first name: %s \n", pn->FirstName);
        Dprintf("Student last name: %s \n", pn->LastName);
        Dprintf("Student roll number: %d \n", pn->RollNumber);
        Dprintf("Student GPA: %0.2f \n", pn->GPA);

        for(i = 0; i < 5; i++)
        {
            Dprintf("Course %d ID: %d \n", i + 1, pn->Courses[i]);
        }
		Dprintf("----------------------- \n");
    	// make pn points to next node
        pn = pn->Next;
    }
}

/* ================================================================================ */
