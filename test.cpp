#include <iostream>
#include "exponential.h"
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setprecision;


int main(void) {
	exponential et;
	int select;
	
	cout << "e의 몇 번째 자리까지 출력할까요?" << endl;
	cin >> select;
	
	cout << setprecision(select) << et.e(select) << endl;
 	
	return 0;
}