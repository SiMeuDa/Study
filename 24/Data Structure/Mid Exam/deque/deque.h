#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
}DEQUE;

void Error(const char* message){
    fprintf(stderr, "\n[Error]: %s\n", message);
    exit(1);
}

void init_deque(DEQUE* d){
    d->rear = 0;
    d->front = 0;
}

int isFull(DEQUE* d){
    if(d->front == (d->rear + 1) % MAX)
        return true;
    else
        return false;
}

int isEmpty(DEQUE* d){
    if(d->rear == d->front)
        return true;
    else
        return false;
}

void add_rear(DEQUE* d, int value){
    if(isFull(d) == true)
        Error("DEQUE is FULL");
    
    d->rear = (d->rear + 1) % MAX;
    d->data[d->rear] = value;
}

int delete_rear(DEQUE* d){
    int prev = d->rear;
    if(isEmpty(d) == true)
        Error("DEQUE is EMPTY");

    d->rear = (d->rear - 1 + MAX) % MAX;

    return d->data[prev];
}

int get_rear(DEQUE* d){
    if(isEmpty(d) == true)
        Error("DEQUE is EMPTY");
    
    return d->data[d->rear];
}

void add_front(DEQUE* d, int value){
    if(isFull(d) == true)
        Error("DEQUE is FULL");

    d->data[d->front] = value;
    d->front = (d->front - 1 + MAX) % MAX;
}

int delete_front(DEQUE* d){
    if(isEmpty(d) == true)
        Error("DEQUE is EMPTY");
    
    d->front = (d->front + 1) % MAX;
    return d->data[d->front];
}

int get_front(DEQUE* d){
    if(isEmpty(d) == true)
        Error("DEQUE is EMPTY");
    
    return d->data[d->front];
}
