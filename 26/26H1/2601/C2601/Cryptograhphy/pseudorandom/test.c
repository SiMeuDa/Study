#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void printArray(int* data, size_t size);

int main(void)
{
	int* data;
	data = (int*)malloc(sizeof(int) * 10);
	if(data == NULL)
		return -1;

	for(int i = 0; i < 10; i++)
		if(!(scanf("%d", data + i)))
			return -1;
	printf("[Input]: ");
	printArray(data, 10);

	data = insertion(data, 10);

	printf("[Result]: ");
	printArray(data, 10);

	free(data);
	
	return 0;
}

void printArray(int* data, size_t size)
{
	for(size_t i = 0; i < size; i++)
		printf("[%d] ", data[i]);
	printf("\n");

	return;
}
