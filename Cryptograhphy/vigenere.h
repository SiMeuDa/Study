#pragma once
#include <cstring>

class vigenere{
private:
	char* text;

	//copy origin text to memeber variable
	bool text_copy(char* text)
	{
		int t_len = strlen(text);

		this->text = new char[t_len + 1];
		if(this->text == nullptr)
			return true;

		for(int i = 0; i < t_len; i++)
			this->text[i] = text[i];
		this->text[t_len] = '\0';
		
		return false;
	}

	bool key_chck(char* key)
	{//check key whether upper case or others
		int len = strlen(key);

		for(int i = 0; i < len; i++)
			if(key[i] > 'Z' || key[i] < 'A')
				return true;
		return false;
	}
public:
	vigenere(){};
	~vigenere(){};

	//main function (may cause over head)
	char* cihper(char* msg, char* key){
		if(key_chck(key))
			return nullptr;
		
		int k_len = strlen(key);
		int msg_len = strlen(msg);
		if(text_copy(msg))
			return nullptr;

		static int j = 0;
		
	
		for(int i = 0; i < msg_len; i++)
		{
			text[i] += key[j] - 'A';
			if(text[i] > 'Z')
				text[i] -= 26;
			j++;

			if(j == k_len)
				j = 0;
		}

		j = 0;

		return text;
	}
};
