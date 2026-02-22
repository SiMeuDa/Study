#pragma once
#include <string>

class binary{
private:
//sharing constant
	//binary's len, default: 32bit
	static constexpr int len = 32;
	static constexpr double two_pow[len] = {
	//2^(index)
		1, 2, 4, 8,
		16, 32, 64, 128,
		256, 512, 1024, 2048,
		4096, 8192, 16384, 32768,
		65536, 131072, 262144, 524288,
		1048576, 2097152, 4194304, 8388608,
		16777216, 33554432, 67108864, 134217728,
		268435456, 536870912, 1073741824, 2147483648	
	};
	//binary string
	std::string bin;
public:
	binary operator!(void);
	binary operator++(int);
	binary operator--(int);
private:
	//make integer to binary string
	void setBinary(int num);

public:
	binary() {}
	binary(int num);				//make binary
	binary(const binary& other);	//copy construtor
	std::string getBinary(void);	//return bin
	friend int todecimal(const binary& other);
	friend std::string tohexa(const binary& other);
};

binary binary::operator!(void)
{
	for(int i = 0; i < len; i++)
	{
		if(this->bin[i] == '0')
			this->bin[i] = '1';
		else if(this->bin[i] == '1')
			this->bin[i] = '0';
	}

	return *this;
}

binary binary::operator++(int)
{
	for(int i = len - 1; i >= 1; i--)
	{
		++this->bin[i];
		if(this->bin[i] == '2' || this->bin[i] == '3')
		{
			++this->bin[i - 1];
			this->bin[i] -= 2;
		}
	}
	if(this->bin[0] == '2')
		--(this->bin[0]);

	return *this;
}

binary binary::operator--(int)
{
	int index = 0;
	for(int i = 0; i < len; i++)
		if(this->bin[i] == '1')
			index = i;

	this->bin[index] = '0';

	for(int i = index + 1; i < len; i++)
		this->bin[i] = '1';

	return *this;
}

void binary::setBinary(int num)
{
	if(num >= 0)	
	{
		bin = std::string(len, '0');
		for(int i = 0; i < len; i++)
		{
			if(num >= two_pow[len - 1 - i])
			{
				num -= two_pow[len - 1 - i];
				bin[i] = '1';
			}
		}
	}
	else if(num < 0)
	{//2's compliment
		bin = std::string(len, '1');

		num = -num;

		for(int i = 0; i < len; i++)
		{
			if(num >= two_pow[len - 1 -i])
			{
				num -= two_pow[len - 1 - i];
				bin[i] = '0';
			}
		}
		(*this)++;
	}

	return;
}

binary::binary(int num)
{
	setBinary(num);
}

binary::binary(const binary& other)
{
	this->bin = other.bin;
}

std::string binary::getBinary(void){	return bin;    }

int todecimal(const binary& other)
{
//if don't divide case, it cause overflow
	static int result;
	result = 0;

	bool signBit = 0;
	binary temp = other;

	if(other.bin[0] == '0')
	{//positive
		signBit = 0;
	}
	else if(other.bin[0] == '1')
	{//negative
		signBit = 1;
		!temp;
		temp--;
	}
	
	for(int i = 0; i < temp.len; i++)
		if(temp.bin[i] == '1')
			result += temp.two_pow[temp.len - 1 - i];
	if(signBit)
		result = -result;

	return result;
}

std::string tohexa(const binary& other)
{
	std::string result = "0x";
	const char hexa[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
	};
	int index = 0;

	for(int i = other.len / 4; i >= 0; i--)
	{
		for(int j = 4; j >= 0; j--)
			if(other.bin[i + j - 1] == '1')
				index += other.two_pow[j - 1];
		result.insert(3, hexa[index]);
	}

	return result;
}
