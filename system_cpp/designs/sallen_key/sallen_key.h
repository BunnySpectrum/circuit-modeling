#ifndef _SALLEN_KEY_DESIGN_H_
#define _SALLEN_KEY_DESIGN_H_

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


class Circuit_Sallen_Key : public Circuit{
    public:
        Circuit_Sallen_Key(std::string name) : Circuit(name){};
        virtual void load_design(std::list<std::shared_ptr<Net>>& nets, std::list<std::shared_ptr<Element>>& elements);
};
#endif