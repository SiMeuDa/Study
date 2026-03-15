#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;
	string str;
	cin >> str;
	cout << bitset<64>( m.run(str)) << endl;
	/*
	if(m.run())
		cout << "SUCCESS" << endl;
	else
		cout << "FAIL" << endl;
	*/

	
	return 0;
}
