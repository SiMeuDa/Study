#pragma once
#include <cstdint>
#include <vector>
#include <bitset>
#include <string>
#include "DES/DES.h"

class cipher : private mode{
private:
	void setParity(uint64_t&);
public:
	cipher() {}
	~cipher() {}

	std::vector<uint64_t> encryption(std::string, uint64_t);
	std::string decryption(std::vector<uint64_t>, uint64_t);
};

