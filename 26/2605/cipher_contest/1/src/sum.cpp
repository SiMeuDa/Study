#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 4)
		return -1;

	fstream r[3];
	string r1, r2, r3;

	for(int i = 0; i < 3; i++){
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
	
	for(int i = 0; i < 3; i++)
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
	}

	r[0].close();

	return 0;
}
