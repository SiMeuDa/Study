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
	
	cout << "e�� �� ��° �ڸ����� ����ұ��?" << endl;
	cin >> select;
	
	cout << setprecision(select) << et.e(select) << endl;
 	
	return 0;
}