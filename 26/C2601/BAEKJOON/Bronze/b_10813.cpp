#include <iostream>
using namespace std;
#define MAX 100
#define SWAP(x, y, z)    \
    z = x;               \
    x = y;               \
    y = z; 


int main(int argc, char* argv[])
{
    int N, M;
    try{
        if(!(cin >> N >> M))
            throw("Invalid Input");
        if(((N > M) ? N : M) > MAX || ((N < M) ? N : M) < 1)
            throw("Out of Range");
        
        int* arr = new int[N];
        if(arr == nullptr)
            throw("Failed to Allocate Memory");
        
        //initialize to box num
        for(int k = 0; k < N; k++)
            arr[k] = k + 1;
        
        int temp, i, j;
        
        for(int k = 0; k < M; k++)
        {
            if(!(cin >> i >> j))
                throw("Invalid Input");
            
            if(i > j || j > N || i < 1)
                throw("Out of Range");
            
            SWAP(arr[i - 1], arr[j - 1], temp);
        }
        
        for(int k = 0; k < N; k++)
            cout << arr[k] << " ";
        
        delete[] arr;
        
    }catch(const char* msg){
        cerr << "[Error]: " << msg << endl;
        return -1;
    }
    return 0;
}
