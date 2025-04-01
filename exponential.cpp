#include "exponential.h"

/// <summary>
/// Caculate Factorial
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
long long exponential::factorial(int n) {
	long long result = 1;

	if (n == 0 || n == 1)
		return 1;

	for (int i = 0; i < n; i++){
		result  *= (i + 1);
	}
	
	return result;
}

/// <summary>
/// Pow function in cmath, Support only nature y value
/// </summary>
/// <param name="x">
/// base of exponential
/// </param>
/// <param name="y">
/// degree of exponential
/// </param>
/// <returns></returns>
long long exponential::power(long long x, int y)
{
	if (y == 0)
		return 1;
	else if (y == 1)
		return x;
	else {
		long long temp = x;
		for (int i = 1; i < y; i++){
			x *= temp;
		}
		return x;
	}
}

/// <summary>
///  Caculate Nature Constant's Approximate Value Using Talyor Series and LaGrange Error bound
/// </summary>
/// <param name="DP">
/// : Decimal Point
/// </param>
/// <returns></returns>
double exponential::e(int DP) {
	static double e_value = 0;
	double temp_e = 0;

	for (int i = 0;; i++){
		//LaGrange Error bound (M is 2.8 cause e is smaller than 2.8)
		if (factorial(i + 1) >= power(10, DP) * e_upper_bound)
			break;
		temp_e += 1.0 / factorial(i);
	}
	e_value = temp_e;

	return e_value;
}