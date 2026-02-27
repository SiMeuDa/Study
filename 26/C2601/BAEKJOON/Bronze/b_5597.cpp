#include <iostream>
using namespace std;
#define MAX 30

int main(int argc, char* argv[])
{
    int n;
    int arr[MAX];
    
    try{
        for(int i = 0; i < MAX; i++)
            arr[i] = i + 1;
        
        for(int i = 0; i < MAX - 2; i++)
        {
            if(!(cin >> n) || n > MAX)
                throw("Invalid Input");
            
            for(int j = 0; j < MAX; j++)
                if(n == arr[j])
                    arr[j] = 0;
        }
        
        for(int i = 0; i < MAX; i++)
            if((bool)(arr[i]))
                cout << i + 1 << endl;
        
    }catch(const char* msg){
        cerr << "[Error]: " << msg << endl;
        return -1;
    }
    return 0;
}
