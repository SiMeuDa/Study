#include "mode.h"
#include <iostream>
using namespace std;

int main(void)
{
	mode m;

	string msg, key;

	cout << "msg: ";
	cin >> msg;

	cout << "key: ";
	cin >> key;

	cout << "result: " << m.ECB(msg.c_str(), key.c_str()) << endl;

	return 0;
}
