#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "formula.h"
using namespace std;

int main(void)
{
	fstream f;
	string str, msg, file_name;
	uint16_t alpha[26];
	double chi[26];
	formula fm;

	for(int i = 0; i < 26; i++)
	{
		for(int j = 0; j < 26; j++)
			alpha[j] = 0;

		msg = "";
		str = "";
		file_name = "Decrypt_Result_";

		//open file name set
		if(i < 10)
			file_name.append(1, '0');
	
		file_name.append(to_string(i));
		file_name.append(".txt");

		f.open(file_name, ios::in);
		if(!f.is_open())
		{
			cerr << "Failed to open " << file_name << " file" << endl;
			return -1;
		}

		while(getline(f, msg))
			str.append(msg);

		f.close();

		uint16_t len = str.length();
		
		//count
		for(uint16_t j = 0; j < len; j++)
			++alpha[str[j] - 'A'];
		
		chi[i] = fm.Chis(alpha, sizeof(alpha) / sizeof(alpha[0]), len);
	}
	file_name = "Chi_result.txt";

	f.open(file_name, ios::out);

	if(!f.is_open())
	{
		cerr << "Failed to open " << file_name << " file" << endl;
		return -1;
	}

	for(int i = 0; i < 26; i++)
	{
		f << "Chi( key = " << i << "): ";
		if( chi[i] <= 200 )
			f << "# ";
		f << chi[i] << "\t";

		if(i % 2)
			f << "\n";
	}

	f.close();

	return 0;
}
