#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <numeric>
using namespace std;



int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cerr << "[Error]: Invalid Argument" << endl;
		return -1;
	}

	fstream f;
	size_t index[50], start = 0;
	for(int i = 0; i < 50; i++)
		index[i] = 0;
	
	string strORG;

	f.open(argv[1]);

	if(f.is_open() != true){
		cerr << "[Error]: Failed to Open File" << endl;
		return -1;
	}

	int i = 0;

	while(getline(f, strORG))
	{
		while(strORG.find("DSZ", start) != string::npos)
		{
			if(i == 50)
				break;
			index[i] = strORG.find("DSZ", start);

			start = index[i++] + 1;
		}
	}

	f.close();

	for(int i = 0; i < 50; i++)
	{
		if(index[i] == 0)
			continue;

		for(int j = 0; j < 50; j++)
		{
			if((index[j] == 0) || i == j)
				continue;

			cout << "GCD(" << index[i] << ", " << index[j] << "): ";
		        cout << gcd(index[i], index[j]) << endl;
		}
	}

	return 0;
}
