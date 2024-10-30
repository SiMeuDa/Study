#include <stdio.h>

int main(void)
{
	char str1[100] = {'0000'};
	char str2[100];
	int i, j;

	printf("어떤 문장을 출력할까요 : ");
	gets(str2);
	
	for (j = 0; j < 100; j++)
	{
		if (str2[j] == ' ')
		{
			str2[j] = '!';
		}
		for (i = '!'; i <= '~'; i++)
		{

			if (str2[j] == '\0')
			{
				break;
			}
			printf("%s%c\n", str1, i);
			if (i == str2[j])
			{
				str1[j] = i;
				if (str1[j] == '!')
				{
					str1[j] = '  ';
				}
				break;
			}
		}
	}
	
	printf("Result :%s\n", str1);

	return 0;
}