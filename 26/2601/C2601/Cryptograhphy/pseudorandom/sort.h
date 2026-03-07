#pragma once

int* insertion(int* data, size_t size)
{
	int temp;
	for(size_t i = 0; i < size; i++)
	{
		for(size_t j = 0; j < size; j++)
		{
			temp = data[i];

			if(data[j] > data[i])
				for(size_t k = size - 1; k > j; k--)
					data[k] = data[k - 1];
		}
	}

	return data;
}

int* selection(int* data, size_t size)
{
	int min, temp;
	size_t index = 0;

	for(size_t i = 0; i < size; i++)
	{
		min = data[i];
		for(size_t j = i; j < size; j++)
		{
			if(min > data[j])
			{
				min = data[j];
				index = j;
			}
		}
		
		temp = data[i];
		data[i] = min;
		data[index] = temp;
	}

	return data;
}
