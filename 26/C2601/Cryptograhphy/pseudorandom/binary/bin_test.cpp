#include <iostream>
#include "binary.h"
#include <cstdlib>
#include <cctype>

bool isstrdigit(char* str)
{
	for(int i = 0; str[i] != '\0'; i++)
		if(!isdigit(str[i]) && str[i] != '-')
			return false;
	return true;
}

void Menu(int& select)
{
	bool isRepeat = false;
	std::cout << "========== BINARY CLASS TEST SYSTEM ==========" << std::endl;
	std::cout << "1.\tCheck Input" << std::endl;
	std::cout << "2.\tPrint Binary" << std::endl;
	std::cout << "3.\tPrint Hexa" << std::endl;
	std::cout << "4.\tRight Shift" << std::endl;
	std::cout << "5.\tLeft Shift" << std::endl;
	std::cout << "6.\tSum Value" << std::endl;
	std::cout << "7.\tTerminate Program" << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << "Select: ";
	do{
		if(isRepeat)
			std::clog << "[System]: Select between 1 - 7" << std::endl;
		if(!(std::cin >> select))
		{
			std::cerr << "[Error]: Invaild Input" << std::endl;
			exit(1);
		}
	} while(select < 0 || select > 7);
	std::cout << std::endl;
}

void printBinary(binary b)
{
		std::string result = b.getBinary();

		for(int i = 1; i <= result.length(); i++)
		{
			std::cout << result[i - 1];
			if(!(i % 4))
				std::cout << " | ";
		}

		return;
}

int main(int argc, char* argv[])
{
	if((argc == 1) || !isstrdigit(argv[1]))
	{
		std::cerr << "[System] Usage: ./[file_name] [decimal_number]" << std::endl;
		return 0;
	}
	int select = 1;
	int shift = 0;
	bool isPlay = true;
	binary b(atoi(argv[1]));
	
	while(isPlay)
	{
		Menu(select);
		switch(select)
		{
		case 1:
			std::cout << "[System] Your Decimal Input: " << getDecimal(b) << std::endl;
			break;
		case 2:
			std::cout << "[System] Binary Result: ";
			printBinary(b);
			break;
		case 3:
			std::cout << "[System] Hexa Result: " << getHexa(b) << std::endl;
			break;
		case 4:
			std::cout << "[System]: How many did you shift(right): ";
			if(!(std::cin >> shift))
			{
				std::cerr << "[Error]: Invaild Input" << std::endl;
				return -1;
			}
			b >> shift;
			std::cout << "[System] Binary Result: ";
			printBinary(b);
			break;
		case 5:
			std::cout << "[System]: How many did you shift(left): ";
			if(!(std::cin >> shift))
			{
				std::cerr << "[Error]: Invaild Input" << std::endl;
				return -1;
			}
			b << shift;
			std::cout << "[System] Binary Result: ";
			printBinary(b);
			break;
		case 6:
			std::cout << "[System] Sum value: " << std::endl;
			if(!(std::cin >> shift))
			{
				std::cerr << "[Error]: Invaild Input" << std::endl;
				return -1;
			}
			b + shift;
			printBinary(b);
			break;
		case 7:
			isPlay = false;
			break;
		}
		std::cout << std::endl << std::endl;
	}
			
	return 0;
}
