#pragma once
#include "DES/DES.h"
#include <cstdint>
#include <vector>

class mode : protected DES{
private:
	constexpr int block_len = 8;

	uint64_t to_char(char*);
/*
protected:
	mode()  {};
	~mode() {};
*/
public:
	mode()	{};
	~mode() {};
	//Electric CodeBook mode
	std::vector<uint64_t> ECB(char*, uint64_t);

	int run(void);
};
