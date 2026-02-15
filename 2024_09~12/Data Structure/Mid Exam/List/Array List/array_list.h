#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define true 1
#define false 0

typedef struct{
    int array[MAX];
    int size;
}ArrayList;

void Error(const char* message){
    fprintf(stderr, "\n[Error]: %s\n", message);
    exit(1);
}

void inti_arraylist(ArrayList* al){
    al->size = 0;
}

//check list is empty (ADT)
int isEmpty(ArrayList* al){
    if(al->size == 0)
        return true;
    else
        return false;
}

//check array is full (ADT)
int isFull(ArrayList* al){
    if(al->size == MAX)
        return true;
    else
        return false;
}

//get length (ADT)
int getEntry(ArrayList* al, int index){
    if(index < 0 || index >= al->size)
        Error("LOCATION ERROR");
    return al->array[index];
}

//insert last (ADT)
void insert_last(ArrayList* al, int value){
    if(al->size >= MAX)
        Error("LIST OVERFLOW");

    al->array[al->size++] = value;
}


//insert first (ADT)
void insert(ArrayList* al, int index, int value){
    if(isFull(al) == false && (index>= 0) && (index <= al->size)){
        for(int i = (al->size - 1); i >= index; i--)
            al->array[i + 1] = al->array[i];
        al->array[index] = value;
        al->size++;
    }
}

//delete element in index location (ADT)
int delete(ArrayList* al, int index){
    int value;

    if(index < 0 || index >= al->size)
        Error("LOCATION ERROR");
    value = al->array[index];
    for(int i = index; i < (al->size - 1); i++)
        al->array[i] = al->array[i + 1];
    al->size--;

    return value;
}
