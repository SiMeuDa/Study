#include <cctype>
#include <string>

class caesar{
protected:
	inline char circular(char msg, int key)
	{
		int shift = key % 26;
		if(shift < 0)
			shift += 26;
		if(isdigit(msg))
			return (msg - '0' + shift) % 26 + '0';
		else if(isupper(msg))
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
		volatile int de_key = 26 - key;

		for(int i = 0; i < len; i++)
			text[i] = circular(text[i], de_key);

		de_key = 0;
		if(isErase)
			key = 0;

		return text;
	}
};
