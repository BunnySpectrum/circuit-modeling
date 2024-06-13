#include "sallen_key/design.h"

/*


                    +---|  Z3  |-------------------------------+
                    |                                          |
                    |                      ________________    |
(Vin) ---|  Z1  |---+---|  Z2  |---+------|> U1.P          |   |
                                   |      |        U1.Out  >---+---(Vout)  
                                   Z4  +--|> U1.N          |   |
                                   |   |   ----------------    |
                                 (Gnd) +-----------------------+
*/

void load_design(std::list<std::shared_ptr<Net>>& nets, std::list<std::shared_ptr<Terminal_2Way>>& elements){
    std::cout << "loading design." << std::endl;


    // Create elements
    auto pVin = std::make_shared<Terminal_2Way>("Vin");
    elements.push_back(pVin);

    auto pVdd = std::make_shared<Terminal_2Way>("Vdd");
    elements.push_back(pVdd);


    auto pZ1 = std::make_shared<Terminal_2Way>("Z1");
    elements.push_back(pZ1);

    auto pZ2 = std::make_shared<Terminal_2Way>("Z2");
    elements.push_back(pZ2);

    auto pZ3 = std::make_shared<Terminal_2Way>("Z3");
    elements.push_back(pZ3);
    
    auto pZ4 = std::make_shared<Terminal_2Way>("Z4");
    elements.push_back(pZ4);

    // U1
    auto pU1Out = std::make_shared<Terminal_2Way>("U1.Out");
    elements.push_back(pU1Out);

    auto pU1N = std::make_shared<Terminal_2Way>("U1.N");
    elements.push_back(pU1N);

    auto pU1P = std::make_shared<Terminal_2Way>("U1.P");
    elements.push_back(pU1P);

    auto pU1Vdd = std::make_shared<Terminal_2Way>("U1.Vdd");
    elements.push_back(pU1Vdd);

    auto pU1Vss = std::make_shared<Terminal_2Way>("U1.Vss");
    elements.push_back(pU1Vss);


    // Nets
    auto pNetVin = std::make_shared<Net>("Vin");
    pNetVin->add_node(pVin->pT2Node);
    pNetVin->add_node(pZ1->pT1Node);
    nets.push_back(pNetVin);


    auto pNetZTee = std::make_shared<Net>("ZTee");
    pNetZTee->add_node(pZ1->pT2Node);
    pNetZTee->add_node(pZ2->pT1Node);
    pNetZTee->add_node(pZ3->pT1Node);
    nets.push_back(pNetZTee);
    
    auto pNetU1P = std::make_shared<Net>("U1P");
    pNetU1P->add_node(pZ2->pT2Node);
    pNetU1P->add_node(pZ4->pT1Node);
    pNetU1P->add_node(pU1P->pT2Node);
    nets.push_back(pNetU1P);
    
    auto pNetVout = std::make_shared<Net>("Vout");
    pNetVout->add_node(pZ3->pT2Node);
    pNetVout->add_node(pU1Out->pT2Node);
    pNetVout->add_node(pU1N->pT2Node);
    nets.push_back(pNetVout);
    
    auto pNetVmain = std::make_shared<Net>("Vmain");
    pNetVmain->add_node(pU1Vdd->pT2Node);
    pNetVmain->add_node(pVdd->pT2Node);
    nets.push_back(pNetVmain);

    auto pNetGnd = std::make_shared<Net>("Gnd");
    pNetGnd->add_node(pVin->pT1Node);
    pNetGnd->add_node(pVdd->pT1Node);
    pNetGnd->add_node(pZ4->pT2Node);
    pNetGnd->add_node(pU1Vss->pT2Node);
    nets.push_back(pNetGnd);


    return;
}