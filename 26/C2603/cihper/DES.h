#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "binary.h"
#include "feistel.h"

class DES : private feistel{
private:
//not for cipher logic (was for hardware)
//Initial Permutation
	uint64_t IP(uint64_t);
//ket scheduling (64bit -> 48bit)
	void keySchedule(uint64_t);
//not for cipher logic (was for hardware)
//Final Permutation
	uint64_t FP(uint64_t);
protected:
	DES();
	~DES();
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

void keySechdule(uint64_t key)
{

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
