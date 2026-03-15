#include <iostream>
#include <bitset>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;
	string str;
	getline(cin, str);

	cout << (str == m.run(str)) << endl;
	/*
	if(m.run(str))
	   cout << "성공" << endl;
	else
		cout << "실패" << endl;
	*/
	return 0;
}
