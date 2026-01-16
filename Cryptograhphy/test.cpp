#include <iostream>
#include "caesar.h"
#include "vigenere.h"

int main(int argc, char** argv)
{
	if(argc == 1)
		return -1;
	int caesar_key = 0;
	std::cout << "카이사르 키: ";
	std::cin >> caesar_key;

	caesar c(caesar_key);
	std::cout << "========================== 카이사르 암호문 ============== 키: " << caesar_key << " =====" << std::endl << std::endl;
	
	std::cout << "원문: \t\t";
	
	for(int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	
	std::cout << std::endl;

	std::cout << "암호문: \t";
        for(int i = 1; i < argc; i++)
		std::cout << c.crypto(argv[i]) << " ";
       	
	std::cout << std::endl << std::endl;

	std::cout << "=======================================================================" << std::endl << std::endl << std::endl;


	char vigenere_key[100];
	std::cout << "비즈네르 키: ";
	std::cin >> vigenere_key;

	vigenere v;
	

	std::cout << "========================== 비즈네르 암호문 ============== 키: " << vigenere_key << " =====" << std::endl << std::endl;

	std::cout << "원문: \t\t";
	
	for(int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;

	std::cout << "암호문: \t";
	for(int i = 1; i < argc; i++)
		std::cout << v.cihper(argv[i], vigenere_key) << " ";
	std::cout << std::endl << std::endl;

	std::cout << "=======================================================================" << std::endl << std::endl << std::endl;
	
	return 0;
}
