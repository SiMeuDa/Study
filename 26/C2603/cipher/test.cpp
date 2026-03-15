#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;
	string msg;
	uint64_t key;
	cout << "msg: ";
	cin >> msg;
	cout << "key: ";
	cin >> key;

	vector<uint64_t> result = m.ECB(msg.c_str(), key);

	cout << "Output: ";
	for(auto it = result.begin(); it != result.end(); it++)
		cout << *it << " | ";
	cout << endl << endl;

	return 0;
}
