#pragma once
#include <vector>
#include <string>
#include <cstdint>

template <typename T>
class binary{
public:
	std::vector<char> bin;

	binary(T value, size_t len = 0)
	{
		size_t repeat;
		if(len == 0)
			repeat = sizeof(T) * 8;
		else
			repeat = len;

		for(size_t i = 0; i < repeat; i++)
		{
			if(value & 1)
				bin.insert(bin.begin(), '1');
			else
				bin.insert(bin.begin(), '0');

			value = value >> 1;
		}
	}
	binary(const binary& other){ this->bin = other.bin;	}
	
	~binary(){	bin.clear();	}
	
	T to_integer(void)
	{
		T result = 0;
		for(int i = bin.size() - 1; i >= 0; i--)
			if(bin[i] == '1')
				result += (((T)1) << (bin.size() - 1 - i));
		return result;
	}

//circular right shift
	binary operator >>(int count)
	{
		binary result = *this;
		char temp;
		for(int i = 0; i < count; i++)
		{
			temp = result.bin.back();
			for(auto it = result.bin.end() - 1; it >= result.bin.begin() + 1; it--)
				*it = *(it - 1);
			result.bin[0] = temp;
		}

		return result;
	}
	
	int resize(size_t size)
	{
		bin.resize(size);
		return size;
	}
};
