#pragma once
#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

class exponential
{
private:
	const double e_upper_bound = 2.8;
	long long factorial(int n);
public:
	long long power(long long x, int y);
	double e(int DP);
};

#endif