#include "linear_queue.h"

void print_queue(QUEUE* q)
{
    for(int i = 0; i < MAX/2; i++)
    {
        if(i <= q->front || i > q->rear)
            printf("%3c|", ' ');
        else
            printf("%3d|",q->data[i]);

        if((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");

}

int main(void)
{
    QUEUE q;
    init_queue(&q);

    for(int i = 0; i < MAX/2; i++)
    {
        enqueue(&q, i);  
        
        print_queue(&q);
    }
    for(int i = 0; i < MAX/2; i++)
    {
        dequeue(&q);
        print_queue(&q);
    }

    return 0;
}
