#include <stdio.h>

void input(int* in1, int* in2, int* in3);
void output(int* out1, int* out2, int* out3);

int main(void)
{
	int x, y, z;
	input(&x, &y, &z);
	output(&x, &y, &z);
}

void input(int* in1, int* in2, int* in3)
{
	scanf("%d%d%d", in1, in2, in3);
}

void output(int* out1, int* out2, int* out3)
{
	printf("%d %d %d\n", *out1, *out2, *out3);
}
