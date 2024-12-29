#include <iostream>
#include "engine.h"

extern "C"
 {
void engine_initialize() {
    std::cout <<"Initializing engine" << std::endl;
}
 }
