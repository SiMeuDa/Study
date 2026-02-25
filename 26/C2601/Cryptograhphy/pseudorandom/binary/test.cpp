#include "binary.h"
#include <iostream>
#include <cstdlib>
using namespace std;

inline void printBinary(binary b)
{
	string result = b.getBinary();
	std::cout << '\t';
	for(int i = 0; i < 32; i++)
	{
		cout << result[i];
		if((i + 1) % 4 == 0)
			cout << " | ";
	}
	cout << endl;

	return;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cerr << "[Error]: [file_name] [First_Decimal_Number] [Second_Decimal_Number]" << endl;
		return -1;
	}
	binary a(atoi(argv[1]));
	binary b(atoi(argv[2]));


	cout << "Binary 1 : ";
	printBinary(a);
	
	cout << "Binary 2 : ";
	printBinary(b);
	binary c = a + b;
	cout << "Binary 1 + 2 : ";
	printBinary(c);

	c = a * b;
	cout << "Binary 1 * 2: ";
	printBinary(c);
	cout << "Hexa: " << to_hexa(c) << endl;

	return 0;
}
