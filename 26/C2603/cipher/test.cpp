#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;
	/*
	string msg;
	uint64_t key;
	cout << "msg: ";
	getline(cin, msg);

	cout << "key: ";
	cin >> key;

	vector<uint64_t> result = m.ECB(msg.c_str(), key);

	cout << "Encryption: ";
	for(auto it = result.begin(); it != result.end(); it++)
		cout << *it << " | ";
	cout << endl;
	std::string str;
	
	str = m.ECB(result, key);

	cout << "Decryption: " << str << endl;
	*/

	cout << (m.run()) << endl;
	/*
	   cout << "성공" << endl;
	else
		cout << "실패" << endl;
	*/
	return 0;
}
