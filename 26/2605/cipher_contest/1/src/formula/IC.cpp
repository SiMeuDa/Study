#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "formula.h"
using namespace std;

int main(int argc, char* argv[])
{
	fstream f;
	string str, msg;

	formula fm;
	uint16_t alpha[26], len;
	double IC = 0;

	for(int i = 0; i < 26; i++)
		alpha[i] = 0;

	try{
		if(argc != 2)
			throw invalid_argument("Invalid Argument");

		f.open(argv[1]);
		if(!f.is_open())
			throw logic_error("Failed to open File");
		
		while(getline(f, str))
			msg.append(str);

		f.close();

	}catch(const exception& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
	
	len = msg.length();

	for(int i = 0; i < len; i++)
		++alpha[msg[i] - 'A'];

	IC = fm.IC(alpha, sizeof(alpha) / sizeof(alpha[0]), len);

	cout << "IC: " << IC << endl;

	return 0;
}
