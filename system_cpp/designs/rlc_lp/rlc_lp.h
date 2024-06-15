#ifndef _RLC_LP_H_
#define _RLC_LP_H_

#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <string>
#include <variant>

#include "circuit/circuit.h"
#include "comp/resistor.h"
#include "prime/terminal_2way.h"
#include "prime/voltage_source.h"
#include "prime/element.h"
#include "netlist.pb.h"
#include "prime/net.h"

class Circuit_RLC_LP : public Circuit{
    public:
        Circuit_RLC_LP(std::string name) : Circuit(name){};
        virtual void load_design(std::list<std::shared_ptr<Net>>& nets, std::list<std::shared_ptr<Element>>& elements);
};


#endif