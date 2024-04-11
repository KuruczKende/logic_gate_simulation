#include "module.h"
#include "wire.h"

void module_t::set_ki_port(size_t ki_index, module_t* modulep, size_t be_index) {
    if (ki_index >= ki_db)throw "over indexed";
    if (ki_index < 0)throw "under indexed";
    if (be_index >= modulep->get_be_num())throw "over indexed";
    if (be_index < 0)throw "under indexed";
    ki_ports[ki_index].add(port<module_t*>{modulep, be_index});
}
/**
 * Destructor for the module_t class. Deletes all the output wires in the module.
 */
module_t::~module_t(){
    delete[] be_ertek;
    delete[] ki_ertek;
    delete[] ki_ports;
}
