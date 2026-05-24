#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <thread>
#include "cipher.h"
using namespace std;

void take_klen(int&);
string is_dir(string);
string org_msg(const char*);

int main(int argc, char* argv[])
{
	int len, div = 26;
	string msg, dir;
	vector<thread> t;

    //check hardware's thread count
    unsigned int hw_threads = std::thread::hardware_concurrency();

    int num_threads = (hw_threads >= 4) ? 4 : 2;

	div = div / num_threads;

	try{
		if(argc != 2)
			throw invalid_argument("Invalid Argument");
		
		take_klen(len);
		string key(len, 'A');
		string end(len, 'Z');
		end[0] = 'A';
		end[0] += div;

		//make dirctory for save result
		dir = is_dir(argv[1]);

		//take original message from file
		msg = org_msg(argv[1]);


    	for (int i = 0; i < num_threads; ++i) 
    	{	
        	//start threading
        	t.emplace_back([&msg, end, key, dir, len]() 
			{
				string name, chg_key = key;
				fstream fout;
				cipher c;
				while(key != end)
				{
					//file name set
					name = dir;

					//check key
					for(int k = len - 1; k > 0; k--)
					{		
						if(chg_key[k] >  'Z')
						{	
							chg_key[k] = 'A';
							++chg_key[k - 1];
						}
					}

					name.append("/Decrypt_BruteForce_KEY_" + key + ".txt");
					
					fout.open(name, ios::out);
					if(!fout.is_open())
						throw ios_base::failure("Failed to open File");
					fout << c.vigenere(msg, chg_key, false);
				
					fout.close();		

					chg_key[len - 1]++;
				}

				name = dir;
				name.append("/Decrypt_BruteForce_KEY_" + end + ".txt");

				fout.open(name, ios::out);
				if(!fout.is_open())
					throw ios_base::failure("Failed to open File");

				fout << c.vigenere(msg, end, false);

				fout.close();
			});
			
			key[0] += div + 1;

			if(i != num_threads)
				end[0] += div;
			else
				end[0] = 'Z';
			
		}

	    //if it allow to join, join thread
	    for (auto& it : t)
	        if (it.joinable()) 
				it.join();

	}catch(const exception& e){
		cerr << "[Error]: " << e.what() << endl;
		return -1;
	}
    
	
	clog << "SUCCESS TO DO BRUTE FORCE ATTACK" << endl;

	return 0;

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

	filesystem::create_directories(name);

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
