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

int main(int argc, char* argv[])
{
	if((argc == 1) || !isstrdigit(argv[1]))
	{
		std::cerr << "[Usage]: ./[file_name] [decimal_number]" << std::endl;
		return 0;
	}

	binary b(atoi(argv[1]));
	std::cout << "Binary Result: ";
	std::string result = b.getBinary();

	for(int i = 1; i <= result.length(); i++)
	{
		std::cout << result[i - 1];
		if(!(i % 4))
			std::cout << " | ";
	}
	std::cout << std::endl;

	std::cout << "Hexa Result: " << b.getHexa() << std::endl;

	return 0;
}
