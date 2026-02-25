#pragma once
#include <iostream>
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
//check whether bool or something else
//when use in plus = true, in minus = false
	void checkBinary(bool);
public:
//operator
	binary operator! (void);
	binary operator^ (const binary& other);
	binary operator| (const binary& other);
	binary operator& (const binary& other);
	binary operator<< (int);
	binary operator>> (int);
	binary operator++ (int);
	binary operator-- (int);
	binary operator+ (const binary& other);
	binary operator- (const binary& other);
	binary operator* (const binary& other);
//constructor
	binary() {}
	binary(int);
	binary(const binary& other);
//return binary string
	std::string getBinary(void);
//change binary to decimal
	friend int to_decimal(const binary& other);
//change binary to hexa
	friend std::string to_hexa(const binary& other);
};

void binary::checkBinary(bool isPlus)
{
	if(isPlus)
	{//plus
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
	{//minus
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
	binary result;
	result.bin = std::string(len, '0');

	for(int i = 0; i < len; i++)
	{
		if(this->bin[i] == '1')
			result.bin[i] = '0';
		else if(result.bin[i] == '0')
			result.bin[i] = '1';
	}

	return result;
}

binary binary::operator^(const binary& other)
{
	binary result;
	result.bin = std::string(len, '0');

	for(int i = 0; i < len; i++)
	{
		if(this->bin[i] == other.bin[i])
			result.bin[i] = '0';
		else
			result.bin[i] = '1';
	}

	return result;
}

binary binary::operator|(const binary& other)
{
	binary result;
	result.bin = std::string(len, '0');

	for(int i = 0; i < len; i++)
	{
		if((this->bin[i] == '1') or (other.bin[i] == '1'))
			result.bin[i] = '1';
		else
			result.bin[i] = '0';
	}

	return result;
}

binary binary::operator&(const binary& other)
{
	binary result;
	result.bin = std::string(len, '0');

	for(int i = 0; i < len; i++)
	{
		if((this->bin[i] == '1') and (other.bin[i] == '1'))
			result.bin[i] = '1';
		else
			result.bin[i] = '0';
	}

	return result;

}

binary binary::operator<<(int num)
{
	binary result;
	result.bin = this->bin;
	char signBit = this->bin[0];

	result.bin.erase(0, num);
	result.bin[0] = signBit;
	result.bin.append(num, '0');

	return result;
}

binary binary::operator>>(int num)
{
	binary result;
	result.bin = this->bin;
	char signBit = this->bin[0];

	result.bin.erase(len - 1 - num, num);
	result.bin.insert(0, num, '0');
	result.bin[0] = signBit;

	return result;
}

binary binary::operator++(int)
{
	++(this->bin[len - 1]);
	checkBinary(true);

	return *this;
}

binary binary::operator+(const binary& other)
{
	binary result;
	result.bin = std::string(len, '0');
	bool carry = false;
	for(int i = this->len - 1; i >= 0; i--)
	{
	    bool A = (bool)(this->bin[i] - '0');
	    bool B = (bool)(other.bin[i] - '0');

	    //Sum
	    if(A ^ B ^ carry)
			result.bin[i] = '1';
		else
			result.bin[i] = '0';
		//Carry
	    carry = (A & B) | (carry & (A ^ B));
	}

	return result;
}

binary binary::operator-(const binary& other){	return (*this) + other;		}

binary binary::operator*(const binary& other)
{
	binary result(0);
	
	for(int i = 0; i < len; i++)
	{
		if(other.bin[i] == '1')
		{
			binary temp = (*this << len - 1 - i);

			result = result + temp;
		}
	}

	return result;
}

binary::binary(int num)
{
	char input;
	if(num >= 0)
	{
		bin = std::string(len, '0');
		input = '1';
	}
	else
	{
		bin = std::string(len, '1');
		input = '0';
		num = -num;
	}

	for(int i = 0; i < len; i++)
	{
		if(num >= two_pow[len - 1 - i])
		{
			num -= two_pow[len - 1 - i];
			bin[i] = input;
		}
	}

	//input is negative
	if(input == '0')
		*this = (*this)++;
}

binary::binary(const binary& other){	this->bin = other.bin;	}

std::string binary::getBinary(void){	return bin;		}

int to_decimal(const binary& other)
{
	int result = 0;
	bool isPlus = true;
	if(other.bin[0] == '1')
		isPlus = false;

	for(int i = 1; i < other.len; i++)
	{
		if(isPlus)
			if(other.bin[i] == '1')
				result += other.two_pow[other.len - 1 - i];
		else
			if(other.bin[i] == '0')
				result += other.two_pow[other.len - 1 - i];
	}

	if(!isPlus)
	{
		result++;
		result = -result;
	}

	return result;
}

std::string to_hexa(const binary& other)
{
	std::string result = "0x";

	char hex[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
		};
	int count = 0;
	for(int i = other.len - 1; i >= 0; i--)
	{
		if(other.bin[i] == '1')
			count += other.two_pow[4 - ((i + 1) % 4)];
		if(((i + 1) % 4 == 0) && i != other.len - 1)
		{
			result.insert(2, 1, hex[count]);
			count = 0;
		}
	}

	return result;
}
