
#include <iostream>
#include <unordered_set>
#include <list>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"



int main(){
    std::cout << "Hello world.\n";
    Terminal_2Way z1("Z1"), z2("Z2"), z3("Z3"), z4("Z4");
    Terminal_2Way vin("Vin");
    Terminal_2Way u1Out("U1.Out"), u1N("U1.N"), u1P("U1.P");

    std::list<Terminal_2Way> passives{z1, z2, z3, z4};
    std::list<Terminal_2Way> sources{vin};
    std::list<Terminal_2Way> components{u1Out, u1N, u1P};

    /*
    Z1
        L: Vin-R
        R: Z3-L, Z2-L
    */
    z1.lNode.connect(vin.rNode);
    z1.rNode.connect(z3.lNode);
    z1.rNode.connect(z2.lNode);

    /*
    Z2
        L: Z1-R, Z3-L
        R: Z4-L, U1.P-L
    */
    z2.lNode.connect(z1.rNode);
    z2.lNode.connect(z3.lNode);   
    z2.rNode.connect(z4.lNode);
    z2.rNode.connect(u1P.lNode);

    /*
    Z3
        L: Z1-R, Z2-L
        R: U1.Out-R, U1.N-L
    */
    z3.lNode.connect(z1.rNode);
    z3.lNode.connect(z2.lNode);
    z3.rNode.connect(u1Out.rNode);
    z3.rNode.connect(u1N.lNode);

    std::cout << "List:" << std::endl;
    std::list<Terminal_2Way>::iterator itr;
    for (itr = passives.begin(); itr != passives.end(); itr++){
        std::cout << itr->name << std::endl;
    }



    return 0;
}