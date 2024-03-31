#include "module.h"

void module_t::set_wire(size_t index, wire_t* wire) {
    if (index >= ki_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    ki_wires[index] = wire;
}
