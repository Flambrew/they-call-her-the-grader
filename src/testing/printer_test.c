#include "../globals.h"


enum result test_one() {
    return FAIL;
}


enum result (*fn[])() = {&test_one};