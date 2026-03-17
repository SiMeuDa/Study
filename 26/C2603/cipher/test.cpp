#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

void printVector(vector<uint64_t> vec)
{
	for(auto it = vec.begin(); it != vec.end(); it++)
		cout << *it;
	cout << endl;
}

int main(void)
{
	mode m;
	string str;
	int select;
	uint64_t key;
	vector<uint64_t> result;

	//take plain text from user
	cout << "Plain Text: ";
	getline(cin, str);
	//take key from user
	cout << "Key: ";
	if(!(cin >> key))
	{
		cerr << "[Error]: Invalid Input" << endl;
		return -1;
	}

	cout << "Select operation mode(0: ECB, 1: CBC, 2: CFB, 3: OFB, 4: CTR)" << endl;
	cout << "select: ";
	if(!(cin >> select))
	{
		cerr << "[Error]: Invalid Input" << endl;
		return -1;
	}
	
	switch(select)
	{
	case 0:
		result = m.ECB(str, key);
		break;
	case 1:
		result = m.CBC(str, key);
		break;
	case 2:
		result = m.CFB(str, key);
		break;
	case 3:
		result = m.OFB(str, key);
		break;
	case 4:
		result = m.CTR(str, key);
		break;
	default:
		cout << "[Error]: Invalid Input" << endl;
	}
	cout << "Encryption: " << endl;
	printVector(result);
	cout << "Decryption: " << endl;


	switch(select)
	{
	case 0:
		str = m.ECB(result, key);
		break;
	case 1:
		str = m.CBC(result, key);
		break;
	case 2:
		str = m.CFB(result, key);
		break;
	case 3:
		str = m.OFB(result, key);
		break;
	case 4:
		str = m.CTR(result, key);
		break;
	default:
		cout << "[Error]: Invalid Input" << endl;
	}

	cout << str << endl << endl;


	return 0;
}
