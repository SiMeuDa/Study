#include <iostream>
#define N 100

int main(int argc, char* argv[])
{
    unsigned int max = 0, input, m_index;
    for(unsigned int i = 0; i < 9; i++)
    {
        if(!(std::cin >> input) || (input > N))
            return -1;
        
        if(max < input)
        {
            max = input;
            m_index = i;
        }
    }
    
    std::cout << max << std::endl << m_index + 1;
    
    return 0;
}
