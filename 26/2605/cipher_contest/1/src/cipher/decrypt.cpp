#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include "cipher.h"
using namespace std;


int main(int argc, char* argv[])
{
	if(argc != 2 and argc != 3)
	{
		cerr << "Invalid Argument" << endl;
		return -1;
	}
	fstream fin, fout;
	string str, msg;
	cipher c;
	int i;
	i = 0;
	
	for(i; i < 26; i++)
	{
		fin.open(argv[1], ios::in);
		if(!fin.is_open())
		{
			cerr << "Failed to open " << argv[1] << "File" << endl;
			return -1;
		}

		string file_name = "Decrypt_Result_";
		//open file name set
		if(i < 10)
			file_name.append(1, '0');
	
		file_name.append(to_string(i));
		file_name.append(".txt");

		fout.open(file_name, ios::out);
		if(!fout.is_open())
		{
			cerr << "Failed to open " << file_name << " File" << endl;
			fin.close();
			return -1;
			cerr << "Failed to open " << file_name << " file" << endl;
			return -1;
		}

		while(getline(fin, str))
			fout << c.caesar(str, i, false);
		
		
		fin.close();
		fout.close();

		if(argc == 3)
			break;
	}

	return 0;
}
