#ifndef _TERMINAL_2WAY_H_
#define _TERMINAL_2WAY_H_

#include "prime/node.h"
#include "utils/uid.h"
#include "netlist.pb.h"

class Terminal_2Way{
    public:
        Terminal_2Way(std::string objName);
        std::unique_ptr<netlist::Element> to_proto();

        int32_t uid;
        std::string name;

        std::shared_ptr<Node> pT1Node;
        std::shared_ptr<Node> pT2Node;
        float voltage();
        float current();
        float impedance();
};

#endif