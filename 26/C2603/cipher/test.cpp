#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;
	string str;
	cout << "Plain Text: ";
	getline(cin, str);
	uint64_t key;
	cout << "Key: ";
	cin >> key;
	cout << "Result(DES): " << endl;
	std::vector<uint64_t> result = m.ECB(str, key);
	cout << "Encryption: ";
	for(auto it = result.begin(); it != result.end(); it++)
		cout << *it;

	cout << endl;

	cout << "Decryption: " << m.ECB(result, key) << endl;


	return 0;
}
