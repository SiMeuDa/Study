#include <stdio.h>
#include <stdlib.h>

void Error(const char* message){
    fprintf(stderr, "\n[Error]: %s\n", message);
    exit(1);
}

typedef struct Linknode{
    int data;
    struct Linknode* link;
}LinkedList;

int get_length(LinkedList* head){
    int count = 0;
    for(LinkedList* p = head; p != NULL; p = p->link)
        ++count;
    
    return count;
}

LinkedList* insert_first(LinkedList* head, int value){
    LinkedList* p = (LinkedList*)malloc(sizeof(LinkedList));
    
    if(p == NULL)
    {
        Error("Failed to allocate Memory");
        free(head);
    }
    
    p->data = value;
    p->link = head;
    
    head = p;
    
    return head;
}

LinkedList* insert(LinkedList* head, LinkedList* pre, int value ){
    LinkedList* p = (LinkedList*)malloc(sizeof(LinkedList));
    if(p == NULL)
    {
        Error("Failed to allocate Memory");
        free(head);
    }
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

LinkedList* delete_first(LinkedList* head){
    LinkedList* removed;
    if(head == NULL)   
        return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

LinkedList* delete(LinkedList* head, LinkedList* pre){
    LinkedList* removed;
    if(removed == NULL)
    {
        Error("Failed to allocate Memory");
        free(head);
    }
    removed = pre->link;
    pre->link = removed->link;
    free(removed);

    return head;
}
