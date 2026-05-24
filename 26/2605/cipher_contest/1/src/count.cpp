#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	fstream f;
	int count = 0;

	f.open(argv[1]);
	if(!f.is_open())
		return -1;

	string str;

	while(getline(f, str))
		count += str.length();

	f.close();
	cout << "Count: " << count << endl;
	return 0;
}
