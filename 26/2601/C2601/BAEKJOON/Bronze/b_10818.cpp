#include <iostream>
using namespace std;

int main(void)
{
    int N, input, max = -1000000, min = 1000000;
    if(!(cin >> N) || ((N > 1000000) && (N < 1)))
       return -1;
    for(int i = 0; i < N; i++)
    {
        if(!(cin >> input) || ((input > 1000000) && (input < -1000000)))
			return -1;
        max = (max > input) ? max : input;
        min = (min < input) ? min : input;
    }
    cout << min << " " << max;
      
    return 0;
}
