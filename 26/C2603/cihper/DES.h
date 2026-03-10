#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "binary.h"
#include "feistel.h"
#define TEST 0x00
class DES : private feistel{
private:
	std::vector<int64_t> subKey;
//not for cipher logic (was for hardware)
//Initial Permutation
	uint64_t IP(uint64_t);
//ket scheduling (64bit -> 48bit)
	void keySchedule(uint64_t);
//not for cipher logic (was for hardware)
//Final Permutation
	uint64_t FP(uint64_t);
#ifndef TEST
protected:
	//Make Sub Key vector
	DES() { subKey.resize(16);	}
	~DES();
#endif
#ifdef TEST
public:	
	DES(int64_t key){	
		subKey.resize(16);
		keySchedule(key);
	};	
	~DES() {};
	std::vector<int64_t> getSubKey(void) { return subKey;	}
#endif
};


uint64_t DES::IP(uint64_t msg)
{
	//Standard IP Table
	int table[64] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
		};
	binary origin(msg);
	binary change(msg);
	uint64_t result;

	for(int i = 0; i < 64; i++)
		change.bin[i] = origin.bin[table[i - 1]];

	result = change.to_integer();

	return result;
}

void DES::keySchedule(uint64_t key)
{
	//Standard Table
	int pc1_Ctable[28] = {
		57, 49, 41, 33, 25, 17,  9,
		 1,	58, 50, 42, 34,	26, 18,
		10,  2,	59, 51, 43, 35, 27,
		19, 11,  3,	60, 52, 44, 36
		};
	//Standard Table
	int pc1_Dtable[28] = {
		63, 55, 47, 39, 31, 23, 15,
		 7, 62, 54, 46, 38, 30, 22,
		 14, 6, 61, 53, 45, 37, 29,
		 21, 13,  5, 28, 20, 12, 4
		};
	//every sequence round count have different value
	//key num = feistel structure repeat count
	int round_table[16] = {
		1, 1, 2, 2,
		2, 2, 2, 2,
		1, 2, 2, 2,
		2, 2, 2, 1
	};
	//Standard Table (56bit -> 48bit)
	int pc2_table[48] = {
		14, 17, 11 , 24, 1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32
		};
	binary result(0, 48);
	binary temp(key, 64);
	binary binC(0, 28);
	binary binD(0, 28);

	//PC - 1
	for(int i = 0; i < 28; i++)
	{
		binC.bin[i] = temp.bin[pc1_Ctable[i] - 1];
		binD.bin[i] = temp.bin[pc1_Dtable[i] - 1];
	}

	temp.resize(56);
	
	for(int i = 0; i < 16; i++)
	{
		//Left Circular Shift
		binC = binC << round_table[i];
		binD = binD << round_table[i];

		for(int j = 0; j < 28; j++)
		{	//sum C, D to one string
			temp.bin[j] = binC.bin[j];
			temp.bin[j + 28] = binD.bin[j];
		}

		//PC - 2
		for(int j = 0; j < 48; j++)
			result.bin[j] = temp.bin[pc2_table[j] - 1];

		//save sub key
		this->subKey[i] = result.to_integer();
	}
}

uint64_t DES::FP(uint64_t msg)
{
	//Stanard FP Table (inverse metrix of IP table)
	int table[64] = {
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41,  9, 49, 17, 57, 25
		};
	binary origin(msg);
	binary change(msg);
	uint64_t result;

	for(int i = 0; i < 64; i++)
		change.bin[i] = origin.bin[table[i - 1]];

	result = change.to_integer();

	return result;
}
