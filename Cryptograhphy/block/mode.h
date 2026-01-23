#pragma once
#include <string>
#include "caesar.h"
using namespace std;

class mode{
private:
	char* text[4];
	int len;

	inline void common(string msg)
	{
		while(msg.length() % 4)
			msg.append("*");
		len = msg.length();
		
		for(int i = 0; i < 4; i++){
			text[i] = new char[len / 4 + 1];
			for(int j = 0; j < len / 4; j++)
				(text[i])[j] = msg[j + ((i * len) / 4)];
		}
	}
public:
	string ECB(const char* msg, const char* key)
	{
		common(msg);
		string result = "";

		for(int i = 0; i < 4; i++){
			result.append(/*c.crypto(text[i], ikey, false) need Encihper Logic*/);
			delete[] text[i];
		}
		len = 0;

		return result;
	}

	string CBC(const char* msg, const char* key, const char* VI, bool isEncrypt = true)
	{
		common(msg);
		string result = "";
		string temp;

		for(int i = 0; i < 4; i++)
		{
			if(i == 0)
				//save VI for first block
				temp = VI;
			else
				//save before encryted block
				temp = text[i];
			if(isEncrypt)
			{
			// Encihper

				for(int j = 0; j < len / 4; j++)
				{
					(text[i])[j] = (text[i])[j] ^ temp[j % temp.length()];
					//Encihper Logic
				}
			}
			else
			{
			//Decihper
				for(int j = 0; j < len / 4; j++)
				{
					//Decihper Logic


					(text[i])[j] = (text[i])[j] ^ temp[j % length()];
				}
			}

			result.append(text[i]);
		}
		//free C-style string made for encihper lpgice
		for(int i = 0; i < 4; i++)
			delete[] text[i];
	
		return result;
	}
};
