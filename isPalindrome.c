#include <stdio.h>
#define MAX 101

int main(void)
{
    int size = 0;
    char word[MAX];

    scanf("%s", word);

    for(int i = 0; i < MAX; i++)
    {
        if(word[i] == '\0')
            break;
        size++;
    }
    for(int i = 0; i < size; i++)
    {
        if(word[i] != word[size - 1 - i])
        {
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");

    return 0;
}