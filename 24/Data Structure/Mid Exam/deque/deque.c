#include "deque.h"

void print_deque(DEQUE* d){
    printf("DEQUE(front:%d rear:%d): ", d->front, d->rear);

    while(isEmpty(d) == false){
        int i = d->front;
        do{
            i = (i + 1) % MAX;
            printf("%d|", d->data[i]);
            if(d->rear == i)
                break;
        }while(i != d->front);
    }
    printf("\n");
}

int main(void){
    DEQUE d;
    init_deque(&d);

    for(int i = 0; i < 3; i ++)
    {
        add_front(&d, i);
        print_deque(&d);
    }

    for(int i = 0; i < 3; i++)
    {
        delete_rear(&d);
        print_deque(&d);
    }

    return 0;
}
