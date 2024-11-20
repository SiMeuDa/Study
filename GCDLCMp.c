#include <stdio.h>
#include <math.h>
void gcdlcm(int* n1, int* n2);

int main(void)
{
	int num[2];
	
	scanf("%d%d", num + 0, num + 1);

	gcdlcm(&num[0], &num[1]);

	printf("%d %d\n", num[0], num[1]);

	printf("%c", 27);
}

void gcdlcm(int* n1, int* n2)
{
	int gcd = 1, lcm = (*n1) * (*n2);
	int i, j;
	
	for(i = 2; i <= sqrt(lcm); i++)
	{
		if(lcm % i == 0 && (*n1) % i == 0 && (*n2) % i == 0)
			gcd = i;
	}

	lcm = lcm / gcd;


	*n1 = gcd;
	*n2 = lcm;


}
