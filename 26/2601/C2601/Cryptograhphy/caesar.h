#pragma once
#include <cctype>
#include <string>

class caesar{
protected:
	inline char circular(char msg, int key)
	{
		int shift;
		if(isdigit(msg))
		{
			shift = key % 10;
			if(shift < 0)
				shift += 10;

			return (msg - '0' + shift) % 10 + '0';
		}
		shift = key % 26;
		
		if(shift < 0)
			shift += 26;

		if(isupper(msg))
			return (msg - 'A' + shift) % 26 + 'A';
		else if(islower(msg))
			return (msg - 'a' + shift) % 26 + 'a';

		return msg;
	}

public:
	caesar() {}
	~caesar() {}

	std::string crypto(const char* msg, volatile int& key, bool isErase = true)
	{
		std::string text = msg;
		int len = text.length();

		for(int i = 0; i < len; i++)
			text[i] = circular(text[i], key);
		
		if(isErase)
			key = 0;

		return text;
	}

	std::string decrypto(const char* msg, volatile int& key, bool isErase = true)
	{
		std::string text = msg;
		int len = text.length();
		volatile int nde_key = 10 - key;
		volatile int de_key = 26 - key;

		for(int i = 0; i < len; i++)
		{
			if(isalpha(text[i]))
				text[i] = circular(text[i], de_key);
			else if(isdigit(text[i]))
				text[i] = circular(text[i], nde_key);
		}

		de_key = 0;
		nde_key = 0;
		if(isErase)
			key = 0;

		return text;
	}
};
