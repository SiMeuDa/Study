#pragma once
#include <cstdint>
#include <vector>
#include "DES.h"

class cipher : private DES{
private:
	void parity(uint64_t&);
public:
	cihper() {}
	~cihper() {}
};

void parity(uint64_t& key)
{
	volatile uint8_t compare;
	volatile uint64_t temp;

	for(int i = 0; i < 8; i++)
	{
		temp = key;
	
		//select 8bit for shift
		compare = (temp >> i) & 0xFF;
		
		//if compare is even, change parity
		if(compare & 0x02)
			key += (0x00000001) << i;
	}

//erase key info
	temp = 0;
	compare = 0;

	return;
}
