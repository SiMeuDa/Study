#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <future>
#include <cstring>
#include "cipher.h"
using namespace std;

void tetragram(const char*, vector<double>&);
void take_klen(int&);
string is_dir(string);
string org_msg(const char*);

int main(int argc, char* argv[])
{
	int klen, div = 26;
	string msg, dir;
	vector<double> tetra, result;
	vector<future<vector<double>>> t;

    //check hardware's thread count
    unsigned int hw_threads = std::thread::hardware_concurrency();

    int num_threads = (hw_threads >= 4) ? 4 : 2;

	div = div / num_threads;
	
	tetra.resize(4, 0.0);

	try{
		if(argc != 3)
			throw invalid_argument("Invalid Argument");
	
	 	tetragram(argv[1], tetra);
		
		for(auto& a : tetra)
			cout << a << endl;

		return 0;

		take_klen(klen);
		string key(klen, 'A');
		string end(klen, 'Z');

		end[0] = 'A';
		end[0] += div;

		//make dirctory for save result
		dir = is_dir(argv[2]);

		//take original message from file
		msg = org_msg(argv[2]);

    	for (int i = 0; i < num_threads; ++i) 
    	{	
        	//start threading
        	t.push_back(async(launch::async, [&msg, tetra, end, key, dir, klen]() 
			{
				string result, chg_key = key;
				char** value;
				double m = -1, comp = 0;
				vector<double> res;
				res.resize(klen + 1);
				for(int j = 0; j < klen + 1; j++)
					res[j] = 0;

				char table[4][5]= { 
					"THER",
					"HERE",
					"TION",
					"WITH"
				};
				cipher c;
				int len;

				len = msg.length();
		
				value = new char*[len / 4 + 1];
		
				for(int i = 0; i < len / 4 + 1; i++)
				{
					value[i] = new char[5];
					if(value[i] == nullptr)
					{
						for(int j = 0; j < i; j++)
							delete value[i];
		
						delete[] value;
					}
				}
				while(true)
				{
					if(chg_key[0] == '[' or chg_key[klen - 1] == '[')
						break;

					//vigenere == string return
					result = c.vigenere(msg, chg_key, false);

					//divie to tetra
					for(int j = 0; j < len; j += 4)
					{
						for(int k = j; k < 4; k++)
						{
							if(k <= len)
								(value[j])[k] = result[k];
							else
								(value[j])[k] = ' ';
						}
					}
					
					//tetragram logic
					for(int j = 0; j < len / 4 + 1; j += 4)
					{
						for(int k = 0; k < 4; k++)
							if(strstr(value[j], value[k]) != nullptr)
									comp += tetra[k];

						if(comp > m)
						{
							m = comp;
							
							res[0] = m;

							for(int k = 1; k <= klen; k++)
								res[k] = static_cast<double>(chg_key[k - 1]);
						}
					}

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

					//end condition
					if(chg_key == end)
						break;
				}

				for(int j = 0; j < len / 4 + 1; j++)
					delete[] value[j];

				delete[] value;

				return res;
			}));
			
			key[0] += div + 1;

			if(i != num_threads - 1)
				end[0] += div;
			else
				end[0] = 'Z';
			
		}
		vector<double> vecmax = {-1.0};

	    //if it allow to join, join thread
	    for (auto& it : t)
	    {
			vector<double> r = it.get();

			if(r[0] > vecmax[0])
				vecmax = r;
		}
		
		key = string(klen, 'A');

		clog << "[RESULT] Key: " << key << endl;


	}catch(const exception& e){
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}
    
	return 0;

}

void tetragram(const char* path, vector<double>& bias)
{
	char table[4][5] = {
		"THER",
		"HERE",
		"TION",
		"WITH"
		};
	
	fstream f;
	string str;
	size_t pos;
	f.open(path);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");

	while(getline(f, str))
	{
		while(pos != string::npos)
		{
			for(int i = 0; i < 4; i++)
			{
				pos = str.find(table[i]);
				if(pos != string::npos)
					bias[i]++;
			}
		}
	}

	for(int i = 0; i < 4; i++)
		bias[i] = log10(bias[i]);

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

string is_dir(string name)
{
	name.erase(name.end() - 4, name.end());
	name.append("_BruteForce");

	return name;
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
