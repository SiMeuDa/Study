#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
    int count;
}QUEUE;

void Error(const char* message){
    fprintf(stderr, "\n[Error]: %s\n", message);
    exit(1);
}

void init_queue(QUEUE* q){
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int isEmpty(QUEUE* q){
    if(q->front == q->rear)
        return true;
    else
        return false;
}

int isFull(QUEUE* q){
    if(q->front == (q->rear + 1) % MAX)
        return true;
    else
        return false;
}

void enqueue(QUEUE* q, int value){
    if(isFull(q) == true)
        Error("QUEUE is FULL");
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
}

int dequeue(QUEUE* q){
    if(isEmpty(q) == true)
        Error("QUEUE is EMPTY");
    q-> front = (q->front + 1) % MAX;

    return q->data[q->front];
}
