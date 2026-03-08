#include <iostream>
#include "binary.h"
#include <cstdint>
using namespace std;

int main(void)
{
	uint64_t value;
	cout << "input: ";
	cin >> value;

	binary b(value);


	return 0;
}
