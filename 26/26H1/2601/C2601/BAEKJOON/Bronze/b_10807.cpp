#include <iostream>
using namespace std;

int main(void)
{
	constexpr int limit[4] = {1, 100, -100, 100};
	int N = 0, v = 0, count = 0;
	int* arr;
	try{
		if(!(cin >> N))
			throw("Invaild Input");
		
		arr = new int[N];
		if(arr == nullptr)
			throw("Failed to Allocate Memory");

		for(int i = 0; i < N; i++)
		{
			if(!(cin >> arr[i])){
				delete[] arr;
				throw("Invaild Input");
			}
		}
		
		if(!(cin >> v))
			throw("Invaild Input");

		for(int i = 0; i < N; i++)
			if(v == arr[i])
				count++;

	}catch(const char* msg){
		cerr << "[Error]: " << msg << endl;
		return -1;
	}
	cout << count;
	delete[] arr;

	return 0;
}
