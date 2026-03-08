#pragma once
#include <cstdint>
#include <vector>
#include "binary.h"

class feistel{
private:
//key scheduled for 16 -> feistel cac 16 times
	static constexpr int repeat = 16;
//diffusion & confusion & key mix => main function
	uint32_t F(uint32_t, uint64_t);
protected:
	feistel() {};
	~feistel(){};

	uint64_t round(uint64_t, uint64_t);
};

uint64_t feistel::round(uint64_t msg, std::vector<uint64_t> key)
{
	uint32_t L, R, temp;
	uint64_t result
	
	//divide L, R for each 32bit
	L = static_cast<uint32_t>((msg >> 32) & 0xFFFFFFFF);
	R = static_cast<uint32_t>(msg & 0xFFFFFFFF);

	//feistel structure
	for(int i = 0; i < repeat; i++)
	{
		temp = R;
		R = F(R, key[i]);
		R = L ^ R;
		L = temp;
	}
	//sum for uint64_t
	result = static_cast<uint64_t>(R) << 32;
	result += static_cast<uint64_t>(L);

	//Memory info Erase
	*(volatile uint64_t*)&key = 0;
	*(volatile uint32_t*)&R = 0;
	*(volatile uint32_t*)&L = 0;
	*(volatile uint32_t*)&temp = 0;

	return result;
}
