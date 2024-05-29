#include "terminal_4way.h"

Terminal_4Way::Terminal_4Way(std::string objName):
    input(objName + ".in"),
    output(objName + ".out")
    {
        uid = UID::next_id();
        name = objName;
}