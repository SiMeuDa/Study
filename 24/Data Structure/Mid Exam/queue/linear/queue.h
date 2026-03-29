#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define true 1
#define false 0

typedef struct{
    int rear;
    int front;
    int data[MAX];
}QUEUE;


void Error(const char* message){
    fprintf(stderr, "\n[Error]: %s\n", message);
    exit(1);
}

void init_queue(QUEUE* q){
    q->rear = -1;
    q->front = -1;
    
    for(int i = 0; i < MAX; i++)
        q->data[i] = 0;

}

int isFull(QUEUE* q){
    if(q->rear == MAX - 1)
        return true;
    else if(q->rear < MAX - 1)
        return false;
}

int isEmpty(QUEUE* q){
    if(q->rear == q->front)
        return true;
    else if(q->rear > q->front)
        return false;
}

void enqueue(QUEUE* q, int value){
    if(isFull(q) == true)
        Error("QUEUE is FULL");
    else if(isFull(q) == false)
        q->data[++(q->rear)] = value;
}

int dequeue(QUEUE* q){
    if(isEmpty(q) == true)
        Error("QUEUE is EMPTY");
    else if(isEmpty(q) == false)
        return q->data[++(q->front)];
}

int peeks(QUEUE* q){
    if(isEmpty(q) == true)
        Error("QUEUE is EMPTY");
    else if(isEmpty(q) == false)
    {
        if(q->front != -1)
            return q->data[q->front];
        else if(q->front == -1)
            return q->data[++(q->front)];
    }
}
