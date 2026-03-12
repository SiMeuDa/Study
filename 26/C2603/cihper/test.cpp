#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>
#include "DES.h"
using namespace std;

int main(void)
{
	uint64_t key, m;
	string msg;
	cout << "msg: ";
	cin >> msg;
	cout << "key: ";
	cin >> key;
	int len = msg.length();

	for(int i = 0; i != len; i++)
		m += ((static_cast<uint64_t>(msg[i] & 0xFF)) << len - 2 * i - 2);
	
	DES des;

	m = des.cipher(m, key);

	cout << "Output: " << m << endl;

	return 0;
}
