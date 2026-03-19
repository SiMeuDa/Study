#include "cipher.h"
#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <cctype>
using namespace std;

bool isValidPath(const std::string& path);
const char* filecrypto(int, char**);

int main(int argc, char* argv[])
{
	string errMsg;
	try{
		if((argc == 7) && (argv[3] == "-f"))
		{
	//./[file_name] -en [1/0]  -f [file_path] -k [key]
			if((argv[5] != "-k") || (argv[1] != "-en"))
				throw("Invalid Parameter");

			errMsg = filecrypto(argc, argv); 
				if(errMsg != "true")
					throw(errMsg);
		}
	}catch(const char* msg)
	{
		cerr << "[Error]: " << msg << endl;
		return -1;
	}

}

bool isValidPath(const std::string& path)
{//check whether file path is valid
    return access(path.c_str(), F_OK) == 0;
}

const char* filecrypto(int argc, char** argv)
{
	try{
		//path check
		if(!isValidPath(argv[4]))
			throw("Invalid File Path");

		fstream fin(argv[4], ios::in);
		if(fin.fail())
			throw("Failed to open File");

		cipher c;
		std::string fileStr;
		std::string buffer;
		std::vector<uint64_t> vecRes;

		while(!fin.eof())
		{
			fin >> buffer;
			fileStr.append(buffer);
		}
		fin.close();
		//take key
		buffer = argv[6];
		
		//make key uint64_t
		uint64_t key = 0;
		int len = 0;
	
		for(int i = 0; i < len; i++)
		{
			//check overflow
			if(key > key * 10)
				throw("Key value is Too Big");
			key *= 10;
			//check overflow
			if(key > key + buffer[i] - '0')
				throw("Key value is Too Big");
			key += (buffer[i] - '0');
		}

		fstream fout(argv[4], ios::out);
		if(fout.fail())
			throw("Failed to open File");

		if(argv[3] == "1")
		{
			vecRes = c.encryption(fileStr, key);	
			for(auto it = vecRes.begin(); it != vecRes.end(); it++)
				fout << *it;
			fout.close();
		}
		else if(argv[3] == "0")
		{
			len = fileStr.length();
			uint64_t take;

			for(int i = 0; i < len; i++)
			{
				if(!isdigit(fileStr[i]))
					throw("Invalid File Input");

				if((i % 63 == 0) && (i != 0))
				{
					vecRes.push_back(take);
					take = 0;
				}
				if(take > take * 10)
					throw("Invalid File Input");
				take *= 10;
				//change char to integer
				if(take > take + fileStr[i] - '0')
					throw("Invalid File Input");
				take += (fileStr[i] - '0');
			}

			fileStr = c.decryption(vecRes, key);

			fout << fileStr;

			fout.close();
		}
		else//argv[3] == bool type
			throw("Invalid Input");
	}catch(const char* msg)
	{
		return msg;
	}
	//Normal Return Msg
	return "true";
}
