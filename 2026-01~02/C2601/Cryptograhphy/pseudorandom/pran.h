#pragma once
#include <random>
#include <vector>
#include <cmath>
#include <string>
#include "binary.h"


class prandom : private binary{
private:
	std::vector<uint32_t> seed;
	inline static int count = 0;
	void setSeed(void);
	void padding(std::string& str, int& len);
	bool isCoprime(int x, int y);
public:
	prandom() : seed(4){ setSeed(); }
	~prandom() {}

//Middle-Squae Method
	void msqrt(std::vector<int>& arr, int size);
//Linear Congruential Generator
	void lcg(std::vector<int>& arr, int size);
//Linear Feedback Shift Register
// 			==
//Tausworthe Generator
	void lfsr(std::vector<int>& arr, int size);
};

void prandom::setSeed(void)
{	
//using device entropy, generate seed value
	std::random_device rd;
	std::seed_seq sseq = {rd(), rd(), rd(), rd()};

	sseq.generate(this->seed.begin(), this->seed.end());
}

bool prandom::isCoprime(int x, int y)
{
	while(y != 0)
	{//Euclidean algorithm => GCD
		int r = x % y;
		x = y;
		y = r;
	}
	//if GCD == 1, it is coprime
	return (x == 1);
}

void prandom::padding(std::string& str, int& len){
	for(int i = len; i >= 0; i--, len++)
		str.insert(0, "0");
	return;
}

void prandom::msqrt(std::vector<int>& arr, int size)
{
	if(size <= 0)	//size check
		return;

//make empty string for sqrt
	std::string str;
	arr.resize(size);
//take seed.
	str = std::to_string((int)(this->seed.at(((count++) % 4))));
	int len, start, temp;

	for(int i = 0; i < size; i++)
	{
		len = str.length();
		if(len < 4)
			padding(str, len);
		if(len & 1)	//isOdd
			start = len / 2 - 1;
		else	//isEven
			start = len / 2 - 2;
	//change value
		for(int j = 0; j < 4;j ++)
			str[j] = str[j + start];
	//limit length of string
		str.resize(4);
	//save vector value
		arr.at(i) = stoi(str);
	//if 0, change value to entropy value
		if(arr.at(i) == 0)
			arr.at(i) = (int)(this->seed.at(count++ % 4));
	//temp vari for sqrt & to_string
		temp = arr.at(i) * arr.at(i);
	//change to string
		str = std::to_string(temp);
	}
	return;
}

void prandom::lcg(std::vector<int>& arr, int size)
{
	if(size <= 0)	//size check
		return;
	arr.resize(size);
	
	//X(n + 1) = (aX(n) + c) mod m
	long long X, a, c, m;
	X = this->seed.at(count++ % 4);
	a = 1103515245;	//most used constant
	m = 2147483648;	//most used constant
	do{
		c = this->seed.at(count++ % 4);
	}while(c % 2);	//c and m must coprime

	for(int i = 0; i < size; i++)
	{	//main calculate
		X = (X * a + c) % m;

		arr.at(i) = static_cast<int>(X);	//arr == int vector
	}

	return;
}

void prandom::lfsr(std::vector<int>& arr, int size)
{
	if(size <= 0)
		return;	//size check
	arr.resize(size);
//tap index 31, 21, 1, 0
	std::vector<int> tindex = {0, 10, 30, 31};

//make binary with seed value
	binary b(this->seed.at(count++ % 4));
	
	std::string bin;
	int c;
	for(int j = 0; j < size; j++)
	{
		if(j != 0)
			binary b(bin);
		else
			binary b(this->seed[count++ % 4]);
		c = 0;
		//take binary string
		bin = b.getBinary();
		for(int i = 0; i < 4; i++)
			if(bin[tindex.at(i)] == '1')	//1 count
				c++;
		//register shift
	 	b << 1;
		//take value after shift
		bin = b.getBinary();

		//xor calculate
		if(c % 2)	//c is Odd
			bin[31] = '1';
		else
			bin[31] = '0';
		//ensure positive value
		bin[0] = '0';
		
		//translate to Decimal
		arr.at(j) = getDecimal(b, bin);
	}

	return;
}
