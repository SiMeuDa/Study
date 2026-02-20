#include "stack.h"

void print_stack(STACK* s)
{
    for(int i = 0; i < MAX/2; i++)
    {
        if(i > s->top)
            printf("%3c|", ' ');
        else
            printf("%3d|",s->data[i]);

        if((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");

}

int main(void)
{
    STACK s;
    init_stack(&s);

    for(int i = 0; i < MAX/2; i++)
    {
        push(&s, i);
        print_stack(&s);
    }
    for(int i = 0; i < MAX/2; i++)
    {
        pop(&s);
        print_stack(&s);
    }
        
    return 0;
}
