#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include "cipher.h"
using namespace std;

void take_klen(int&);
string is_dir(string);
string org_msg(const char*);

int main(int argc, char* argv[])
{
	int len, div = 26, start = 0, end;
	string msg, dir, name;
	cipher c;
	fstream fout;

	try{
		if(argc != 2)
			throw invalid_argument("Invalid Argument");
		
		take_klen(len);
		string key(len, 'A');
		string end(len, 'Z');
		//make dirctory for save result
		dir = is_dir(argv[1]);

		//take original message from file
		msg = org_msg(argv[1]);


	    while(key != end) 
   		{
			//file name set
			name = dir;
			name.append("/Decrypt_BruteForce_KEY_");
			
			//check key
			for(int k = len - 1; k > 0; k--)
			{
				if(key[k] >  'Z')
				{
					key[k] = 'A';
					++key[k - 1];
				}
			}

			name.append(key + ".txt");	

			fout.open(name, ios::out);
			if(!fout.is_open())
				throw ios_base::failure("Failed to open File");
			fout << c.vigenere(msg, key, false);
				
			fout.close();		

			key[len - 1]++;
		}

	}catch(const exception& e){
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}
    
	
	clog << "SUCCESS TO DO BRUTE FORCE ATTACK" << endl;

	return 0;

}

void take_klen(int& len)
{
	cout << "What is Key's Length: ";
	int l;
	cin >> l;
	
	len = l;
	cout << len << endl;
	if((len >= 1) && (len <= 5))
		return;
	else
		throw range_error("Out of Range");
}

string is_dir(string name)
{
	name.erase(name.end() - 4, name.end());
	name.append("_BruteForce");

	filesystem::create_directories(name);

	return name;
}

string org_msg(const char* path)
{
	fstream f;
	f.open(path, ios::in);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");
	string msg;
	string result;
	while(getline(f, msg))
		result.append(msg);

	return result;
}
