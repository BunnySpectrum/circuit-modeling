
#include <iostream>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"


int main(){
    std::cout << "Hello world.\n";
    Resistor r1(10), r2(100);
    Terminal_2Way t1(20), t2(42);

    std::cout << r1.value << "\n";
    std::cout << r2.value << "\n";
    std::cout << t1.value << "\n";
    std::cout << t2.value << "\n";


    return 0;
}