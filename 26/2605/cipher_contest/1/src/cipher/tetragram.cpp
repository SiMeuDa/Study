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
				string result, chg_key = key, gram;
				double m = 0, comp = 0;
				vector<double> res;
				res.resize(klen + 1);

				for(int j = 0; j < klen + 1; j++)
					res[j] = 0;

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
					//break condition
					if(chg_key[0] > 'Z' or chg_key[klen - 1] > 'Z')
						break;

					comp = 0;

					//vigenere == string return
					result = c.vigenere(msg, chg_key, false);

					//divie origin msg to tetra
					for(int j = 0; j < len - 3; j++)
					{
						gram = result.substr(j, 4);
						for(int k = 0; k < 4; k++){
							if(strncmp(table[k], gram.c_str(), 4) == 0)
								comp += tetra[k];
						}
					}


					if(comp < m)
					{
						m = comp;
						res[0] = comp;

						for(int k = 1; k <= klen; k++)
							res[k] = static_cast<double>(chg_key[k - 1]);
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

			if(i != num_threads - 1)
				end[0] += div;
			else
				end[0] = 'Z';
			
		}
		bool isFirst = true;
		vector<double> vecmax = {0.0};
	    //if it allow to join, join thread
	    for (auto& it : t)
	    {
			vector<double> r = it.get();
			if(!isFirst){
				if(r[0] < vecmax[0])
					vecmax = r;
			}
			else{
				vecmax = r;
				isFirst = false;
			}
		}
		
		key = string(klen, 'A');

		for(int i = 0; i < klen; i++){
			key[i] = vecmax[i + 1];
		}

		clog << "[RESULT] Key: " << key << ", Tetragram: " << vecmax[0] << endl;


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
	size_t pos = 0;
	int len = 0;
	f.open(path);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");


	while(getline(f, str))
	{
		for(int i = 0; i < 4; i++)
		{
			pos = 0;
			while(pos != string::npos)
			{
				pos = str.find(table[i], pos + 1);
				if(pos != string::npos)
					bias[i]++;
			}
		}
		len += str.length();
	}

	f.close();


	for(int i = 0; i < 4; i++){

		if(bias[i] != 0)
			bias[i] = log10(bias[i] / len);
		else
			bias[i] = log(0.1 / len);
	}

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
