#pragma once
#define MAX_SIZ 5

typedef struct {
	int front;
	int rear;
	char data[MAX_SIZ];
}QueueType;

void init_linear_queue(QueueType* q)
{
	q->front = -1;
	q->rear = -1;
	for (int i = 0; i < MAX_SIZ; i++)
		q->data[i] = '0';
}

int isfull(QueueType* q)
{
	if (q->rear == MAX_SIZ - 1)
		return 1;
	else
		return 0;
}

int isempty(QueueType* q)
{
	if (q->rear == -1)
		return 1;
	else
		return 0;
}

int enQueue(QueueType* q, char value)
{
	if (isfull(q) == 1)
	{
		return -1;
	}
	q->data[++(q->rear)] = value;
	return 0;
}

char deQueue(QueueType* q)
{
	char result;

	if (isempty(q) == 1)
		return '\0';
	else
	{
		result = q->data[++(q->front)];
		return result;
	}
}

