#include <stdio.h>
#define MAX 100
#define MIN 1


int Limit(int size);

int main(void)
{
    int N, i, j;
    
    scanf("%d", &N);
    if(Limit(N) != 0)
        return -1;

    for(i = 0; i < N - 1; i++)
    {
        for(j = i; j < N - 1; j++)
            printf(" ");

        for(j = N - i; j < N; j++)
            printf("*");
        printf("*");
        for(j = N - i; j < N; j++)
            printf("*");
        for(j = i; j < N - 1; j++)
            printf(" ");
        printf("\n");
    }

    for(i = N - 1; i >= 0; i--)
    {
        for(j = i; j < N - 1; j++)
            printf(" ");
        for(j = N - i; j < N; j++)
            printf("*");
        printf("*");
        for(j = N - i; j < N; j++)
            printf("*");
        for(j = i; j < N - 1; j++)
            printf(" ");

        printf("\n");
    }

    return 0;
}

int Limit(int size)
{
    if(size > MAX || size < MIN)
        return -1;
    
    return 0;
}