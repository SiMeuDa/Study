#pragma once
#include <string>
#include <iostream>

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
	//check whether each index over 1 (check 2 or 3)
	void checkBinary(bool);
public:
	//binary & const binary& operator
	binary operator!(void);
	binary operator^(const binary& other);
	binary operator<<(int);
	binary operator>>(int);
	binary operator++(int);
	binary operator--(int);
	binary operator+(const binary& other);
	binary operator-(const binary& other);
private://set Binary
	//make integer to binary string
	void setBinary(int);

public:
	//constructor
	binary(void) {}
	binary(int);				//make binary
	binary(const binary&);			//copy construtor
	
	//function
	std::string getBinary(void);	//return bin
	friend int to_decimal(const binary&);
	friend std::string to_hexa(const binary&);

	//operator with integer parameter
	binary operator^(int);
	binary operator+(int);
	binary operator-(int);
};

void binary::checkBinary(bool isPlus)
{
	if(isPlus)
	{
		for(int i = len - 1; i >= 1; i--)
		{
			if(bin[i] == '2' or bin[i] == '3')
			{
				bin[i] -= 2;
				++bin[i - 1];
			}

		}
	}
	else
	{
		for(int i = len - 1; i >= 1; i--)
		{
			if(bin[i] == '/' or bin[i] == '.')
			{
				--bin[i - 1];
				bin[i] += 2;
			}
		}
	}

	return;
}

binary binary::operator!(void)
{
	binary result = *this;
	for(int i = 0; i < len; i++)
	{
		if(this->bin[i] == '0')
			result.bin[i] = '1';
		else if(this->bin[i] == '1')
			result.bin[i] = '0';
	}

	return result;
}

binary binary::operator^(const binary& other)
{
	binary result(0);
	for(int i = 0; i < len - 1; i++)
	{
		if(this->bin[i] == other.bin[i])
			result.bin[i] = '0';
		else
			result.bin[i] = '1';
	}
	return result;
}

binary binary::operator<<(int num)
{
	char signBit = this->bin[0];
	binary result = *this;
	result.bin.erase(num);
	result.bin.append(num, '0');
	result.bin[0] = signBit;

	return result;
}

binary binary::operator>>(int num)
{
	char signBit = this->bin[0];
	binary result = *this;

	return result;
}

binary binary::operator++(int)
{
	binary result = *this;
	++this->bin[len - 1];
	checkBinary(true);

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

binary binary::operator+(const binary& other)
{
	binary result;
	result.bin = this->bin;

	for(int i = len - 1; i >= 0; i--)
		if(other.bin[i] == '1')
			++(result.bin[i]);

	result.checkBinary(true);

	return result;
}

binary binary::operator-(const binary& other)
{
	binary result;
	result.bin = this->bin;

	for(int i = len - 1; i >= 0; i--)
		if(other.bin[i] == '1')
			--(result.bin[i]);
	
	result.checkBinary(false);

	return result;
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

int to_decimal(const binary& other)
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

std::string to_hexa(const binary& other)
{
	std::string result = "0x";
	const char hexa[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
	};
	int index = 0;

	for(int i = other.len / 4; i >= 1; i--)
	{
		for(int j = 0; j < 4; j++)
			if(other.bin[i * 4 - j - 1] == '1')
				index += other.two_pow[j];
		result.insert(2, 1, hexa[index]);
		index = 0;	
	}

	return result;
}

binary binary::operator+(int num)
{
	binary result(num);
	result = result + *this;

	return result;
}

binary binary::operator-(int num)
{
	binary result(num);
	
	result = *this - result;

	return result;
}
