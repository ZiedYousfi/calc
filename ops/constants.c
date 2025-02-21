#include "constants.h"

const operators ops[] = {{"add", "+"},
                         {"subtract", "-"},
                         {"multiply", "*"},
                         {"divide", "/"},
                         {"sinus", "sin"}};

const int OPS_COUNT = sizeof(ops) / sizeof(ops[0]);
