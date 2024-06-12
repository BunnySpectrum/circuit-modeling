
#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <string>
#include <variant>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"
#include "netlist.pb.h"
#include "prime/net.h"

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

int main(){
    std::cout << "Hello world.\n";

    auto pNetVin = std::make_shared<Net>("Vin");
    auto pNetZTee = std::make_shared<Net>("ZTee");
    auto pNetU1P = std::make_shared<Net>("U1P");
    auto pNetVout = std::make_shared<Net>("Vout");
    auto pNetVmain = std::make_shared<Net>("Vmain");
    auto pNetGnd = std::make_shared<Net>("Gnd");



    auto pZ1 = std::make_shared<Terminal_2Way>("Z1");
    auto pZ2 = std::make_shared<Terminal_2Way>("Z2");
    auto pZ3 = std::make_shared<Terminal_2Way>("Z3");
    auto pZ4 = std::make_shared<Terminal_2Way>("Z4");

    auto pVin = std::make_shared<Terminal_2Way>("Vin");
    auto pVdd = std::make_shared<Terminal_2Way>("Vdd");
    // auto pGnd = std::make_shared<Terminal_2Way>("Gnd");

    auto pU1Out = std::make_shared<Terminal_2Way>("U1.Out");
    auto pU1N = std::make_shared<Terminal_2Way>("U1.N");
    auto pU1P = std::make_shared<Terminal_2Way>("U1.P");
    auto pU1Vdd = std::make_shared<Terminal_2Way>("U1.Vdd");
    auto pU1Vss = std::make_shared<Terminal_2Way>("U1.Vss");


    std::list<std::shared_ptr<Terminal_2Way>> passives{pZ1, pZ2, pZ3, pZ4};
    std::list<std::shared_ptr<Terminal_2Way>> sources{pVin, pVdd};
    std::list<std::shared_ptr<Terminal_2Way>> components{pU1Out, pU1P, pU1N, pU1Vdd, pU1Vss};

    std::list<std::shared_ptr<Net>> nets{pNetVin, pNetZTee, pNetU1P, pNetVout, pNetVmain, pNetGnd};

    std::list<std::shared_ptr<Terminal_2Way>> design;
    design.insert(design.end(), passives.begin(), passives.end());
    design.insert(design.end(), sources.begin(), sources.end());
    design.insert(design.end(), components.begin(), components.end());

    pNetVin->add_node(pVin->pT2Node);
    pNetVin->add_node(pZ1->pT1Node);

    pNetZTee->add_node(pZ1->pT2Node);
    pNetZTee->add_node(pZ2->pT1Node);
    pNetZTee->add_node(pZ3->pT1Node);

    pNetU1P->add_node(pZ2->pT2Node);
    pNetU1P->add_node(pZ4->pT1Node);
    pNetU1P->add_node(pU1P->pT2Node);

    pNetVout->add_node(pZ3->pT2Node);
    pNetVout->add_node(pU1Out->pT2Node);
    pNetVout->add_node(pU1N->pT2Node);

    pNetGnd->add_node(pVin->pT1Node);
    pNetGnd->add_node(pVdd->pT1Node);
    pNetGnd->add_node(pZ4->pT2Node);
    pNetGnd->add_node(pU1Vss->pT2Node);

    pNetVmain->add_node(pU1Vdd->pT2Node);
    pNetVmain->add_node(pVdd->pT2Node);


    netlist::System pbSystem;

    std::unique_ptr<netlist::Node> pNodePB;


    netlist::NetList* pbNetList = pbSystem.mutable_netlist();
    google::protobuf::RepeatedPtrField<netlist::Net> *pNetlistNetsPB = pbNetList->mutable_nets();
    std::unique_ptr<netlist::Net> pNetPB;

    netlist::ElementList* pbElementList = pbSystem.mutable_elementlist();
    google::protobuf::RepeatedPtrField<netlist::Element> *pElementsPB = pbElementList->mutable_elements();
    std::unique_ptr<netlist::Element> pElementPB;

    std::cout << "Nets:" << std::endl;
    for(const std::shared_ptr<Net>& net : nets){
        std::cout << "\t" << net->name << std::endl;
        pNetPB = net->to_proto();
        pNetlistNetsPB->AddAllocated(pNetPB.release());
    }


    std::cout << "Elements:" << std::endl;
    for (const std::shared_ptr<Terminal_2Way>& elementT2 : design){
    
        std::cout << "\t" << elementT2->name << std::endl;
        pElementPB = elementT2->to_proto();
        pElementsPB->AddAllocated(pElementPB.release());
    }


  {    
    std::fstream output("pb_system.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!pbSystem.SerializeToOstream(&output)) {
      std::cerr << "Failed to write system to disk." << std::endl;
      return -1;
    }
  }


    return 0;
}