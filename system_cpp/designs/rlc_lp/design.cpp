#include "rlc_lp/design.h"

/*
(Vin) ---|  Z1  |---+---|  Z2  |---+
                                   |  
                                   Z3 
                                   |  
                                 (Gnd) 
*/

void load_design(std::list<std::shared_ptr<Net>>& nets, std::list<std::shared_ptr<Element>>& elements){
    std::cout << "Loading: RLC LP." << std::endl;


    // Create elements
    auto pVin = std::make_shared<Voltage_Source>("Vin");
    elements.push_back(pVin);


    auto pZ1 = std::make_shared<Terminal_2Way>("Z1");
    elements.push_back(pZ1);

    auto pZ2 = std::make_shared<Terminal_2Way>("Z2");
    elements.push_back(pZ2);

    auto pZ3 = std::make_shared<Terminal_2Way>("Z3");
    elements.push_back(pZ3);
    

    // Nets
    auto pNetVin = std::make_shared<Net>("Vin");
    pNetVin->add_node(pVin->pPosNode);
    pNetVin->add_node(pZ1->pT1Node);
    nets.push_back(pNetVin);


    auto pNetZMid = std::make_shared<Net>("ZMid");
    pNetZMid->add_node(pZ1->pT2Node);
    pNetZMid->add_node(pZ2->pT1Node);
    nets.push_back(pNetZMid);
    
    auto pNetOut = std::make_shared<Net>("Out");
    pNetOut->add_node(pZ2->pT2Node);
    pNetOut->add_node(pZ3->pT1Node);
    nets.push_back(pNetOut);
    
    auto pNetGnd = std::make_shared<Net>("Gnd");
    pNetGnd->add_node(pVin->pNegNode);
    pNetGnd->add_node(pZ3->pT2Node);
    nets.push_back(pNetGnd);


    return;
}