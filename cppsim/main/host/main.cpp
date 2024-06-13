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

#include "sallen_key/design.h"

int main(){

    // Load the sallen key example
    std::list<std::shared_ptr<Net>> skNets;
    std::list<std::shared_ptr<Terminal_2Way>> skElements;
    load_design(skNets, skElements);


    netlist::System pbSystem;

    std::unique_ptr<netlist::Node> pNodePB;


    netlist::NetList* pbNetList = pbSystem.mutable_netlist();
    google::protobuf::RepeatedPtrField<netlist::Net> *pNetlistNetsPB = pbNetList->mutable_nets();
    std::unique_ptr<netlist::Net> pNetPB;

    netlist::ElementList* pbElementList = pbSystem.mutable_elementlist();
    google::protobuf::RepeatedPtrField<netlist::Element> *pElementsPB = pbElementList->mutable_elements();
    std::unique_ptr<netlist::Element> pElementPB;

    std::cout << "Nets:" << std::endl;
    for(const std::shared_ptr<Net>& net : skNets){
        std::cout << "\t" << net->name << " [";

        bool firstTime = true;
        for(const std::shared_ptr<Node>& node : net->connections){
          if(firstTime){
            std::cout << node->name;
            firstTime = false;
          }else{
            std::cout << ", " << node->name;
          }
        }
        std::cout << "]" << std::endl;

        pNetPB = net->to_proto();
        pNetlistNetsPB->AddAllocated(pNetPB.release());
    }


    std::cout << "Elements:" << std::endl;
    for (const std::shared_ptr<Terminal_2Way>& elementT2 : skElements){
    
        std::cout << "\t" << elementT2->name << " [";
        std::cout << elementT2->pT1Node->name << ", " << elementT2->pT2Node->name;
        std::cout << "]" << std::endl;

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