#include <iostream>
#define ABMAX 10
#define ABMIN 0

int main(void)
{
    int A, B;
    while(std::cin >> A >> B)
        std::cout << A + B << '\n';

    return 0;
}
