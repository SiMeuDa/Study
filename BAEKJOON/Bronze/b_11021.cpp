#include <iostream>
#define ABMAX 10
#define ABMIN 0
int main(void)
{
    int T, A, B;
    if(!(std::cin >> T)) return -1;
    
    for(int i = 1; i <= T; i++)
    {
        if(!(std::cin >> A) || A > ABMAX || A < ABMIN) return -1;
        if(!(std::cin >> B) || B > ABMAX || B < ABMIN) return -1;
        
        std::cout << "Case #" << i << ": " << A + B << '\n';
    }
    return 0;
}
