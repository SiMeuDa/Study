#include <iostream>
#include "caesar.h"
#include "vigenere.h"

int main(void)
{
	caesar c;
	vigenere v;
	std::string msg, key;
//	int key;

	std::cout << "평문: ";
	getline(std::cin, msg);
	//std::cin.ignore();

	std::cout << "key: ";
	std::cin >> key;

	std::cout << "암호문: " << v.crypto(msg.c_str(), key.c_str()) << std::endl;
	std::cout << "복호문: " << v.decrypto(v.crypto(msg.c_str(), key.c_str()).c_str(), key.c_str()) << std::endl;

	return 0;
}
