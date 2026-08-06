#include <stdio.h>
#include <string.h>

long double pow(long double x, int y);

int main(void)
{
	long double x;
	int y;

	do{

		printf("[Input x]: ");
		
		if(scanf("%Lf", &x) != 1){
			fprintf(stderr, "[ERROR]: Invalid Input\n");
			return -1;
		}

		printf("[Input y]: ");
	
		if(scanf("%d", &y) != 1){
			fprintf(stderr, "[ERROR]: Invalid Input\n");
			return -1;
		}
	
		printf("[Result]: %.12Lf\n\n", pow(x, y));

	}while(y != -1024);

	return 0;
}

long double pow(long double x, int y)
{
	long double temp = x;

	if(y > 0)
		for(int i = 0; i < y; i++)
			x *= temp;
	else
		for(int i = 0; i > y; i--)
			x /= temp;

	return x;
}
