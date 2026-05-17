#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
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
	double alpha[26];
	string buffer, file;

	for(int i = 0; i < 26; i++)
		alpha[i] = 0;

	fout.open("Freq_Result.txt", ios::out);
	if(!fout.is_open())
	{
		cerr << "Failed to Open Writing File" << endl;
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
			cerr << "Failed to Open Reading File" << endl;
			return -1;
		}


		if(count == 0)
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

			for(int j = 0; j < strLen; j++){
				if(buffer[j] > 'Z' || buffer[j] < 'A'){
					cerr << "Invalid Value" << endl;
					return -1;
				}
				++alpha[buffer[j] % 'A'];
			}
		}

		fin.close();
	
		for(int j = 0; j < 26; j++)
			alpha[j] = static_cast<double>(alpha[j] * 100) / count;
		
		fout << "Key = ";
		
		if(i < 10)
			fout << 0;
		else if(i < 20)
			fout << 1;
		else
			fout << 2;

		fout << i % 10 << "\n";

		for(auto num : alpha)
			fout << num << " ";
		
		fout << "\n";
	}
	fout << "\n";

	fout.close();

	return 0;
}
