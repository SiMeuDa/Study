#include <iostream>
#define MAX 10000
#define MIN 1

int main(void){
    int input;
    if(!(std::cin >> input) || input > MAX || input < MIN) return -1;
    
    for(int i = input - 1; i >= 1; i--)
        input += i;
    
    std::cout << input;
    
    return 0;
}
