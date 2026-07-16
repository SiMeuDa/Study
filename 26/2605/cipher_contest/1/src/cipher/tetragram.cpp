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
#include <map>
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
	//div = 
	//#include <limits>divide number
	int klen, div = 26;
	//msg: original message
	//dir: file directory
	string msg, dir;
	vector<double> tetra, result;
	//multi threading vector
	vector<future<vector<double>>> t;
	//start, end key point(string)
	//[Example] thread = 2
	//sekey[0] == "AAA"
	//sekey[1] == "NAA"
	vector<string> sekey;
	unordered_map<string, double> table;


    	//check hardware's thread count
	unsigned int hw_threads = std::thread::hardware_concurrency();

	int num_threads = (hw_threads >= 4) ? 4 : 2;

	//set sekey size
	sekey.resize(num_threads + 1);
	
	div = div / num_threads;
	
	tetra.resize(4, 0.0);

	try{
		if(argc != 3)
			throw invalid_argument("[Usage]: ./[file_name] [comparing msg] [original msg]");
	
	 	set_table(argv[1], table);
		
		//take key's len
		take_klen(klen);

		//resize start end point
		for(int i = 0; i < num_theads; i++)
		{
			sekey[i].resize(klen);

			sekey[i] = string(klen, 'A');

			(sekey[i])[0] += (26 / num_theads) * i;
		}

		//set end point "ZZZZZ"
		sekey[num_threads] = string(klen, 'Z');
		


		//take original message from file
		msg = org_msg(argv[2]);


    	for (int i = 0; i < num_threads; ++i) 
    	{	
        	//start lambda threading
		//msg: original message
		//tetra: tetragram bias
		//sekey[i] = start point
		//sekey[i + 1] = end point
		//key = using key
		//dir = directory
		//klen = key len
        	t.push_back(async(launch::async, [&msg, tetra, sekey[i], sekey[i + 1], dir, klen]() 
			{
				//result = saving rseult
				//chg_key = changing key
				//gram = tetramgram result
				string result, chg_key = sekey[i], gram;
				//comp = compare value -> change to max
				//m = now m value
				double m = 0, comp = 0;
				//flags
				bool isFirst = true;
				bool isMatch = false;
				//saving & return result
				RESULT res;

				//Simplified Table
				char table[4][5]= { 
					"THER",
					"HERE",
					"TION",
					"WITH"
				};
				cipher c;
				int len;

				len = msg.length();
		

				while(true)
				{
					comp = 0;
					
					//vigenere == string return
					result = c.vigenere(msg, chg_key, false);

					//divie origin msg to tetra
					for(int j = 0; j < len - 3; j++)
					{
						isMatch = false;
						for(int k = 0; k < 4; k++){
							if(strncmp(result.data() + j, table[k], 4) == 0){
								isMatch = true;
								comp += tetra[k];
								break;
							}
						}
						if(!isMatch)
							comp += -1;
					}
					

					if(isFirst){
						m = comp;
						isFirst = false;
					}


					if(comp > m)
					{
						m = comp;

						res.score = m;
						res.key = chg_key;
					}
						
					clog << "Key: " << chg_key << ", tetra: " << comp << ", m: " << m <<  endl;
							

					//increase most left key value
					chg_key[klen - 1]++;
					
					//check key
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
			
			key[0] += div + 1;

			
		}
		
	bool isFirst = true;

	RESULT final_result = {numeric_limits<double>::min(), "ZZZZZ"};

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
	    clog << "[RESULT] Key: " << key << ", Tetragram: " << vecmax[0] << endl;


	}catch(const exception& e){
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}
    
	return 0;

}

void set_table(const char* path, unordered_map<string, double>& table)
{
	fstream f;
	string str;
	size_t pos = 0;
	int len = 0, left_point = 0, count = 0;
	string left = "";
	string_view sv_msg;
	f.open(path);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");


	while(getline(f, str))
	{
		str.insert(0, left);
		//erase space
		for(auto it = str.begin(); it != str.end(); it++)
			if(*it == ' ')
				str.erase(it);

		len = str.length();
		count += len / 4;
		//if string's length is not 4's multiple
		if(len % 4)
		{
			left_point = len - (len % 4);
			//save left string
			for(int i = left_point; i < len; i++)
				left[i - left_point] = str[i];
			//erase duplicated string
			str.erase(left_point);
			
			//len = str.length();
		}

		sv_msg = str;

		for(int i = 0; i < len; i += 4)
			table[sv_msg.substr(i, 4)] += 1;
	}

	f.close();

	for(auto it = table.begin(); it != table.end(); it++)
		*it->second = log10(*it->second / count);


	return;
}
void take_klen(int& len)
{
	cout << "What is Key's Length: ";
	int l;
	cin >> l;
	
	len = l;
	
	if((len >= 1) && (len <= 5))
		return;
	else
		throw range_error("Out of Range");
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

	return result;
}
