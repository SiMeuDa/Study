#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/// <summary>
/// no parameter and return random value 1 to 4
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int random(int max, int min) {
	return rand() % max + min;
}

/// <summary>
/// The function that sum all of array's value
/// Parameter is int pointer(int array), Return is int(sum)
/// </summary>
/// <param name="array"></param>
/// <param name="size"></param>
/// <returns></returns>
int sum(int* array, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += array[i];
	return sum;
}

/// <summary>
/// if you type 341 ('s' + 'u' + 'm') in main function, you can use sum function
/// This function sum the value that already printed in documents
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int sum_value(void)
{
	int n, value;
	static int sum = 0;
	printf("Size of Value Array : ");
	if (scanf_s("%d", &n) == 0)
		return -1;
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &value);
		sum += value;
	}
	return sum;
}
/// <summary>
/// Before End of this program, use this function.
/// scanf_s prevent buffer overflow and getchar can see print message before end this program.
/// </summary>
/// <param name=""></param>
void end(void) {
	int buffer_overflow;
	printf("아무 버튼이나 누르시오....\n");
	scanf_s("%d", &buffer_overflow);
	getchar();
}

int main(void)
{
	srand((unsigned)time(NULL));
	int n, scan[2], max, min;
	int* array = NULL;
	wchar_t Title[30] = L"Random";
	SetConsoleTitle(Title);

	printf("끝내기 위해선 ctrl + Z를 입력해주세요\n\n");

	//Take Max and Min value of Random function
	printf("랜덤 값의 최대, 최소값을 설정해주세요 (max 5 min 1 -> 5 1) : ");
	scan[0] = scanf_s("%d%d", &max, &min);
	if (scan[0] == 0)
	{
		printf("Invalid Input. Try Again\n");
		getchar();
		end();
		return 1;
	}
	else if (scan[0] == EOF)
	{
		end();
		return 1;
	}

	if (max < min)
	{
		int temp = max;
		max = min;
		min = temp;
	}

	while (1)
	{
		//Take array's size
		printf("몇 개의 숫자를 랜덤으로 뽑을까요 : ");
		//To use scanf's return value twice
		scan[1] = scanf_s("%d", &n);

		//if failed to take scanf value, stop program
		if (scan[1] == 0)
		{
			printf("Invalid Input. Try Again\n");
			end();
			scanf_s("%d", &n);
			return 1;
		}
		//if you want to stop this program, you should use ctrl + z
		else if (scan[1] == EOF)
			break;
		
		if (n == 's' + 'u' + 'm')
		{
			//To prevent buffer overflow by scanf_s in sum_value function
			printf("%d\n", sum_value());
			end();
			return 0;
		}
		//Allocate array's size for dynamic memory allocation
		array = (int*)malloc(sizeof(int) * n);

		//if allocation fail, stop program
		if (array == NULL)
		{
			printf("Failed to allocate dynamic memory\n");
			end();
			return 1;
		}


		printf("항목 별 랜덤 값 : ");
		//Take random array value from random function
		for (int i = 0; i < n; i++)
		{
			array[i] = random(max, min);
			//take and print
			printf("%3d", array[i]);
		}

		// Sum all array's value for function
		printf("\n총합 : %3d\n\n", sum(array, n));

		//free dynamic memory
		free(array);
	}
	end();
	return 0;
}