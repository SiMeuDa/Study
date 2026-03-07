#include <iostream>
using namespace std;
#define MAX 100

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
        
        int i, j, k;
        for(int l = 0; l < M; l++)
        {
            if(!(cin >> i >> j >> k))
                throw("Invalid Input");
            
            if(i > j || j > N || k > N)
                throw("Out of Range");
            
            for(int p = i - 1; p < j; p++)
                arr[p] = k;
        }
        
        for(int l = 0; l < N; l++)
            cout << arr[l] << " ";
        delete[] arr;
        
    }catch(const char* msg){
        cerr << "[Error]: " << msg << endl;
        return -1;
    }
    return 0;
}
