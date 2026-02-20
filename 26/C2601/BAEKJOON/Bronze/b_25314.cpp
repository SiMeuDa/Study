#include <iostream>
#define NMAX 1000
#define NMIN 4

int main(void)
{
    int N;
    if(!(std::cin >> N) || (N > NMAX) || (N < NMIN)) return -1;
    
    for(int i = 0; i < N / 4; i++)
        std::cout << "long ";
    std::cout << "int";
    
    return 0;
}
