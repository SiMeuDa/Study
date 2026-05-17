#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <iomanip>
#include "formula.h"
using namespace std;

int main(int argc, char* argv[])
{
	fstream fin, fout;
	//count all alphabet
	uint16_t count = 0;
	double Chi = 0;
	formula f;
	int strLen;
	//check frequency
	uint16_t alpha[26];
	string buffer, file;

	for(int i = 0; i < 26; i++)
		alpha[i] = 0;

	fout.open("Chi_Result.txt", ios::out);
	if(!fout.is_open())
	{
		cerr << "HERE" << endl;
		return -1;
	}

	//open file
	for(int i = 0; i < 26; i++)
	{
		for(int k = 0; k < 26; k++)
			alpha[k] = 0;

		file = "Decrypt_Result_";

		if(i < 10)
			file.append("0");
		else if(i < 20)
			file.append("1");
		else
			file.append("2");

		file.append(1, static_cast<char>((i % 10) + '0'));

		file.append(".txt");

		fin.open(file, ios::in);
		if(!fin.is_open()){
			cerr << "HERE" << endl;
			return -1;
		}

		if(i == 0)
		{		
			//move to end
			fin.seekg(0, ios::end);
			//take count
			count = fin.tellg();
			//move to begin
			fin.seekg(0, ios::beg);
		}

		//take line string
		while(getline(fin, buffer))
		{
			strLen = buffer.length();

			for(int j = 0; j < strLen; j++)
				++alpha[buffer[j] % 'A'];
		}

		fin.close();


		Chi = f.Chis(alpha, sizeof(alpha) / sizeof(alpha[0]), count);

		fout << "Chi(";
		
		if(i < 10)
			fout << 0;
		else if(i < 20)
			fout << 1;
		else
			fout << 2;

		fout << i % 10 << "): \t";
		cout << fixed << setprecision(6) << Chi << "\n";
	}
	
	fout.close();

	return 0;
}
