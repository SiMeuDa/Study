#include <stdio.h>

int count[26];

int main(void)
{
    int try = 0;
    char word[100];
    char alphabet[27];
    int i, j;
    for(i = 0; i < 100; i++)
    {
        count[i] = -1;
        if(i <= 25)
        {
            alphabet[i] = 97 + i;
        }
    }

    scanf("%s", word);
    
    for(i = 0; i < 100; i++)
    {
        if(word[i] == 0) break;
        for(j = 0; j <= 26; j++)
        {
            if(word[i] == alphabet[j])
            {
                count[try] = i;
            }
            try++;
        }
        try = 0;
    }
    
    for(i = 0; i <= 26; i++)
    {
        printf("%d ", count[i]);
    }
    printf("\n");

    return 0;
}