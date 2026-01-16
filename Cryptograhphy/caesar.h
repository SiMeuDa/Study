#pragma once
#include <cstring>

class caesar
{
private:
	int key;

	char* text;

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
public:
	caesar(int k = 0){
		if(k > 26)
			k = k % 26; //key = key mod 26
		key = k;
	}

	~caesar(){key = 0;}

	char* crypto(char* str)
	{

		text_copy(str);
		for(int i = 0; text[i] != '\0'; i++)
		{
			text[i] += key;

			if(text[i] > 'Z')
				text[i] -= 26;
		}

		return text;
	}
};
