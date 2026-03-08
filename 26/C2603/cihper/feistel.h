#pragma once
#include <cstdint>
#include <vector>
#include "binary.h"

class feistel{
private:
	uint32_t L, R;
	uint64_t key;
protected:
	feistel(uint64_t);
	~feistel();

	uint64_t cipher();
};

feistel::feistel(uint64_t msg, uint64_t key)
{
	uint32_t L, R, temp;
	L = ((msg >> 32) & 0xFFFFFFFF);
	R = (msg & 0xFFFFFFFF);
}

uint64_t feistel::cipher(void)
{
	uint64_t result;
	uint32_t temp;
	for(int i = 0; i < 16; i++)
	{
		temp = R;
		R = F(key[i], R);
		R = L ^ R;
		F = temp;
	}

	result = static_cast<uint64_t>(R) << 32;
	result += static_cast<uint64_t>(L);
	static_cast<volatile uint64_t>(key) = 0;
	static_cast<volatile uint32_t>(R) = 0;
	static_cast<volatile uint32_t>(L) = 0;

	return result;
}
