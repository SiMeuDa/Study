#pragma once
#include "DES/DES.h"
#include <cstdint>
#include <vector>
#include <string>
#include <thread>

class mode : protected DES{
private:
	constexpr static int block_len = 8;
	std::vector<uint64_t> mstr;

	//do padding
	std::string padding(std::string);

	//change msg to integer msg(vector)
	std::vector<uint64_t> to_integer(std::string);

/*
protected:
	mode()  {};
	~mode() {};

	//Electric CodeBook mode
	std::vector<uint64_t> ECB(std::string, uint64_t);
*/
public:
	mode()	{};
	~mode() {};
	//Electric CodeBook mode
	std::vector<uint64_t> ECB(std::string, uint64_t);
};
