#include <iostream>
using namespace std;

class Nature {
private:
	bool isZero(double value)
	{
		if (value == 0) return true;
		return false;
	}

	bool isDecimal(double value)
	{
		if ((int)value != value) return true;
		return false;
	}

	bool isNegative(double value)
	{
		if (value < 0) return true;
		return false;
	}

public:
	bool isNature(double value)
	{
		if (isZero(value) != false && isDecimal(value) != false && isNegative(value) != false) return true;
		return false;
	}
};

class Integar : Nature {
private:
	bool isDecimal(double value)
	{
		if ((int)value != value) return true;
		return false;
	}
public:
	bool isIntegar(double value)
	{
		if (isNature(value) == true || isDecimal(value) == false) return true;
		return false;
	}
};

class Rational : Integar {
public:
	bool isRational(double value)
	{
		for (int i = 1; i < sqrt(value); i++)
			if (isIntegar(value) == true || isIntegar(value / i) == true) return true;
		return false;
	}
};

class Irrational : Rational {
public:
	bool isIrrational(double value)
	{
		if (isRational(value) == false) return true;
		return false;
	}
};

class Real : Irrational, Rational {
public:
	bool isReal(double value)
	{
		if (Rational::isRational(value) == true || isIrrational(value) == true) return true;
		return false;
	}
};

class Imaginary : Real {
public:
	bool isImaginary(double value)
	{
		if (isReal(value) == false) return true;
		return false;
	}
};