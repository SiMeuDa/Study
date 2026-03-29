#include <iostream>
#define NMAX 100
#define NMIN 1

int main(void)
{
    int N;
    if(!(std::cin >> N) || N > NMAX || N < NMIN) return -1;
    
    for(int i = 1; i <= N; i++){
        for(int j = N; j > i; j--)
            std::cout << " ";
        for(int j = 0; j < i; j++)
            std::cout << "*";
        std::cout << '\n';
    }
    return 0;
}
