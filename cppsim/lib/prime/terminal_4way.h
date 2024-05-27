#ifndef _TERMINAL_4WAY_H_
#define _TERMINAL_4WAY_H_

#include "prime/terminal_2way.h"

class Terminal_4Way{
    public:
        int id;
        float value;
        Terminal_2Way input;
        Terminal_2Way output;
        Terminal_4Way();

};

#endif