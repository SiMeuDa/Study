#include "cipher.h"


void setParity(uint64_t& msg)
{
	for (int i = 0; i < 8; i++)
    {
    	uint8_t group = (msg >> (i * 8)) & 0xFF;

 	    int ones = std::bitset<8>(group).count();

        uint8_t parity = (ones % 2 == 0) ? 1 : 0;

        msg &= ~(1ULL << (i * 8));
        msg |=  ((uint64_t)parity << (i * 8));
    }
}

std::vector<uint64_t> encryption(std::string msg, uint64_t key)
{
	std::vector<uint64_t> result = 
}
