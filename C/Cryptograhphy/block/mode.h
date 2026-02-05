#pragma once
#define BYTE 16
#include <string>
#include <random>
#include <chrono>
using std::string;

class mode{
private:
	inline string pedding(string text)
	{//pedding string with *
		while(text.length() % BYTE)
			text.append("*");

		return text;
	}

	inline string unpedding(string text)
	{//erase * from sentence
		for(int i = text.length() - 1; (i >=0) && (text[i] == '*'); i--)
			text.pop_back();
		return text;
	}

	inline string Random(string value, int len, int max, int min)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 engine(seed);

		std::uniform_int_distribution<char> dist(min, max);

		for(int i = 0; i < len; i++)
			value[i] = dist(engine);

		return value;
	}

public://ECB, CBC, CFB, OFB, CTR
	//Electric CodeBook
	string ECB(string msg, string key, bool isEncipher = true)
	{
		if(isEncipher)//do peddding
			msg = pedding(msg);
		else
			msg = unpedding(msg);

		int block_num = msg.length() / BYTE;
		string result = "";

		//make string block
		string* sblock = new string[block_num];
		if(sblock == nullptr)	//error handling
			return "error occur";

		//limit block's size & copy str
		for(int i = 0; i < block_num; i++)
		{
		//Limit string's size
			sblock[i].resize(BYTE);
			for(int j = 0; j < BYTE; j++)	//duplicate msg to string arr
				(sblock[i])[j] = msg[j + i * BYTE];
			if(isEncipher)
				sblock[i] = crypto(sblock[i], key);	//do encihper
			else
				sblock[i] = decrypto(sblock[i], key);
		}

		for(int i = 0; i < block_num; i++)
			result.append(sblock[i]);

		delete[] sblock;

		return result;
	}

	string CBC(string msg, string key, string IV = "", bool isEncipher = true)
	{
		if(isEncipher)//do peddding
			msg = pedding(msg);
		else
			msg = unpedding(msg);
		int block_num = msg.length() / BYTE;
		string result = "";

		if((IV == "") && isEncipher)	//make random IV
			IV = Random(IV, BYTE, 255, 0);
		else if(!isEncipher && (IV == ""))
			return "need IV";
		
		IV.resize(BYTE);

		//make string block
		string* sblock = new string[block_num];
		if(sblock == nullptr)	//error handling
			return "error occur";
	
		for(int i = 0; i < block_num; i++){
			for(int j = 0; j < BYTE; j++)	//divide msg to blocks
				(sblock[i])[j] = msg[j + i * BYTE];
			sblock[i].resize(BYTE);
		}
	
		if(isEncipher)
		{	//encihper logic
			for(int i = 0; i < block_num; i++)
			{
				for(int j = 0; j < BYTE; j++)
					(sblock[i])[j] = (sblock[i])[j] ^ IV[j];

				IV = sblock[i];
			}	

			for(int i = 0; i < block_num; i++)
				result.append(sblock[i]);
		}
		else	//decihper logic
		{
			string temp;

			for(int i = 0; i< block_num; i++)
			{
				temp = decrypto(sblock[i], key);

				if(i)
					for(int j = 0; j < BYTE; j++)
						temp[j] = (sblock[i - 1])[j] ^ temp[j];
				else
					for(int j = 0; j < BYTE; j++)
						temp[j] = temp[j] ^ IV[j];

				result.append(temp);
			}
		}

		delete[] sblock;

		return result;
	}

	string CFB(string msg, string key, string IV = "", bool isEncipher = true)
	{
		int block_num = msg.length() / BYTE;
		string result = "";

		if((IV == "") && isEncipher)	//make random IV
			IV = Random(IV, BYTE, 255, 0);
		else if(!isEncipher && (IV == ""))
			return "need IV";
		
		IV.resize(BYTE);

		//make string block
		string* sblock = new string[block_num];
		if(sblock == nullptr)	//error handling
			return "error occur";
	
		for(int i = 0; i < block_num; i++){
			for(int j = 0; j < BYTE; j++)	//divide msg to blocks
				(sblock[i])[j] = msg[j + i * BYTE];
			sblock[i].resize(BYTE);
		}



		delete[] sblock;

		return result;
	}
};
