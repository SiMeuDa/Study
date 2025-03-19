#include <iostream>
#include <string>
using namespace std;

class Computer{
public:
    string name;
    unsigned int RAM;
    string cpu_type;
    double cpu_speed;
    Computer(){}
    ~Computer() {print(); }
    
private:
    void print(void);
};

void Computer::print(void){
    cout << "이름: " << name << endl;
    cout << "RAM: " << RAM << "GB" << endl;
    cout << "CPU 종류: " << cpu_type << endl;
    cout << "CPU 속도: " << cpu_speed << "GHz" << endl;
}

int main(void)
{
    Computer computer;

    computer.name = "해피쏭 노트북";
    computer.RAM = 16;
    computer.cpu_type = "인텔 코어i7-12세대";
    computer.cpu_speed = 2.4;

    return 0;
}
