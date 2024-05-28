#include "utils/uid.h"

static int64_t id = 0;

int64_t UID::next_id(){
    return id++;
}