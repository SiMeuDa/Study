/*
 * Change string to hexa
 */
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <cstdint>

using namespace std;
 
string take_string(const char*);
string to_ascii(const string_view);
void print_hex(const string_view);
inline void zinsert(string&, size_t, size_t);
inline void fprint_hex(const string_view, const char*, bool = false);

int main(int argc, char* argv[])
{
	string msg;

	for(uint64_t i = 0; i < 9999999999; i++)
	{
		msg = "action=set_salary&uid=";
		msg.append(to_string(i % 1000000));

		zinsert(msg, 26, 22);
		msg.append("&amt=0100&month=").append(to_string(i -  (i %  1000000)));

		zinsert(msg, 48, 42);

		msg = to_ascii(msg);

		if(i)
			fprint_hex(msg,"result.txt");
		else
			fprint_hex(msg, "result.txt", true);
	}
		
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
		if(org[i] == ' ')
			break;
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

	}
	//buffer flush and \n
	clog << endl;

	return;
}

inline void zinsert(string& msg, size_t limit, size_t index)
{
	while(msg.length() != limit)
		msg.insert(index, "0");
	return;
}

inline void fprint_hex(const string_view msg, const char* name, bool isFirst)
{
	fstream f;

	if(isFirst)
	{
		f.open(name, ios::out);
		if(!f.is_open())
			return;
	}
	else
	{
		f.open(name, ios::app);
		if(!f.is_open())
			return;
	}

	f << msg << endl;

	f.close();
	
	return;
}
