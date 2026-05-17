#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "formula.h"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
		return -1;

	fstream fin;
	//count all alphabet
	uint16_t count = 0;
	double IC = 0, Chi = 0;
	formula f;
	int strLen;
	//check frequency
	uint16_t alpha[26];
	string buffer;

	for(int i = 0; i < 26; i++)
		alpha[i] = 0;

	//open file
	fin.open(argv[1]);
	if(!fin.is_open())
		return -1;
	
	//move to end
	fin.seekg(0, ios::end);
	//take count
	count = fin.tellg();
	//move to begin
	fin.seekg(0, ios::beg);

	//take line string
	while(getline(fin, buffer))
	{
		strLen = buffer.length();

		for(int i = 0; i < strLen; i++)
			++alpha[buffer[i] % 'A'];
	}

	fin.close();

	IC = f.IC(alpha, sizeof(alpha) / sizeof(alpha[0]), count);

	fin.open("Formula_Result.txt", ios::out);
	if(!fin.is_open())
		return -1;

	fin << "[RESULT]\n";
	fin << "IC: \t\t\t" << IC << "\n";
	fin << "N: \t\t\t\t" << count << "\n";

	fin.close();

	return 0;
}
