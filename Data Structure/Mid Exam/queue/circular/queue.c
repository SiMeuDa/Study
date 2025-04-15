#include "circular_queue.h"

void print_queue(QUEUE* q){
    printf("QUEUE(front:%d rear:%d) = ", q->front, q->rear);

    if(isEmpty(q) == false)
    {
        int i = q->front;
        do{
            i = (i + 1) % MAX;
            printf("%d|" ,q->data[i]);
            if(i == q->rear)
                break;
        }while(i != q->front);
    }

    printf("\n");
}

int main(void)
{
    int element;
    QUEUE q;
    init_queue(&q);

    while(isFull(&q) == false)
    {
        scanf("%d", &element);
        enqueue(&q, element);
        print_queue(&q);
    }

    while(isEmpty(&q) == false)
    {
        element = dequeue(&q);
        printf("%d\n", element);
        print_queue(&q);
    }

    printf("Queue is Empty\n");

    return 0;
}
