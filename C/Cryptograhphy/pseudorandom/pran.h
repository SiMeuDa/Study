#pragma once
#include <random>
#include <vector>
#include <cmath>
#include <string>

class prandom{
private:
	std::vector<uint32_t> seed;
	static int count;
	void setSeed(void);
	bool isCoprime(int x, int y);
public:
	prandom() : seed(4){ setSeed(); }
	~prandom() {}

//Middle-Squae Method
	void msqrt(std::vector<int>& arr, int size);
//Linear Congruential Generator
	void lcg(std::vector<int>& arr, int size);
};

int prandom::count = 0;

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


void prandom::msqrt(std::vector<int>& arr, int size)
{
	bool error = true;
	try{//size check
		if(size <= 0)
			throw error;
	}catch(bool error){
		arr.resize(0);
		return;
	}
//make empty string for sqrt
	std::string str;
	arr.resize(size);
//set seed.
	str = std::to_string((int)(this->seed.at(((count++) % 4))));
	int len, start, temp;

	for(int i = 0; i < size; i++)
	{
		len = str.length();

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
		temp = pow(arr.at(i), 2);
	//change to string
		str = std::to_string(temp);
	}
	return;
}

void prandom::lcg(std::vector<int>& arr, int size)
{//X(n + 1) = (aX(n) + c) mod m
	long long X, a, c, m;
	X = this->seed.at(count++ % 4);
	a = pow(4, 10) + 1;
	m = pow(2, 31) - 1;
	do{
		c = this->seed.at(count++ % 4);
	}while((c % 2) && c < m);	//c and m must coprime

	for(int i = 0; i < size; i++)
	{
		X = (X * a + c) % m;

		arr.at(i) = (int)X;
	}

	return;
}
