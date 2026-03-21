/*
   		FILE EN/DECRYPTION PROGRAM
		USED CIPHER LOGIC: DES
		LATER, THIS PROGRAM'S CIPHER LOGIC WILL CHANGE FOR 3DES
 */
#include "src/cipher.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <cctype>
using namespace std;

inline bool isValidPath(const std::string& path);
inline bool isStrDigit(const char*, int);

int main(int argc, char* argv[])
{
	//take error messge
	string errMsg;
	cipher c;
	try{
		//isEncryption: 1, filePath: 1, key: 1
		if(((argc == 7) || (argc == 8)) && (argv[3] == "-f"sv) && (argv[5] == "-k"sv) && (argv[1] == "-en"sv))
		{//Standard DES section
		//foam: ./[file_name] -en [1/0] -f [file_path] -k [key]
			if(!isValidPath(argv[4]))
				throw std::invalid_argument("[Invalid Input]: Wrong File Path");

			fstream file;
			uint64_t key, key2;
			char buffer[128];
			string str;


			//UINT64_MAX = 18,446,744,073,709,551,615 = 0xFFFFFFFFFFFFFFFF<F12
			try{
				if((argc == 9) && (argv[6] != argv[7]))
					key2 = stoull(argv[7]);
				else
					key2 = 0;

				key = stoull(argv[6]);
			}catch(const out_of_range& e)
			{
				throw std::overflow_error("[Runtime Error]: Key Value is too Big");
			}
			catch(const invalid_argument& e)
			{
				throw invalid_argument("[Invalid Input]: Key Value must be ULL Type");
			}

			if(argv[2] == "1"sv)
			{//Encryption
				//open file for binary -> reduce program running time
				file.open(argv[4], ios::in | ios::binary);
			
				if(file.fail())
					throw std::invalid_argument("[Invalid Input]: Failed to Open File");

				//take file msg
				while(file.read(buffer, sizeof(buffer)))
					str.append(buffer, file.gcount());	//take real read count, append that

				if(file.gcount() > 0)
					str.append(buffer, file.gcount());	//append rest string

				file.close();

				//encrypt logic
				std::vector<uint64_t> vecResult = c.encryption(str, key, key2);
				if(vecResult.empty())
					throw std::length_error("[Length Error]: Failed to Encrypt File");
				
				//write to file
				file.open(argv[4], ios::out | ios::trunc | ios::binary);
				if(file.fail())
					throw invalid_argument("[Invalid Input]: Failed to Open File");
				//write whole vector
				file.write(reinterpret_cast<const char*>(vecResult.data()), vecResult.size() * sizeof(uint64_t));
				file.close();

				clog << "[SYSTEM]: SUCCESS TO ENCRYPT FILE" << endl;
			}
			else if(argv[2] == "0"sv)
			{//Decryption
				//open for Input, for binary, At end
				file.open(argv[4], ios::in | ios::binary | ios::ate);
				if(file.fail())
					throw std::invalid_argument("[Invalid Input]: Failed to Open File");
				//check file size
				streamsize size = file.tellg();
				//return to begin
				file.seekg(0, ios::beg);
				//for resize vector
				size_t count = size / sizeof(uint64_t);

				std::vector<uint64_t> vecInput(count);

				if(count <= 0)
					throw length_error("[Length Error]: Failed to Read File");

				file.read(reinterpret_cast<char*>(vecInput.data()), size);

				file.close();
				//decrypt logic
				str = c.decryption(vecInput, key, key2);
				
				file.open(argv[4], ios::out | ios::binary | ios::trunc);
				if(file.fail())
					throw invalid_argument("[Invalid Input]: Failed to Open File");

				//write string
				file.write(str.data(), str.length());

				file.close();

				clog << "[SYSTEM]: SUCCESS TO DECRYPT FILE" << endl;
			}
			else	//Invalid Data Type
				throw std::invalid_argument("[Invalid Input]: -en argument must be 1 or 0");
		}
		else	//Invalid parameter input
			throw invalid_argument("Invalid Input\n[Usage]: ./[file_name] -en [1/0] -f [file_path] -k [key] ([key2])");
	}catch(const std::exception& e)
	{
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}

	return 0;
}

inline bool isValidPath(const std::string& path)
{//check whether file path is valid
    return access(path.c_str(), F_OK) == 0;
}

inline bool isStrDigit(const char* msg, int len)
{//check string is compromised for number
	for(int i = 0; (i < len) | (msg[i] != '\0'); i++)
		if(!isdigit(msg[i]))
			return false;
	return true;
}
