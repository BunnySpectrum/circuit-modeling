#ifndef _TERMINAL_2WAY_H_
#define _TERMINAL_2WAY_H_

#include "prime/node.h"
#include "utils/uid.h"

class Terminal_2Way{
    public:
        int32_t uid;
        std::string name;

        std::shared_ptr<Node> pT1Node;
        std::shared_ptr<Node> pT2Node;
        Terminal_2Way(std::string objName);
        float voltage();
        float current();
        float impedance();
};

#endif