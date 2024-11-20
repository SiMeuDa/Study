#include <stdio.h>
#define size 3

int* mid(int array[]);

int main(void)
{
	int array[size];

	for(int i = 0 ; i < size; i++) scanf("%d", &array[i]);

	printf("%d\n", *(mid(array)));

	return 0;
}

int* mid(int array[])
{
	int temp;
	if(array[0] > array[1])
	{
		//1.array[0] > 2.array[1] > 3.array[1]
		if(array[1] > array[2])
		{
			temp = array[2];
			array[2] = array[0];
			array[0] = temp;
		}
		else if(array[0] > array[2] && array[1] != array[2]) // array[1] < array[2]
		{
			// 1.array[0]> 2.array[2] > 3.array[1]
			temp = array[0];
			for(int i = 0; i < size - 1; i++) array[i] = array[i + 1];
			array[2] = temp;
		}
		else //array[0] > array[1] == array[2]
		{
			
			array[2] = array[0];
			array[0] = array[1];
		}
	}
	else if(array[0] < array[1])
	{
		if(array[1] < array[2])
		{
		//array[0] < array[1] < array[2]
			temp = array[0];
			array[0] = array[2];
			array[2] = temp;
		}
		else if(array[0] < array[2] && array[1] != array[2])
		{
		//array[0] < array[2] < array[1] cause else if
			temp = array[2];
			array[2] = array[1];
			array[1] = temp;
		}
	// array[0] < array[1] == array[2] no reason to change
	}
	else if(array[0] == array[1])
	{
		if(array[0] > array[2])
		{
			//array[0] = array[1] > array[2]
			array[0] = array[2];
			array[2] = array[1];
		}
	}


	return &array[1];
}
