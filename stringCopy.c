#include <stdio.h>

void strcopy(char a[], char b[]);

char array_A[7], array_B[7];

int main(void)
{

	fgets(array_B, sizeof(array_B) , stdin);

	strcopy(array_A, array_B);

	printf("%s\n", array_A);

	return 0;
}

void strcopy(char a[], char b[])
{
	for (int i = 0; i < 7; i++)
		*(a + i) = *(b + i);
}