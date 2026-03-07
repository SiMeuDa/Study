#include <iostream>
#include <cstdint>
#include <iomanip>
using namespace std;

void parity(uint64_t& key)
{
	volatile uint8_t compare;
	volatile uint64_t temp;

	for(int i = 0; i < 8; i++)
	{
		temp = key;
	
		//select 8bit for shift
		compare = (temp >> (i * 4)) & 0xFF;
		
		//if compare is even, change parity
		if((compare & 0x02) || (compare == 0))
			key += ((0x00000001) << (i * 4));
		cout << "0x" << setw(8) << setfill('0') << hex << key << endl;
	}

//erase key info
	temp = 0;
	compare = 0;

	return;
}

int main(void)
{
	uint64_t test;
	cout << "input: ";
	cin >> test;

	parity(test);
	
	cout << test << endl;

	return 0;
}
