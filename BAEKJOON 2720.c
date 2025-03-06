#include <stdio.h>
#include <stdlib.h>

#define Quater 25
#define Dime 10
#define Nickel 5
#define Penny 1

void printError(void)
{
    printf("[Error] : Failed to assign Memory\n");
    printf("Press any button to stop....\n");
    getchar();
}

int main(void)
{
    int money, try, coin[4] = {Quater, Dime, Nickel, Penny};
    int** quantity;

    printf("How many time repeat : ");
    scanf("%d", &try);
    
    quantity = (int**)malloc(sizeof(int*) * try);
    if(quantity == NULL)
    {
        printError();
        return -1;
    }

    for(int i = 0 ; i < try; i++)
    {
        quantity[i] = (int*)malloc(sizeof(int) * 4);
        if(quantity[i] == NULL)
        {
            free(quantity);
            printError();
            return -1;
        }
        printf("How much you take : ");
        scanf("%d", &money);

        for(int j = 0; j < 4; j++)
        {
            for(int k = 0;; k++)
            {
                if(money - k * coin[j] < 0)
                {
                    (quantity[i])[j] = k - 1;
                    money = money - (k - 1) * coin[j];
                    break;
                }
                else if(money - k * coin[j] == 0)
                {
                    (quantity[i])[j] = k;
                    money = money - k * coin[j];
                    break;
                }
            }
        }
    }

    for(int i = 0; i < try; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("%d ", (quantity[i])[j]);
        free(quantity[i]);
        printf("\n");
    }

    free(quantity);
    
    return 0;   
}