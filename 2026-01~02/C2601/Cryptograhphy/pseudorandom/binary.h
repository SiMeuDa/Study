#pragma once
#include <string>
class binary{
private:
	std::string str;
//pow(2, index) array
	const int sec_pow[30] = {
		1, 2, 4, 8,	
		16, 32, 64,	128,
		256, 512, 1024, 2048,
		4096, 8192, 16384, 32768,
		65536, 131072, 262144, 524288,
		1048576, 2097152, 4194304, 8388608,
		16777216, 33554432, 67108864, 134217728,
		268435456, 536870912, 	1073741824};
	void setBinary(int num);

public:
	binary(std::string bin_str) : str(bin_str) {}
	binary(int num);
	
	binary operator^(const binary& other);
	friend binary operator^(const binary& other, int index);
	binary operator<<(int num);
	binary operator>>(int num);
};

void binary::setBinary(int num)
{
	int count = 29;
	
	for(int i = 29; num != 0; i--)
	{
		if(num - sec_pow[i] > 0)
		{
			num -= sec_pow[i];
			str.insert(29 - i, "1");
		}
		else	
			str.insert(29 - i, "0");
	}

	while(str.length() != 31)
		str.insert(0, "0");
}

binary::binary(int num)
{
	setBinary(num);
}

binary binary::operator^(const binary& other)
{
	binary result(0);
	for(int i = 0; i < 31; i++)
	{
		if((this->str[i] == "1" && other.str[i] == "1") || this->str[i] == "0" && other.str[i] == "0")
			result.str[i] = "0";
		else if((this->str[i] == "1" && other.str[i] == "0") || (this->str[i] == "0" && other.str[i] == "1"))
			result.str[i] = "1";
	}

	return result;
}

binary operator^(const binary& other, int index)
{
	binary result(this->str);
	if((this->str[index] == "1" && other.str[index] == "1") || (this->str[index] == "0" && other.str[index] == "0"))
		result.str[index] = "0";
	else if((this->str[index] == "1" && other.str[index] == "0") || (this->str[index] == "0" && other.str[index] == "1"))
		result.str[index] = "1";
	return result;
}

binary binary::operator<<(int num){
	binary result(this->str);
	if(result.str[0] != result.str[1])
	{
		if(result.str[0] == "0")
			result.str[1] = "0";
		else
			result.str[1] = "1";
	}
	
	result.str.erase(0, num);
	for(int i = 0; i < num; i++)
		result.str.append("0");

	return result;
}

binary binary::operator<<(int num){	
	binary result(this->str);
	std::string input = "1";
	if(result.str[0] != result.str[1])
	{
		if(result.str[0] == "0")
			input = "0";
	}
	
	result.str.erase(31, num);
	
	for(int i = 0; i < num; i++)
		result.str.insert(0, input);

	return result;
}
