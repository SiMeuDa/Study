#include "ABC.h"
#include <random>
#include <limits>

double random(void)
{
	int a = rand() % numeric_limits<int>::min() + numeric_limits<int>::max();
	srand((unsigned int) (&a));
	int b = rand() % numeric_limits<int>::min() + numeric_limits<int>::max();
	return (a) % (b);
}

int main(void)
{
	Imaginary im;
	double value = random();

	if(im.isImaginary(value) == false)
		cout << "Hello," << value << " World" << endl;
	
	return 0;
}