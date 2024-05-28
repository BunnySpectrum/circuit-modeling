#ifndef _TERMINAL_2WAY_H_
#define _TERMINAL_2WAY_H_

#include "prime/node.h"
#include "utils/uid.h"

class Terminal_2Way{
    public:
        int uid;
        Node lNode;
        Node rNode;
        Terminal_2Way();
        float voltage();
        float current();
        float impedance();
};

#endif