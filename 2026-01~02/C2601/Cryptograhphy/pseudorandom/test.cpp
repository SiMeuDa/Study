#include "pran.h"
#include <iostream>

const std::vector<std::string> name = {
	"Middle Square Method",
	"Linear Conruential Generator",
	"Linear Feedback Shift Register",
	"Blum Blum Shub",
	"Mersenne Twister",
	"WELL",
	"ChaCha20 / Salsa20",
	"PCG Family",
	"xoshiro / xoroshiro"
};

int main(void)
{
	prandom p;
	int size, select;

	std::vector<int> arr;
	std::cout << "size of vector: ";
	if(!(std::cin >> size))
	{
		std::cerr << "[Error]: Invaild Input" << std::endl;
		return -1;
	}
	
	std::cout << "========== Select Method ==========" << std::endl;
	for(int i = 0; i < name.size(); i++)
		std::cout << name.at(i) << " : " << i << std::endl;
	std::cout << "===================================" << std::endl;

	while(true)
	{
		std::cout << "Select: ";
		if(!(std::cin >> select)){
			std::cerr << "[Error]: Invaild Input" << std::endl;
			return -1;
		}
		else if(select <= 8 && select >= 0)
			break;
		else
			std::clog << "[System]:You should select on list" << std::endl;
	}
	
	std::cout << name.at(select) << " Result: ";

	switch(select)
	{
	case 0:
		p.msqrt(arr, size);
		break;
	case 1:
		p.lcg(arr, size);
		break;
	default:
		std::cout << "[System]: On Working" << std::endl;
		return 0;
	}


	for(int i = 0; i < size; i++)
		std::cout << arr.at(i) << " | ";
	std::cout << std::endl;

	return 0;
}
