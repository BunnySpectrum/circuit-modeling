#ifndef _TERMINAL_4WAY_H_
#define _TERMINAL_4WAY_H_

#include "prime/terminal_2way.h"
#include "utils/uid.h"

class Terminal_4Way{
    public:
        int32_t uid;
        std::string name;
        Terminal_2Way input;
        Terminal_2Way output;
        Terminal_4Way(std::string objName);

};

#endif