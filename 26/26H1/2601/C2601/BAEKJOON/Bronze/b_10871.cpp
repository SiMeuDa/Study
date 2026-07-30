#include <iostream>
using namespace std;
#define MAX 10000
#define MIN 1

int main(void)
{
	int N = 0, X = 0, input, count = 0;

	try{
		if(!(cin >> N >> X) && ((N >= MIN) && (N <= MAX)) && (X >= MIN) && (X <= MAX))
			throw("Invalid Input");
		for(int i = 0; i < N; i++)
		{
			if(!(cin >> input))
				throw("Invalid Input");
			if(input < X)
				cout << input << " ";
		}
	}catch(const char* msg){
		cerr << "[Error]: " << msg << endl;
		return -1;
	}
	
	return 0;
}
