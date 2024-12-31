#include <iostream>
#include "engine.h"
#include "custorage.h"


extern "C"
 {
void engine_initialize() {
    curiox::Storage::init();
}


void engine_create_relation(int dbOid, int relNumber) {
    curiox::Storage::createOnDiskRelation(dbOid, relNumber);
}
 }
