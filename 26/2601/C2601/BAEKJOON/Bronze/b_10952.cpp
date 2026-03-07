#include <iostream>
#define ABMAX 10
#define ABMIN 0

int main(void)
{
    int A, B;
    while(A || B)   
    {
        if(!(std::cin >> A) || A > ABMAX || A < ABMIN) return -1;
        if(!(std::cin >> B) || B > ABMAX || B < ABMIN) return -1;
        
        if(!(A || B))
            break;
        std::cout << A + B << '\n';
    }
    return 0;
}
