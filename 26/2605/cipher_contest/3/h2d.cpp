#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
using namespace std;

string take_string(const char*);
string to_ascii(const string_view);
void print_hex(const string_view);

int main(int argc, char* argv[])
{
	if(argc != 2)
		return -1;

	//take string
	string msg = take_string(argv[1]);

	//translate to ascii hexa
	msg = to_ascii(msg);

	//print hexa result
	print_hex(msg);

	return 0;
}

string take_string(const char* path)
{
	fstream f;
	string str, result;
	//file check
	f.open(path, ios::in);
	if(!f.is_open())
		throw ios_base::failure("Failed to open File");

	//take file with space
	while(getline(f, str))
		result.append(str).append(" ");

	return result;
}

string to_ascii(const string_view org)
{
	char hex[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7', 
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
		};
	int len = org.length();
	string result;
	result.resize(len * 2);

	for(int i = 0; i < len; i++)
	{
		//translate to int digit
		int value = static_cast<int>(org[i]);

		//save to hexa
		result[2 * i] = hex[value / 16];
		result[2 * i + 1] = hex[value % 16];
	}

	return result;
}

void print_hex(const string_view msg)
{
	int len = msg.length();

	for(int i = 1; i <= len; i++)
	{
	//**** **** ****
		clog << msg[i - 1];

		if(i % 4 == 0)
			clog << " ";
	}
	//buffer flush and \n
	clog << endl;

	return;
}
