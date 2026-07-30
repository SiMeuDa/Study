#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 6)
		return -1;

	fstream r[5];
	string r1, r2, r3, r4, r5;

	for(int i = 0; i < 5; i++){
		r[i].open(argv[i + 1], ios::in);
		if(!r[i].is_open())
		{
			cerr << "Failed to open File" << endl;
			return -1;
		}
	}

	getline(r[0], r1);
	getline(r[1], r2);
	getline(r[2], r3);
	getline(r[3], r4);
	getline(r[4], r5);
	
	for(int i = 0; i < 5; i++)
		r[i].close();

	r[0].open("result.txt", ios::out);

	for(int i = 0;;i++)
	{
		if(i >= r1.length())
			break;
		r[0] << r1[i];
		if(i >= r2.length())
			continue;
		r[0] << r2[i];
		if(i >= r3.length())
			continue;
		r[0] << r3[i];
		if(i >= r4.length())
			continue;
		r[0] << r4[i];
		if(i >= r5.length())
			continue;
		r[0] << r5[i];
	}

	r[0].close();

	return 0;
}
