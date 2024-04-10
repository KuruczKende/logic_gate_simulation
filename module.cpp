#include "module.h"
#include "wire.h"
/**
 * Sets the output wire at the specified index in the module.
 *
 * @param index the index where the wire will be set
 * @param wire the wire to set at the specified index
 * @param del a boolean indicating whether to delete the existing wire at the index before setting the new wire
 */
void module_t::set_wire(size_t index, wire_t* wire) {
    if (index >= ki_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    ki_wires[index] = wire;
}
/**
 * Destructor for the module_t class. Deletes all the output wires in the module.
 */
module_t::~module_t(){
    delete[] ki_wires;
}
