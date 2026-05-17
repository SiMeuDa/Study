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
	uint16_t* frequency(std::string);

	double IC(uint16_t*, size_t, uint16_t);
	double Chis(uint16_t*, size_t, uint16_t);
};

uint16_t* formula::frequency(std::string str)
{
	uint16_t alphabet[26];
	//init
	for(int i = 0; i < 26; i++)
		alphabet[i] = 0;

	int len = str.length();

	for(int i = 0; i < len; i++)
		++alphabet[str[i] % 'A'];

	return alphabet;
}

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
	 double Chi = 0;

	for(size_t i = 0; i < size; i++)
		Chi += (pow((static_cast<double>(alpha[i]) / N) - this->alphaFre[i], 2) / this->alphaFre[i]);

	return Chi;
}
