#include "terminal_2way.h"

Terminal_2Way::Terminal_2Way(std::string objName):
    pLNode(std::make_shared<Node>(objName + "-L")),
    pRNode(std::make_shared<Node>(objName + "-R")){
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
