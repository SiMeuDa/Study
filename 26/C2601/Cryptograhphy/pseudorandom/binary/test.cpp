#include "fix.h"
//#include <iostream>
#include <cstdlib>
using namespace std;

inline void printBinary(binary b)
{
	string result = b.getBinary();

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
	if(argc == 1)
	{
		cerr << "[Error]: [file_name] [Decimal_Number]" << endl;
		return -1;
	}
	binary b(atoi(argv[1]));

	cout << "Input: " << to_decimal(b) << endl;
	cout << "Binary:" << endl;
	printBinary(b);
	
	b = !b;
	b++;
	cout << "Negative:" << endl;
	printBinary(b);

	b--;
	b = !b;
	cout << "Hexa: " << to_hexa(b) << endl;

	return 0;
}
