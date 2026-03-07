#include <iostream>
#define QTY 3
#define CAC(x, y, z)	\
	x + y * z			\

using namespace std;

int main(void)
{
	int output[QTY], money = 0;

	for(int i = 0; i < QTY; i++)
		cin >> output[i];
	
	if(output[0] == output[1])
	{
		if(output[0] == output[2])
			money = CAC(10000, output[0], 1000);
		else
			money = CAC(1000, output[0], 100);
	}
	else if(output[1] == output[2] || output[0] == output[2])
	{
		money = CAC(1000, output[2], 100);
	}
	else
	{
		int swap = output[0], i, j;

		//INSERTION SORT
		for(i = 1; i < QTY; i++)
		{
			swap = output[i];
			for(j = i - 1; j >= 0; j--)
			{
				if(output[j] > swap)
					output[j + 1] = output[j];
				else
					break;
			}
			output[j + 1] = swap;
		}

		money = CAC(0, output[QTY - 1], 100);
	}

	cout << money;

	return 0;
}
