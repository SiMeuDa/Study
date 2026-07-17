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
	bool isPrint = false;
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
		//check argument validation
		if((argc != 5) or
		(argv[1] != "-p"sv) or 
		(argv[2] != "1"sv and argv[2] != "0"sv))
			throw invalid_argument("[Usage]: ./[file_name] -p [1(print)/0(don't print)] [comparing msg] [original msg]");

		//set flags
		isPrint = atoi(argv[2]);

		//setting table
	 	set_table(argv[3], table);
		
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
		msg = org_msg(argv[4]);


    	for (int i = 0; i < num_threads; ++i) 
    	{	
        	//start lambda threading
		//msg: original message
		//table: set table on set_table
		//sekey[i] = start point
		//sekey[i + 1] = end point
		//klen = key len
        	t.push_back(async(launch::async, [&msg, &table, s_key = sekey[i], e_key = sekey[i + 1], klen, isPrint]() 
			{
				//result = saving rseult
				//chg_key = changing key
				//gram = tetramgram result
				string chg_key = s_key, gram;
				string_view  sv_msg;

				//comp = compare value -> change to max
				//m = now m value
				double compare = numeric_limits<double>::lowest(), score = 0;
				
				//saving & return result
				RESULT local_result;
				
				
				//object for using vigenere
				cipher c;
				//string len
				int len;

				//now == end -> break
				while(strncmp(chg_key.c_str(), e_key.c_str(), klen) < 0)
				{
					score = 0.0;

					//vigenere == string return
					sv_msg = c.vigenere(msg, chg_key, false);
					
					len = sv_msg.length();
					
					//calculate tetramgram score
					//high frequency -> big score
					//low frequency -> small score
					for(int j = 0; j < len - 3; j++)
					{
						//find value
						if(table.find(string(sv_msg.substr(j, 4)))!= table.end())
							score += table[string(sv_msg.substr(j, 4))];
						else
							score += table.at("!Match");

					}

					if(isPrint)
						clog << "Key: " << chg_key << ", Tetragram: " << score << "\n";

					//find biggest value
					if(compare < score)
					{
						//updata compare value
						compare = score;

						//save return value
						local_result.score = score;
						local_result.key = chg_key;
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

				return local_result;
			}));
		}
		
	RESULT final_result = {string(klen, 'Z'), numeric_limits<double>::lowest()};

	    //if it allow to join, join thread
	    for (auto& it : t)
	    {
		    RESULT thread_result = it.get();
			
		    if(thread_result.score > final_result.score)
		    {
			    final_result.key = thread_result.key;
			    final_result.score = thread_result.score;
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
