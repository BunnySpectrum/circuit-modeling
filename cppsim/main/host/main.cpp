
#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <string>
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

    pNetVin->add_node(pVin->pRNode);
    pNetVin->add_node(pZ1->pLNode);

    pNetZTee->add_node(pZ1->pRNode);
    pNetZTee->add_node(pZ2->pLNode);
    pNetZTee->add_node(pZ3->pLNode);

    pNetU1P->add_node(pZ2->pRNode);
    pNetU1P->add_node(pZ4->pLNode);
    pNetU1P->add_node(pU1P->pRNode);

    pNetVout->add_node(pZ3->pRNode);
    pNetVout->add_node(pU1Out->pRNode);
    pNetVout->add_node(pU1N->pRNode);

    pNetGnd->add_node(pVin->pLNode);
    pNetGnd->add_node(pZ4->pRNode);
    pNetGnd->add_node(pU1Vss->pRNode);

    pNetVmain->add_node(pU1Vdd->pRNode);

    /*
    Z1
        L: Vin-R
        R: Z3-L, Z2-L
    */
    // pZ1->pLNode->connect(pVin->pRNode);
    // pZ1->pRNode->connect(pZ2->pLNode);
    // pZ1->pRNode->connect(pZ3->pLNode);


    /*
    Z2
        L: Z1-R, Z3-L
        R: Z4-L, U1.P-L
    */
    // pZ2->pLNode->connect(pZ3->pLNode);
    // pZ2->pRNode->connect(pZ4->pLNode);
    // pZ2->pRNode->connect(pU1P->pRNode);

    /*
    Z3
        L: Z1-R, Z2-L
        R: U1.Out-R, U1.N-L
    */
    // pZ3->pRNode->connect(pU1Out->pRNode);
    // pZ3->pRNode->connect(pU1N->pRNode);

    // pZ4->pRNode->connect(pVin->pLNode);
    // pZ4->pRNode->connect(pVdd->pLNode);
    // pZ4->pRNode->connect(pU1Vss->pRNode);

    // pU1Vdd->pRNode->connect(pVdd->pRNode);


    netlist::NodeList pbNodeList;
    netlist::NetList pbNetList;
    netlist::Node* pbNode;
    netlist::Net* pbNet;

    std::list<std::shared_ptr<Net>>::iterator itrNet;
    std::cout << "Nets:" << std::endl;
    for(itrNet = nets.begin(); itrNet != nets.end(); itrNet++){
        std::cout << (*itrNet)->name << std::endl;
        pbNet = pbNetList.add_nets();
        pbNet->set_uid((*itrNet)->uid);
        pbNet->set_name((*itrNet)->name);
        
        for(std::shared_ptr<Node> pNode : (*itrNet)->connections){
            std::cout << "\t" << pNode->name << std::endl;
            
            netlist::Net::Connection* pbConn = pbNet->add_connections();
            pbConn->set_number(pNode->uid);
            pbConn->set_type(netlist::NODE_TYPE_UNSPECIFIED);
            pbConn->set_name(pNode->name);


        }



    }

    // return 0;

    std::cout << "Nodes:" << std::endl;
    std::list<std::shared_ptr<Terminal_2Way>>::iterator itr;

    std::unordered_set<std::shared_ptr<Node>>::iterator itrLinks;
    for (itr = design.begin(); itr != design.end(); itr++){
    
        std::cout << (*itr)->name << std::endl;

        std::cout << "Left node: " << (*itr)->pLNode->connections.size() << std::endl;
        pbNode = pbNodeList.add_nodes();
        pbNode->set_uid((*itr)->pLNode->uid);
        pbNode->set_name((*itr)->pLNode->name);
        for(std::shared_ptr<Node> pNode : (*itr)->pLNode->connections){

            // netlist::Node::Connection* pbConn = pbNode->add_connections();
            // pbConn->set_number(pNode->uid);
            // pbConn->set_type(netlist::NODE_TYPE_UNSPECIFIED);
            // pbConn->set_name(pNode->name);

            std::cout << '\t' << pNode->name << std::endl;
        }



        std::cout << "Right node: " << (*itr)->pRNode->connections.size() << std::endl;
        pbNode = pbNodeList.add_nodes();
        pbNode->set_uid((*itr)->pRNode->uid);
        pbNode->set_name((*itr)->pRNode->name);

        for(itrLinks = (*itr)->pRNode->connections.begin(); itrLinks != (*itr)->pRNode->connections.end(); itrLinks++){
            // netlist::Node::Connection* pbConn = pbNode->add_connections();
            // pbConn->set_number((*itrLinks)->uid);
            // pbConn->set_type(netlist::NODE_TYPE_UNSPECIFIED);
            // pbConn->set_name((*itrLinks)->name);

            std::cout << '\t' << (*itrLinks)->name << std::endl;
        }

        

        std::cout << std::endl;


    }



    
    




    {
    // Write the new address book back to disk.
    std::fstream output("pb_netlist.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    // if (!pbNodeList.SerializeToOstream(&output)) {
    //   std::cerr << "Failed to write nodelist book." << std::endl;
    //   return -1;
    // }
    if (!pbNetList.SerializeToOstream(&output)) {
      std::cerr << "Failed to write netlist book." << std::endl;
      return -1;
    }
  }
    



    return 0;
}