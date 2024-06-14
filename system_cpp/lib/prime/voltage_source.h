#ifndef _VOLTAGE_SOURCE_H_
#define _VOLTAGE_SOURCE_H_

#include "prime/node.h"
#include "prime/element.h"
#include "utils/uid.h"
#include "netlist.pb.h"

class Voltage_Source : public Element{
    public:
        Voltage_Source(std::string objName);
        virtual std::list<std::shared_ptr<Node>> get_nodes();
        virtual std::unique_ptr<netlist::Element> to_proto();


        // int32_t uid;
        // std::string name;

        std::shared_ptr<Node> pPosNode;
        std::shared_ptr<Node> pNegNode;
};



#endif