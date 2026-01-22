#include <iostream>
#include "caesar.h"

int main(void)
{
	caesar c;
	std::string msg;
	int key;

	std::cout << "평문: ";
	std::cin >> msg;

	std::cout << "key: ";
	std::cin >> key;

	std::cout << "암호문: " << c.crypto(msg.c_str(), key) << std::endl;
	std::cout << "복호문: " << c.decrypto(msg.c_str(), key) << std::endl;

	return 0;
}
