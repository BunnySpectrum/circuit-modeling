#include "terminal_2way.h"

Terminal_2Way::Terminal_2Way(std::string objName):
    pT1Node(std::make_shared<Node>(objName + "-T1", "T1")),
    pT2Node(std::make_shared<Node>(objName + "-T2", "T2")){
    uid = UID::next_id();
    name = objName;
}

float Terminal_2Way::voltage(){
    return 1.0;
}

float Terminal_2Way::current(){
    return 2.0;
}

float Terminal_2Way::impedance(){
    return 3.0;
}
