#ifndef _TERMINAL_2WAY_H_
#define _TERMINAL_2WAY_H_

#include "prime/node.h"
#include "prime/element.h"
#include "utils/uid.h"
#include "netlist.pb.h"

class Terminal_2Way : public Element{
    public:
        Terminal_2Way(std::string objName);
        virtual std::list<std::shared_ptr<Node>> get_nodes();
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