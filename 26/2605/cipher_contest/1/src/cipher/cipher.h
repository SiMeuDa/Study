#include <cstdint>
#include <vector>
#include <string>

class cipher{
private:
	inline char circular(char, int);
public:
	std::string vigenere(std::string, std::string, bool = true);
	std::string caesar(std::string, int, bool = true);
};

inline char cipher::circular(char cha, int shift)
{
	cha -= 'A';

	cha += shift;

	cha %= 26;

	return (cha + 'A');
}


std::string cipher::caesar(std::string msg, int key, bool isEncrypt)
{
	int len = msg.length();
	key = key % 26;

	if(!isEncrypt)
		key = 26 - key;

	for(int i = 0; i < len; i++)
		if(msg[i] <= 'Z' && msg[i] >= 'A')
			msg[i] = circular(msg[i], key);

	return msg;
}

std::string cipher::vigenere(std::string msg, std::string key, bool isEncrypt)
{
	int len = msg.length();
	int key_len = key.length();
	
	std::vector<int> vkey;
	vkey.resize(key_len);

	for(int i = 0; i < key_len; i++)
		vkey[i] = static_cast<int>(key[i] - 'A');

	if(!isEncrypt)
		for(int i = 0; i < key_len; i++)
			vkey[i] = 26 - vkey[i];

	for(int i = 0; i < len; i++)
		if(msg[i] <= 'Z' && msg[i] >= 'A')
			msg[i] = circular(msg[i], vkey[i % key_len]);

	return msg;
}
