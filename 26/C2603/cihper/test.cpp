#include <iostream>
#include "binary.h"
#include "DES.h"
#include <cstdint>
#include <bitset>
using namespace std;

int main(void)
{
	uint64_t value;
	cout << "input: ";
	cin >> value;

	DES des(value);

	cout << "sub Key: ";
	vector<int64_t> ret = des.getSubKey();
	cout << endl;
	for(int i = 0;i < 16; i++)
	{
		cout << "[" << i << "]: " << bitset<64>(ret.at(i)) << endl;
	}


	return 0;
}
