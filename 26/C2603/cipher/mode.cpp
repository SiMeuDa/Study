#include "mode.h"

std::string mode::padding(std::string msg)
{
	std::string result = msg;
	int padding_num = block_len - (result.length() % block_len);
	
	for(int i = 0; i < padding_num; i++)
		result.append(static_cast<char>(padding_num + '0'), 1);

	return result;
}

std::vector<uint64_t> mode::to_integer(std::string msg)
{
	//first do padding
	msg = padding(msg);
	//save char to integer result
	std::vector<uint64_t> result;
	//for using repeatence
	int block_count = msg.length() / block_len;
	//resize vector
	result.resize(block_count);
	//save string each block
	for(int i = 0; i < block_count; i++)
		for(int j = 0; j < block_len; j++)
			result.at(i) |= (msg[block_count * i + j] << ((sizeof(uint64_t) / sizeof(char)) * (block_len - j - 1)));

	return result;
}

int mode::run(void)
{
	uint64_t msg = 1234;
	uint64_t output;
	uint64_t key = 1234;

	output = cipher(msg, key);

	//decryption test
	if(msg == decipher(output, key))
		return 1;
	else
		return -1;
}

uint64_t mode::run(std::string msg)
{
	std::vector<uint64_t> result;

	result = to_integer(msg);

	return result.at(0);
}
