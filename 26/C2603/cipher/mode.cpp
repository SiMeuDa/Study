#include "mode.h"

std::string mode::padding(std::string msg)
{	
	//copy msg
	std::string result = msg;
	//take padding number(PKCS#7 Standard)
	int padding_num = block_len - (result.length() % block_len);
	//do padding(PKCS#7 Standard)
	for(int i = 0; i < padding_num; i++)
		result.push_back(static_cast<char>(padding_num));

	return result;
}

std::vector<uint64_t> mode::unpadding(std::vector<uint64_t> msg)
{	
	//take padding value == repeat count
	uint8_t value = (msg[msg.size() - 1]) & 0xFF;

	msg[msg.size() - 1] = (msg[msg.size() - 1] >> (8 * value)) << (8 * value);

	return msg;
}

std::vector<uint64_t> mode::to_integer(std::string msg)
{
	//first do padding
	msg = padding(msg);
	
	//save char to integer result
	std::vector<uint64_t> result;
	//for using repeatence
	int block_count = msg.length() / block_len;
	//resize & initalize vector
	result.resize(block_count, 0);
	//save string each block
	//casting to uint64_t(unless msg casted to 32bit)
	//shift 8 * (8 - j - 1)
	for(int i = 0; i < block_count; i++)
		for(int j = 0; j < block_len; j++)
			result.at(i) |= (static_cast<uint64_t>(static_cast<unsigned char>(msg[block_len * i + j])) << ((sizeof(uint64_t) / sizeof(char)) * (block_len - j - 1)));

	return result;
}

std::string mode::from_integer(std::vector<uint64_t> vec)
{
	std::string result;
	
	size_t size = vec.size();

	//first do unpadding
	vec = unpadding(vec);

	result.reserve(block_len * size);

	for(size_t i = 0; i < size; i++)
	{
		for(size_t j = 0; j < block_len; j++)
		{
			uint8_t temp = (vec[i] >> (block_len * (block_len - j - 1)) ) & 0xFF;
			if(temp != 0)
				result.push_back(static_cast<char>(temp));
		}
	}

	return result;
}

std::string mode::run(std::string test)
{
	std::vector<uint64_t> temp = to_integer(test);

	return (from_integer(temp));
}



std::vector<uint64_t> mode::ECB(std::string msg, uint64_t key)
{
	std::vector<uint64_t> imsg;
	//change string to integer vector & padding
	imsg = to_integer(msg);

    size_t total_blocks = imsg.size();
	//exception handling
    if (total_blocks == 0) 
		return imsg;

    std::vector<uint64_t> result(total_blocks);

	//check hardware's thread count
    unsigned int hw_threads = std::thread::hardware_concurrency();
	    
    int num_threads = (hw_threads >= 4) ? 4 : 2;
	
	//if block is smaller than thread, overhead exist
    if (total_blocks < static_cast<size_t>(num_threads))
        num_threads = static_cast<int>(total_blocks);
	//vector for thread
    std::vector<std::thread> t;
    size_t chunk_size = total_blocks / num_threads;
    size_t remainder = total_blocks % num_threads; 

    size_t current_start = 0;

    for (int i = 0; i < num_threads; ++i) 
    {
        size_t current_chunk = chunk_size + (i < remainder ? 1 : 0);
        size_t start = current_start;
        size_t end = start + current_chunk;
	//start threading
        t.emplace_back([this, &imsg, &result, start, end, key]() {
			       for (size_t j = start; j < end; ++j)
                	result[j] = this->cipher(imsg[j], key);
        });

		//save end index
        current_start = end; 
    }
	//if it allow to join, join thread
    for (auto& it : t)
        if (it.joinable()) 
			it.join();

    return result;
}

std::string mode::ECB(std::vector<uint64_t> msg, uint64_t key)
{
	std::vector<uint64_t> result;
    size_t total_blocks = msg.size();
	//exception handling
    if (total_blocks == 0) 
		return " ";

	result.resize(total_blocks, 0);

	//check hardware's thread count
    unsigned int hw_threads = std::thread::hardware_concurrency();
	    
    int num_threads = (hw_threads >= 4) ? 4 : 2;
	
	//if block is smaller than thread, overhead exist
    if (total_blocks < static_cast<size_t>(num_threads))
        num_threads = static_cast<int>(total_blocks);
	//vector for thread
    std::vector<std::thread> t;
    size_t chunk_size = total_blocks / num_threads;
    size_t remainder = total_blocks % num_threads; 

    size_t current_start = 0;
    
	for (int i = 0; i < num_threads; ++i) 
    {
        size_t current_chunk = chunk_size + (i < remainder ? 1 : 0);
        size_t start = current_start;
        size_t end = start + current_chunk;
	//start threading
        t.emplace_back([this, &msg, &result, start, end, key]() {
			       for (size_t j = start; j < end; ++j)
                	result[j] = this->decipher(msg[j], key);
        });

		//save end index
        current_start = end; 
    }
	//if it allow to join, join thread
    for (auto& it : t)
        if (it.joinable()) 
			it.join();

	std::string res = from_integer(result);

    return res;
}
