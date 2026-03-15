#include "mode.h"

std::string mode::padding(std::string msg)
{	
	//copy msg
	std::string result = msg;
	//take padding number(PKCS#7 Standard)
	int padding_num = block_len - (result.length() % block_len);
	//do padding(PKCS#7 Standard)
	for(int i = 0; i < padding_num; i++)
		result.push_back(static_cast<char>(padding_num));

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
	//resize & initalize vector
	result.resize(block_count, 0);
	//save string each block
	//casting to uint64_t(unless msg casted to 32bit)
	//shift 8 * (8 - j - 1)
	for(int i = 0; i < block_count; i++)
		for(int j = 0; j < block_len; j++)
			result.at(i) |= (static_cast<uint64_t>(static_cast<unsigned char>(msg[block_len * i + j])) << ((sizeof(uint64_t) / sizeof(char)) * (block_len - j - 1)));

	return result;
}

std::vector<uint64_t> mode::ECB(std::string msg, uint64_t key)
{
	//change msg to integer vector
	std::vector<uint64_t> imsg = to_integer(msg.c_str());
	
	std::thread* t = new std::thread[imsg.size()];
	if(t == nullptr)
	{
		imsg.erase();
		return imsg;
	}

	for(int i = 0; i < imsg.size(); i++)
		t[i] = std::thread(cipher(imsg.at(i), key));

	for(int i = 0; i < imsg.size(); i++)
		t[i].join();

	delete[] t;
	
	return imsg;
}
