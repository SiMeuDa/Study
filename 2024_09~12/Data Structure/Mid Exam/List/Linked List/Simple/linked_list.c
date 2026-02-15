#include "linked_list.h"

void print_list(LinkedList* head){
    for(LinkedList* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

int main(void)
{
    LinkedList* head = NULL;

    for(int i = 0; i < 5; i++){
        head = insert_first(head, i);
        print_list(head);
    }

    printf("\n%d\n\n", get_length(head));

    for(int i = 0; i < 5; i++){
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}
