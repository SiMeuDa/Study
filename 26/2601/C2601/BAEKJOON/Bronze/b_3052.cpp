#include <iostream>
using namespace std;
#define DIV 42

int main(int argc, char* argv[])
{
	int input = 0;
	int temp, count = 0, i, j;
	int result[10] = {
		-1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1
		};

	for(i = 0; i < 10; i++)
	{
		if(!(cin >> input))
			return -1;
		result[i] = input % DIV;
	}
	
	for(i = 0; i < 10; i++)
	{
		temp = result[i];
		
		for(j = i + 1; j < 10; j++)
			if(temp == result[j])
				result[j] = -1;
	}

	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(result[j] < result[j + 1])
			{
				temp = result[j];
				result[j] = result[j + 1];
				result[j + 1] = temp;
			}
		}
	}
	
	for(i = 0; i < 10; i++)
		if(result[i] != -1)
			count++;

	cout << count;

	return 0;
}
