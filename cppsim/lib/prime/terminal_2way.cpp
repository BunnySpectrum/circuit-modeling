#include "terminal_2way.h"

Terminal_2Way::Terminal_2Way(){
    uid = UID::next_id();
}

float Terminal_2Way::voltage(){
    return 1.0;
}

float Terminal_2Way::current(){
    return 2.0;
}

float Terminal_2Way::impedance(){
    return 3.0;
}
