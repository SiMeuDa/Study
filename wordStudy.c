#include <stdio.h>

#define wordLength 1000000000

int Max(int* a)
{
    int i, temp;

    for(i = 0 ;i < 26; i++)
    {
        if(a[i] - a[i - 1] > 0)
            temp = i;
        else if (a[i] - a[i - 1] < 0)
            a[i] = a[i - 1];
        else if (a[i] - a[i - 1] == 0)
            return -1;
    }
    return temp;
}

int main(void)
{
    int i, j, count[26];
    char word[wordLength], alphabet[26];

    for(i = 0; i < 26; i++)
    {
        alphabet[i] = 'a' + i;
        count[i] = 0;
    }

    scanf("%s", word);

    for(i = 0; word[i] != '\0'; i++)
    {
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 'a' - 'A';
        for(j = 0; j < 26; j++)
            if(alphabet[j] == word[i])
                count[j]++;
    }
    int abc = Max(count);

    if(abc == -1)
    {
        printf("?\n");
        return 0;
    }
    
    printf("%c", alphabet[abc] - 32);

    return 0;
}