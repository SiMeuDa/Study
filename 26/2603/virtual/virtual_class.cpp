#include <iostream>
using namespace std;

class A{
public:
	virtual void make(void) { cout << "TOP" << endl; }
	virtual ~A() {}
};

class B : public A{
	void make(void) override { cout << "1" << endl;}
};

class C : public A{
	void make(void) override { cout << "BOTTOM" << endl; }
};

int main(void)
{
	int choice;
	cout << "Make A choice: ";
	cin >> choice;
	A* a;

	if(choice == 0)
		a = new B();
	else
		a = new C();

	a->make();
	
	delete a;

	return 0;
}
