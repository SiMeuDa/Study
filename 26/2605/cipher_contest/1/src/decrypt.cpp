#include <iostream>
#include <fstream>
#include "caesar.h"
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
		return -1;

	fstream fin, fout;
	string str, file;
	caesar c;
	
	fin.open(argv[1], ios::in);
	
	for(int i = 0; i < 26; i++)
	{
		file = "Decrypt_Result_";

		if(i < 10)
			file.append(1, '0');
		else if(i < 20)
			file.append(1, '1');
		else
			file.append(1, '2');

		file.append(1, static_cast<char>((i % 10) + '0'));

		file.append(".txt");

		fin.open(argv[1], ios::in);
		fout.open(file, ios::out);
		
		if(!(fin.is_open() || fout.is_open()))
			return -1;

		while(getline(fin, str))
		{
			fout << c.decrypto(str.c_str(), i, false);
			fout << "\n";
		}

		fin.close();
		fout.close();
	}

	return 0;
}
