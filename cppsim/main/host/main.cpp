
#include <iostream>
#include <unordered_set>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"


int main(){
    std::cout << "Hello world.\n";
    Terminal_2Way z1, z2, z3, z4, vin, u1Out, u1N, u1P;

    z1.lNode.name = "Z1-L";
    z1.rNode.name = "Z1-R";
    z2.lNode.name = "Z2-L";
    z2.rNode.name = "Z2-R";    
    z3.lNode.name = "Z3-L";
    z3.rNode.name = "Z3-R";  
    z4.lNode.name = "Z4-L";
    z4.rNode.name = "Z4-R";  

    vin.lNode.name = "Vin-L";
    vin.rNode.name = "Vin-R";

    u1Out.lNode.name = "U1.Out-L";
    u1Out.rNode.name = "U1.Out-R";

    u1N.lNode.name = "U1.N-L";
    u1N.rNode.name = "U1.N-R";

    u1P.lNode.name = "U1.P-L";
    u1P.rNode.name = "U1.P-R";

    /*
    Z1
        L: Vin-R
        R: Z3-L, Z2-L
    */
    z1.lNode.connections.insert(vin.rNode);
    z1.rNode.connections.insert(z3.lNode);
    z1.rNode.connections.insert(z2.lNode);

    /*
    Z2
        L: Z1-R, Z3-L
        R: Z4-L, U1.P-L
    */
    z2.lNode.connections.insert(z1.rNode);
    z2.lNode.connections.insert(z3.lNode);   
    z2.rNode.connections.insert(z4.lNode);
    z2.rNode.connections.insert(u1P.lNode);

    /*
    Z3
        L: Z1-R, Z2-L
        R: U1.Out-R, U1.N-L
    */
    z3.lNode.connections.insert(z1.rNode);
    z3.lNode.connections.insert(z2.lNode);
    z3.rNode.connections.insert(u1Out.rNode);
    z3.rNode.connections.insert(u1N.lNode);

    std::cout << "List:" << std::endl;
    std::unordered_set<Node>::iterator itr;
    for (itr = z1.rNode.connections.begin(); itr != z1.rNode.connections.end(); itr++){
        std::cout << (*itr) << std::endl;
    }



    return 0;
}