/*
 * queue.h
 *
 *  Created on: Aug 20, 2022
 *      Author: Aseel
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/**************** macro function ****************/
#define Dprintf(...)     {fflush(stdin);\
						  fflush(stdout);\
						  printf(__VA_ARGS__);\
						  fflush(stdin);\
						  fflush(stdout);}

/**************** type definitions ****************/
typedef struct queuenode QueueNode;
typedef struct queue Queue;

struct queuenode
{
	char_t FirstName[10];
	char_t LastName[10];
	uint32_t RollNumber;
	float32_t GPA;
	uint32_t Courses[5];
    QueueNode* Next;
};

struct queue
{
    QueueNode* Front;
    QueueNode* Rear;
    uint8_t Length;
};

/**************** APIs prototypes ****************/
void Create_Queue(Queue *pq);
void Clear_Queue(Queue* pq);
uint8_t Is_Queue_Empty(Queue *pq);
void Add_Student_File(Queue *pq);
void Add_Student_Manually(Queue *pq);
uint8_t Is_RollNumber_Exist(Queue *pq, uint32_t rollnumber);
void Find_By_RollNumber(Queue *pq);
void Find_By_FirstName(Queue *pq);
void Find_By_CourseID(Queue *pq);
void Total_Students_Number(Queue *pq);
void Delete_By_RollNumber(Queue *pq);
void Update_By_RollNumber(Queue *pq);
void Show_AllStudent(Queue *pq);

#endif /* QUEUE_H_ */
