#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <string>
#include <variant>

#include "comp/resistor.h"
#include "prime/terminal_2way.h"
#include "netlist.pb.h"
#include "prime/net.h"


void load_design(std::list<std::shared_ptr<Net>>& nets, std::list<std::shared_ptr<Terminal_2Way>>& elements);