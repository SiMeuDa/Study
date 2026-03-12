#include <iostream>
#include "mode.h"
using namespace std;

int main(void)
{
	mode m;

	if(m.run())
		cout << "SUCCESS" << endl;
	else
		cout << "FAIL" << endl;

	return 0;
}
