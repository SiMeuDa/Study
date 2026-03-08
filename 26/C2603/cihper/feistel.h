#pragma once
#include <cstdint>
#include <vector>
#include "binary.h"

class feistel{
private:
//key scheduled for 16 -> feistel cac 16 times
	static constexpr int repeat = 16;
//key = 48 bit, size = 16
	std::vector<uint64_t> key;
//not for cipher, but in logic (was for hardware)
//Initial Permutation
	uint64_t IP(uint64_t);
//scheduling key for sub key
	void schedule(uint64_t);
//diffusion & confusion & key mix => main function
	uint32_t F(uint32_t, uint64_t);
//not for cipher, but in logic (was for hardware)
//Final Permutation
	uint64_t FP(uint64_t);
protected:
	feistel() {};
	~feistel(){};

	uint64_t cipher(uint64_t, uint64_t);
};

uint64_t feistel::IP(uint64_t msg)
{
	binary b(msg);
	binary result(msg);

	
}

uint64_t feistel::cipher(uint64_t msg, uint64_t key)
{
	uint32_t L, R, temp;
	uint64_t result;

	//do IP
	msg = IP(msg);

	//scheduling key
	schedule(key);
	
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
	
	//do FP
	result = FP(result);

	return result;
}
