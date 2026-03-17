#pragma once
#include "DES/DES.h"
#include <cstdint>
#include <vector>
#include <string>
#include <thread>
#include <random>

class mode : protected DES{
private:
	constexpr static int block_len = 8;
	
	//padding: PKCS#7 Standard
	//do padding
	std::string padding(std::string);
	//do unpadding
	std::vector<uint64_t> unpadding(std::vector<uint64_t>);

	//change msg to integer msg(vector)
	std::vector<uint64_t> to_integer(std::string);
	//change integer msg(vector> to msg
	std::string from_integer(std::vector<uint64_t>);
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
	std::string ECB(std::vector<uint64_t>, uint64_t);
	//CounTeR
	//should fix it
	std::vector<uint64_t> CTR(std::string, uint64_t);
	std::string CTR(std::vector<uint64_t>, uint64_t);
	std::string run(std::string);

};
