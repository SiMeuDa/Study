#include <iostream>
#define TMAX 1000000
#define ABMAX 1000
#define ABMIN 1

int main(void)
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int T, A, B;
    
    if(!(std::cin >> T) || T > TMAX) return -1;
    for(int i = 0; i < T; i++)
    {
        if(!(std::cin >> A) || A > ABMAX) return -1;
        if(!(std::cin >> B) || B > ABMAX) return -1;
        
        std::cout << A + B << '\n';
    }
    
    return 0;
}
