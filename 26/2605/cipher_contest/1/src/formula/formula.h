#include <cstdint>
#include <string>
#include <cmath>

class formula{
private:
	static constexpr double alphaFre[26] = {
		8.17, 1.5, 2.78, 4.25, 12.7, 2.23, 2.02, 6.09,
			6.97, 0.15, 0.77, 4.03, 2.41, 6.75, 7.51, 1.93,
		0.1, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 
		1.97, 0.07 };
public:

	double IC(uint16_t*, size_t, uint16_t);
	double Chis(uint16_t*, size_t, uint16_t);
};

double formula::IC(uint16_t* alpha, size_t size, uint16_t N)
{
	double sigma = [](uint16_t* ni, size_t size, uint16_t N) -> double{
		double sum = 0;
		for(size_t i = 0; i < size; i++)
			sum += (ni[i] * (ni[i] - 1));

		return sum;
	}(alpha, size, N);

	return (sigma / (N * (N - 1)));
}

double formula::Chis(uint16_t* alpha, size_t size, uint16_t N)
{
	//alpha == string alphabet count
	
	//alphaFre == question suggested frequency
	// == Ni
	double Chi = 0, FPi, expected, diff;

	for(size_t i = 0; i < size; i++)
	{
		//Freq(Pi)
		FPi = 100 * alpha[i] / N;
		//Freq(Pi) - Freq(Ni)
		diff = (FPi - this->alphaFre[i]);
		//(Freq(Pi) - Freq(Ni))^2
		diff = diff * diff;
		//(Freq(Pi) - Freq(Ni))^2 / Freq(Ni)
		Chi += diff / this->alphaFre[i];
	}

	return Chi;
}
