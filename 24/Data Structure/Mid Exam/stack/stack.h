#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define true 1
#define false 0

typedef struct{
//create
    int top;
    char data[MAX];
}STACK;

void Error(const char* message){
    fprintf(stderr, "[Error]: %s\n", message);
    exit(1);
}

void init_stack(STACK* s){
//initalize stack's top to -1
    s->top = -1;
}

int isFull(STACK* s){
//whether STACK is full or not
    if(s->top == MAX - 1)
        return true;
    else
        return false;
}

int isEmpty(STACK* s){
//whether STACK is empty or not
    if(s->top == -1)
        return true;
    else
        return false;
}

void push(STACK* s, char value){
//push data to STACK
    if(isFull(s) == true)
        Error("STACK is FULL");
    else if(isFull(s) == false)
        s->data[++s->top] = value;
    else
        Error("Invaild Input");
}

char pop(STACK* s){
//pop out data from STACK and return data decreasing top value
    if(isEmpty(s) == true)
        Error("STACK is EMPTY");
    else if(isEmpty(s) == false)
        return s->data[(s->top)--];
    else
        Error("Invaild Input");
}

char peeks(STACK* s){
//pop out data from STACk and return data
    if(isEmpty(s) == true)
        Error("STACK is EMPTY");
    else if(isEmpty(s) == false)
        return s->data[s->top];
    else
        Error("Invaild Input");
}
