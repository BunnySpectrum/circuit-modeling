#include "utils/uid.h"

static int32_t id = 0;

int32_t UID::next_id(){
    return id++;
}