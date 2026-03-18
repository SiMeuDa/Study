#include "cipher.h"
#include <iostream>
#include <cctype>
#include <cmath>
using namespace std;

bool strDigit(std::string);
void getNum(uint64_t&);
void Menu(void);


int main(int argc, char* argv[])
{
	cipher c;
	uint64_t key;
	string msg;
	vector<uint64_t> vecResult;
	string strResult;
	if(argc >= 2)
	{
		bool isExist[4] = {false, false, false, false};
		int index = 3;
		try{
			//check msg parameter
			if(argv[1] == "-m")
				isExist[0] = true;
			//check key parameter
			for(int i = index; i < argc; i++)
			{
				if(argv[i] == "-k")
				{
					isExist[1] = true;
					index = i + 1;
					break;
				}
			}
			
			string strKey = argv[index];
			//overflow check
			if(strKey.length() < 20)
				isExist[2] = true;
			else if(strKey.length() == 20)
			{
				const char* uint64_max[20] = {
					'1', '8', '4', '4',
					'6', '7', '4', '4',
					'0', '7', '3', '7',
					'0', '9', '5', '5',
					'1', '6', '1', '5'
					};
				for(int i = 0; i < 20; i++)
				{
					if(strKey[i] < uint64_max[i])
						isExist[2] = true;
					else if(strKey[i] > uint64_max[i])
					{
						isExist[2] = false;
						break;
					}
					
				}
			}

			//Check En/Decryption parameter
			if(argv[index + 1] == "-en")
				isExist[3] = true;
			for(int i = 0; i < 4; i++)
				if(!isExist[i])
					throw("Error");

		}catch(const char* msg)
		{
			//Terminate in error sequence
			cerr << "[" << msg << "]: Usage: [file_name] -p [message] -k [integer key] -en [1/0]" << endl;
			return -1;
		}
		
		string num = argv[index];
		key = static_cast<uint64_t>(num);
		for(int i = 2; i < index - 1; i++)
			msg.append(argv[i]);
		if(argv[argc - 1] == "1")
			vecResult = c.encryption(msg, key);
		else
			vecResult = c.decryption(msg, key);
		
		cout << "[Result]: " << endl;

		for(auto it = vecResult.begin(); it != vecResult.end(); it++)
			cout << *it;
		cout << "\n";

		return 0;
		}
	/*
	while(true)
	{
		
	}
*/
	return 0;
}

bool strDigit(std::string str)
{
	int len = str.length();

	for(int i = 0; i < len; i++)
		if(!isdigit(str[i]))
			return false;
	return true;
}

void getNum(uint64_t& num)
{
	num = 0;

	string input;

	if(!(getline(cin, input)))
		return;

	if(!(input.find("0x") == string::npos))
	{//is hexa
		static char hexa[16] = {
			'0', '1', '2', '3',
			'4', '5', '6', '7', 
			'8', '9', 'A', 'B', 
			'C', 'D', 'E', 'F'
		};
		//erase 0x
		input.erase(0, 2);

		int len = input.length();
		int i, j;
		for(i = 0; i < len; i++)
		{
			for(j = 0; j < 16; j++)
			{
				if(islower(input[i]))
					input[i] = toupper(input[i]);
				if(input[i] == hexa[j])
					break;
			}
			num += static_cast<uint64_t>(pow(j, len - 1 - i));
		}
	}
	else if(strDigit(input))
		num = static_cast<uint64_t>(stoi(input));
	return;
}

void Menu(void)
{
}
