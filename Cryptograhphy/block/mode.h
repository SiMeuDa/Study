#pragma once
#include <string>
#include "caesar.h"
using namespace std;

class mode{
private:
	char** text;
	int b_count;
	int len;

	inline void common(string msg)
	{
		while(msg.length() % 4)
			msg.append("*");
		len = msg.length();
		b_count = len / 4;
		text = new char*[b_count];
		
		for(int i = 0; i < b_count; i++){
			text[i] = new char[5];
			for(int j = 0; j < b_count; j++)
				(text[i])[j] = msg[j + ((i * b_count)];
			(text[i])[4] = '\0';
		}
	}
public:
	string ECB(const char* msg, const char* key)
	{
		common(msg);
		string result = "";

		for(int i = 0; i < b_count; i++){
			result.append(/*c.crypto(text[i], ikey, false) need Encihper Logic*/);
			delete[] text[i];
		}
		delete[] text;
		len = 0;

		return result;
	}

	string enCBC(const char* msg, const char* key, const char* VI)
	{
		common(msg);
		string result = "";
		string temp;

		for(int i = 0; i < b_count; i++)
		{
			if(i == 0)
				//save VI for first block
				temp = VI;
			else
				//save before encryted block
				temp = text[i];
			

			for(int j = 0; j < 4; j++)
			{
				(text[i])[j] = (text[i])[j] ^ temp[j % temp.length()];
				//Encihper Logic
			}
			
			result.append(text[i]);
		}
		//free C-style string made for encihper lpgice
		for(int i = 0; i < b_count; i++)
			delete[] text[i];
		delete[] text;

		return result;
	}

	string deCBC(const char* msg, const char* key, const char* VI)
	{
		common(msg);
		string result = "";
		string temp, before;

		for(int i = 0; i < b_count; i++)
		{
			if(i == 0)
				//save VI for first block
				temp = VI;
			else
				//save before decryted block
				temp = before;

			//decihper logic

			before = text[i];
			
			for(int j = 0; j < 4; j++)
				(text[i]) = temp[j] ^ (text[i])[j];
		}
		//free C-style string made for decihper logic
		for(int i = 0; i < b_count; i++)
			delete[] text[i];
		delete[] text;
		before = "";
	
		return result;
	}
};
