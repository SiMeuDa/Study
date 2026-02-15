#pragma once
#include "caesar.h"

class vigenere : private caesar{
private:
public:
	vigenere() {}
	~vigenere() {}

	std::string crypto(const char* msg, const char* key)
	{
		std::string text = msg;
		std::string skey = key;
		int t_len = text.length();
		volatile int k_len= skey.length();

		int i, j = 0;
		for(i = 0; i < t_len; i++)
		{
			if(j == k_len - 1)
				j = 0;
			if(isdigit(skey[j]))
				text[i] = circular(text[i], (int)(skey[j] - '0'));
			else if(isalpha(skey[j]))
			{
				if(isupper(skey[j]))
					text[i] = circular(text[i], (int)(skey[i] - 'A'));
				else
					text[i] = circular(text[i], (int)(skey[j] - 'a'));
			}
			j++;
		}
		skey = "";
		k_len = 0;

		return text;
	}

	std::string decrypto(const char* msg, const char* key)
	{
		std::string text = msg, skey = key;
		int t_len = text.length();
		volatile int k_len = skey.length(), de_key;
		int i, j = 0;

		for(i = 0; i < t_len; i++)
		{
			if(j == k_len - 1)
				j = 0;
			if(isdigit(skey[j]))
				de_key = 10 - (int)(skey[j] - '0');
			else if(isalpha(skey[j]))
			{
				if(isupper(skey[j]))
					de_key = 26 - (int)(skey[j] - 'A');
				else
					de_key = 26 - (int)(skey[j] - 'a');
			}
			j++;

			text[i] = circular(text[i], de_key);
		}

		skey = "";
		k_len = 0;

		return text;
	}
};
