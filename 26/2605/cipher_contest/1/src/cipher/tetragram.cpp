#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <future>
#include <cstring>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include "cipher.h"
using namespace std;

typedef struct{
	string key = "";
	double score = 0;
}RESULT;

void set_table(const char*, unordered_map<string, double>&);
void take_klen(int&);
string org_msg(const char*);

int main(int argc, char* argv[])
{
	//klen = key len
	int klen;

	//msg: original message
	string msg;
	
	//multi threading vector
	vector<future<RESULT>> t;
	
	//start, end key point(string)
	//[Example] thread = 2
	//sekey[0] == "AAA"
	//sekey[1] == "NAA"
	vector<string> sekey;

	//dynamic table
	unordered_map<string, double> table;


    	//check hardware's thread count
	unsigned int hw_threads = std::thread::hardware_concurrency();

	int num_threads = (hw_threads >= 4) ? 4 : 2;

	//set sekey size
	sekey.resize(num_threads + 1);
	
	try{
		//argument count
		if(argc != 3)
			throw invalid_argument("[Usage]: ./[file_name] [comparing msg] [original msg]");

		//setting table
	 	set_table(argv[1], table);
		
		//take key's len
		take_klen(klen);

		//resize start end point
		for(int i = 0; i < num_threads; i++)
		{
			sekey[i].resize(klen);

			sekey[i] = string(klen, 'A');

			(sekey[i])[0] += (26 / num_threads) * i;
		}

		//set end point
		sekey[num_threads] = string(klen, 'Z');
		


		//take original message from file
		msg = org_msg(argv[2]);


    	for (int i = 0; i < num_threads; ++i) 
    	{	
        	//start lambda threading
		//msg: original message
		//table: set table on set_table
		//sekey[i] = start point
		//sekey[i + 1] = end point
		//klen = key len
        	t.push_back(async(launch::async, [&msg, table, sekey[i], sekey[i + 1], klen]() 
			{
				//result = saving rseult
				//chg_key = changing key
				//gram = tetramgram result
				string chg_key = sekey[i], gram;
				string_view = sv_msg

				//comp = compare value -> change to max
				//m = now m value
				double compare = numeric_limits<double>::min();
				
				//saving & return result
				RESULT res;
				
				//object for using vigenere
				cipher c;
				//string len
				int len;

				//start == end -> break
				while(sekey[i] != sekey[i + 1])
				{
					//vigenere == string return
					sv_msg = c.vigenere(msg, chg_key, false);

					
					//calculate tetramgram score
					//high frequency -> big score
					//low frequency -> small score
					for(int j = 0; j < len - 3; j++)
					{
						//find value
						if(table.find(sv_msg.substr(j, 4)) != table.end())
							score += table[sv_msg.substr(j, 4)];
						else
							score += table["!Match"];

					}
				
					//find biggest value
					if(compare < score)
					{
						//updata compare value
						compare = score;

						//save return value
						res.score = score;
						res.key = chg_key;
					}

					//increase most left key value
					chg_key[klen - 1]++;
					
					//check key valid alphabet value
					for(int k = klen - 1; k > 0; k--)
					{		
						if(chg_key[k] >  'Z')
						{	
							chg_key[k] = 'A';
							++chg_key[k - 1];
						}
					}

				}

				return res;
			}));
		}
		
	bool isFirst = true;

	RESULT final_result = {string(klen, 'Z'), numeric_limits<double>::min()};

	    //if it allow to join, join thread
	    for (auto& it : t)
	    {
		    RESULT r = it.get();
			
		    if(r.score > final_result.score)
		    {
			    final_result.key = r.key;
			    final_result.score = final_result.score;
	
		    }
	
	    }

	    //print result
	    clog << "[RESULT] Key: " << final_result.key << ", Tetragram: " << final_result.score << endl;

	}catch(const exception& e){
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}
    
	return 0;

}

void set_table(const char* path, unordered_map<string, double>& table)
{
	//file open
	fstream f;
	string str;
	
	int len = 0, count = 0, min = 0;
	string left = "";
	string_view sv_msg;

	f.open(path);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");


	while(getline(f, str))
	{
		//insert left string
		str.insert(0, left);
		//erase space
		str.erase(remove(str.begin(), str.end(), ' '), str.end());

		//take length
		len = str.length();
		
		//copy to string_view
		//To Prevent additional string copy
		sv_msg = str;

		//take left string
		left = str.substr(str.length() - 4, 3);
	
		//total tetragram count
		count += len - 3;
		//table exist, add value
		for(int i = 0; i < len - 3; i++)
			table[sv_msg.substr(i, 4).data()] += 1;
	}

	f.close();

	//set score log
	for(auto it = table.begin(); it != table.end(); it++)
	{
		it->second = log10(it->second / count);
		//find min value
		if(it->second < min)
			min = it->second;
	}
	
	table["!Match"] = min - 1.0;

	return;
}
void take_klen(int& len)
{
	cout << "What is Key's Length: ";
	int l;
	cin.exceptions(ios_base::failbit | ios_base::badbit);
	try{
		cin >> l;
	
		len = l;
	
		if((len >= 1) && (len <= 5))
			return;
		else
			throw range_error("Out of Range");
	}
	catch(const ios_base::failure e){
		//cin exception
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw e.what();
	}
}

string org_msg(const char* path)
{
	fstream f;
	f.open(path, ios::in);
	
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");

	string msg;
	string result;
	
	while(getline(f, msg))
		result.append(msg);

	//erase space
	result.erase(remove(result.begin(), result.end(), ' '), result.end());

	return result;
}
