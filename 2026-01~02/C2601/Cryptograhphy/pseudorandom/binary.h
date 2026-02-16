#pragma once
#include <string>

class binary {
private:
    std::string str;
	const int len = 32;

    const int sec_pow[31] = {
        1, 2, 4, 8,
        16, 32, 64, 128,
        256, 512, 1024, 2048,
        4096, 8192, 16384, 32768,
        65536, 131072, 262144, 524288,
        1048576, 2097152, 4194304, 8388608,
        16777216, 33554432, 67108864, 134217728,
        268435456, 536870912, 1073741824
    };
    void setBinary(int num);
	
public:
	binary() {}
    binary(std::string bin_str) : str(bin_str) {}
    binary(int num);
	std::string getBinary(){ return str; }
	friend int getDecimal(const binary& other);
    binary operator^(const binary& other);
    binary operator^(int index); 
    
    binary operator<<(int num);
    binary operator>>(int num);
};

void binary::setBinary(int num)
{
    str = "";
	if(num >= 0)
	{
	    for (int i = len - 1; i >= 0; i--)
	    {
	        if (num >= sec_pow[i]) 
	        {
	            num -= sec_pow[i];
	            str.append("1");
	        }
	        else
	        {
	            str.append("0");
	        }
		}
	}
	else
	{
		num = -num;
		for(int i = len - 1; i >= 0; i--)
		{
			if(num >= sec_pow[i])
			{
				num -= sec_pow[i];
				str.append("0");
			}
			else
				str.append("1");
		}
    }
}

binary::binary(int num)
{
    setBinary(num);
}

int getDecimal(const binary& other)
{
	int result = 0;

	for(int i = 0; i < other.len; i++)
		if(other.str[i] == '1')
			result += other.sec_pow[other.len - i];
	return result;
}

binary binary::operator^(const binary& other)
{
    binary result(0); 

    for (int i = 0; i < len; i++)
    {
        char c1 = this->str[i];
        char c2 = other.str[i];

        if (c1 == c2) 
            result.str[i] = '0';
        else          
            result.str[i] = '1';
    }
    return result;
}

binary binary::operator^(int index)
{
    binary result(this->str);
    if (index >= 0 && index < len) {
        if (result.str[index] == '0')
            result.str[index] = '1';
        else
            result.str[index] = '0';
    }
    return result;
}

binary binary::operator<<(int num) {
    binary result(this->str);
    
    if (num >= len) {
        result.str = std::string(len, '0');
        return result;
    }

    result.str.erase(0, num); 
    result.str.append(num, '0'); 

    return result;
}

binary binary::operator>>(int num) {
    binary result(this->str);
    
    char signBit = result.str[0]; 
    
    if (num >= len) {
        result.str = std::string(31, signBit);
        return result;
    }

 
    result.str.erase(len - num, num); 
    
    result.str.insert(0, num, signBit);

    return result;
}
