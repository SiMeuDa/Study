#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100


typedef struct {
	char data[MAX_SIZE];
	int top;
} StackType;

void Error(void) {
	printf("[Error]\n");
	return;
}

bool initi_Stack(StackType* s) {
	s->top = -1;
	for (int i = 0; i < MAX_SIZE; i++)
		s->data[i] = '0';
	return true;
}

bool isEmpty(StackType* s)
{
	if (s->top == -1)
		return true;
	else
		return false;
}

bool isFull(StackType* s)
{
	if (s->top == MAX_SIZE - 1)
		return true;
	else
		return false;
}

//If success to push data to stack return true, else false
bool push(StackType* s, char value)
{
	if (isFull(s) == true)
	{
		Error();
		return false;
	}
	else 
	{
		s->data[++(s->top)] = value;
		return true;
	}
}

char pop(StackType* s)
{
	if (isEmpty(s) == 1)
	{
		Error();
		return '\0';
	}
	else
	{
		s->data[(s->top)--];
		return s->data[(s->top) + 1];
	}
}

char peeks(StackType* s)
{
	if (isEmpty(s) == 1)
	{
		Error();
		return '\0';
	}
	else
	{
		return s->data[s->top];
	}
}