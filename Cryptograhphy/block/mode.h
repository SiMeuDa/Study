#pragma once
#define BYTE 16
#include <string>
#include <thread>
using std::string;
using std::thread;

class mode{
private:
	inline string pedding(string text)
	{
		while(text.length() % BYTE)
			text.append("*");

		return text;
	}

	inline string unpedding(string text)
	{
		for(int i = text.length() - 1; (i >=0) && (text[i] == '*'); i--)
			text.pop_back();
		return text;
	}
public://ECB, CBC, CFB, OFB, CTR
	//Electric CodeBook
	string ECB(string msg, string key)
	{
		//do peddding
		msg = pedding(msg);
		int len = msg.length();
		int block_num = len / BYTE;
		string result;

		//make string block
		string* sblock = new string[block_num];
		if(sblock == nullptr)	//error handling
			return "";
		//limit block's size & copy str
		for(int i = 0; i < block_num; i++)
		{
			sblock[i].resize(BYTE);
			for(int j = 0; j < BYTE; j++)
				(sblock[i])[j] = msg[j + i * BYTE];
		}

		thread* tp = new thread[block_num];

		for(int i = 0; i < block_num; i++)
			result.append((tp[i])(crypto(sblock[i])));

		delete[] sblock, tp;

		return result;
	}
};
