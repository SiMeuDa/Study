#include "pran.h"
#include <iostream>

int main(void)
{
	prandom p;
	int size;

	std::vector<int> arr;
	std::cout << "size of vector: ";
	std::cin >> size;
	
	p.msqrt(arr, size);

	std::cout << "Middle Square Result: ";

	for(int i = 0; i < size; i++)
		std::cout << arr.at(i) << " | ";
	std::cout << std::endl;

	p.lcg(arr, size);

	std::cout << "Linear Conruential Result: ";
	for(int i = 0; i < size; i++)
		std::cout << arr.at(i) << " | ";
	std::cout << std::endl;

	return 0;
}
