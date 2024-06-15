#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <string>
#include <variant>
#include "comp/resistor.h"
#include "prime/terminal_2way.h"
#include "prime/voltage_source.h"
#include "netlist.pb.h"
#include "prime/net.h"

#include "sallen_key/sallen_key.h"
#include "rlc_lp/rlc_lp.h"

#define CIRCUIT_RLC_LP
// #define CIRCUIT_SALLEN_KEY

int main(){

    std::list<std::shared_ptr<Net>> circuitNets;
    std::list<std::shared_ptr<Element>> circuitElements;

    // Load a circuit example
    #if defined(CIRCUIT_RLC_LP)
    Circuit_RLC_LP circuitRLC_LP("rlc_lp");
    circuitRLC_LP.load_design(circuitNets, circuitElements);
    #elif defined(CIRCUIT_SALLEN_KEY)
      Circuit_Sallen_Key circuitSallenKey("sallen_key");
      circuitSallenKey.load_design(circuitNets, circuitElements);
    #endif



    netlist::System pbSystem;
    std::unique_ptr<netlist::Node> pNodePB;

    netlist::NetList* pbNetList = pbSystem.mutable_netlist();
    google::protobuf::RepeatedPtrField<netlist::Net> *pNetlistNetsPB = pbNetList->mutable_nets();
    std::unique_ptr<netlist::Net> pNetPB;

    netlist::ElementList* pbElementList = pbSystem.mutable_elementlist();
    google::protobuf::RepeatedPtrField<netlist::Element> *pElementsPB = pbElementList->mutable_elements();
    std::unique_ptr<netlist::Element> pElementPB;

    std::cout << "Nets:" << std::endl;
    for(const std::shared_ptr<Net>& net : circuitNets){
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
    for (const std::shared_ptr<Element>& element : circuitElements){
    
        std::cout << "\t" << element->name() << " [";
        
        bool firstTime = true;
        for(const std::shared_ptr<Node>& node : element->get_nodes()){
          if(firstTime){
            std::cout << node->name;
            firstTime = false;
          }else{
            std::cout << ", " << node->name;
          }
        }
        std::cout << "]" << std::endl;

        pElementPB = element->to_proto();
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