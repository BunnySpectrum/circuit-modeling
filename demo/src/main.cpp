
#include <iostream>

class Resistor{
    public:
        int id;
        float value;
        Resistor(float v){
            value = v;
        }
};

class Capacitor{
    public:
        int id;
        float value;
        Capacitor(float v){
            value = v;
        }
};


int main(){
    std::cout << "Hello world.\n";
    Resistor r1(10), r2(100);
    Capacitor c1(0.1e-6), c2(1e-6);

    std::cout << r1.value << "\n";
    std::cout << r2.value << "\n";
    std::cout << c1.value << "\n";
    std::cout << c2.value << "\n";


    return 0;
}