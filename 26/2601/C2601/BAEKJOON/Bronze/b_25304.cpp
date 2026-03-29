#include <iostream>
#define XMAX 1000000000
#define NMAX 100
#define aMAX 1000000
#define bMAX 10
#define MIN 1

int main(void)
{
    int X, N, a, b, money[NMAX];
    if(!(std::cin >> X) || (XMAX < X) || (X < MIN)) return -1;
    if(!(std::cin >> N) || (NMAX < N) || (N < MIN)) return -1;
    
    for(int i = 0; i < N; i++)
    {
        if(!(std::cin >> a) || (aMAX < a) || (a < MIN)) return -1;
        if(!(std::cin >> b) || (bMAX < b) || (b < MIN)) return -1;
        if(i == 0)
            money[i] = a * b;
        else
            money[i] = a * b + money[i -1];
    }
    
    if(money[N - 1] == X)
        std::cout << "Yes";
    else
        std::cout << "No";
    
    return 0;
    
    
}
