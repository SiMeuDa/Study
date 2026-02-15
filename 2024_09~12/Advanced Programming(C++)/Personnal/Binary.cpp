#include "Number"

int main(void)
{
    int value;
    std::cout << "Enter a number: "; //<< value << std::endl;

    std::cin >> value;
    Binary binary(value);

    std::cout << "Binary representation: ";
    binary.print_binary();
    std::cout << std::endl;
/*
    std::cout << "Octal representation: ";
    binary.print_octal();
    std::cout << std::endl;
*/
    std::cout << "Hexadecimal representation: ";
    binary.print_hexa();
    std::cout << std::endl;
    return 0;
}   