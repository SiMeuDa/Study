#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cerr << "Invalid Argument" << endl;
		return -1;
	}

	fstream f;
	string take, str;
	int len, div_num;


	f.open(argv[1], ios::in);
	if(!f.is_open()){
		cerr << "Failed to open File" << endl;
		return -1;
	}

	while(getline(f, take))
		str.append(take);

	f.close();

	len = str.length();

	cout << "Divide for which value: ";
	cin >> div_num;

	for(int j = 0; j < div_num; j++)
	{
		take = "result_";
		take.append(1, static_cast<char>(j + '0'));
		take.append(".txt");

		f.open(take, ios::out);
		if(!f.is_open()){
			cerr << "Failed to open file" << endl;
			return -1;
		}

		for(int i = j; i < len; i += div_num){
			if(str[i] > 'Z' or str[i] < 'A')
				continue;
			if(i >= len)
				break;
			f << str[i];
		}

		f.close();
	}

	return 0;
}
