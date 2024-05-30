
#include <iostream>
#include <unordered_set>
#include <list>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"



int main(){
    std::cout << "Hello world.\n";

    auto pZ1 = std::make_shared<Terminal_2Way>("Z1");
    auto pZ2 = std::make_shared<Terminal_2Way>("Z2");
    auto pZ3 = std::make_shared<Terminal_2Way>("Z3");
    auto pZ4 = std::make_shared<Terminal_2Way>("Z4");

    auto pVin = std::make_shared<Terminal_2Way>("Vin");

    auto pU1Out = std::make_shared<Terminal_2Way>("U1.Out");
    auto pU1N = std::make_shared<Terminal_2Way>("U1.N");
    auto pU1P = std::make_shared<Terminal_2Way>("U1.P");


    std::list<std::shared_ptr<Terminal_2Way>> passives{pZ1, pZ2, pZ3, pZ4};
    std::list<std::shared_ptr<Terminal_2Way>> sources{pVin};
    std::list<std::shared_ptr<Terminal_2Way>> components{pU1Out, pU1P, pU1N};

    /*
    Z1
        L: Vin-R
        R: Z3-L, Z2-L
    */
    pZ1->pLNode->connect(pVin->pRNode);
    pZ1->pRNode->connect(pZ3->pLNode);
    pZ1->pRNode->connect(pZ2->pLNode);


    /*
    Z2
        L: Z1-R, Z3-L
        R: Z4-L, U1.P-L
    */
    // z2.lNode.connect(z1.rNode);
    // z2.lNode.connect(z3.lNode);   
    // z2.rNode.connect(z4.lNode);
    // z2.rNode.connect(u1P.lNode);

    /*
    Z3
        L: Z1-R, Z2-L
        R: U1.Out-R, U1.N-L
    */
    // z3.lNode.connect(z1.rNode);
    // z3.lNode.connect(z2.lNode);
    // z3.rNode.connect(u1Out.rNode);
    // z3.rNode.connect(u1N.lNode);

    std::cout << "List:" << std::endl;
    std::list<std::shared_ptr<Terminal_2Way>>::iterator itr;
    std::unordered_set<std::shared_ptr<Node>>::iterator itrLinks;
    for (itr = passives.begin(); itr != passives.end(); itr++){
        std::cout << (*itr)->name << std::endl;

        std::cout << "Left node: " << (*itr)->pLNode->connections.size() << std::endl;
        for(std::shared_ptr<Node> pNode : (*itr)->pLNode->connections){
            std::cout << '\t' << pNode->name << std::endl;
        }

        std::cout << "Right node: " << (*itr)->pRNode->connections.size() << std::endl;
        for(itrLinks = (*itr)->pRNode->connections.begin(); itrLinks != (*itr)->pRNode->connections.end(); itrLinks++){
            std::cout << '\t' << (*itrLinks)->name << std::endl;
        }

        

        std::cout << std::endl;


    }



    return 0;
}