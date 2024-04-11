#include "shell_module.h"
/**
 * Constructor for shell_module_t class.
 *
 * @param ports the number of ports to initialize
 */
shell_module_t::shell_module_t(size_t ports) {
    be_db = ki_db = ports;
    if (ports == 0) {
        ki_ertek = be_ertek = nullptr;
        ki_ports = nullptr;
    }
    else {
        ki_ertek = be_ertek = new uint8_t[ports];
        ki_ports = new lista<port<module_t*>>[ports];
    }
}
module_t* shell_module_t::copy() {
    return new shell_module_t(this->be_db);
}
/**
 * Initializes the shell module with the given number of ports.
 *
 * @param ports the number of ports to initialize
 */
void shell_module_t::init(size_t ports) {
    delete[] be_ertek;
    delete[] ki_ports;
    be_db = ki_db = ports;
    if (ports == 0) {
        ki_ertek = be_ertek = nullptr;
        ki_ports = nullptr;
    }
    else {
        ki_ertek = be_ertek = new uint8_t[ports];
        ki_ports = new lista<port<module_t*>>[ports];
    }
}
/**
 * Sets the value at the specified index in the inputs.
 *
 * @param index the index at which to set the value
 * @param ertek the value to set
 */
void shell_module_t::set_be(size_t index, uint8_t ertek) {
    if (index >= ki_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    ki_ertek[index] = ertek;
    for (size_t i = 0; i < ki_ports[index].length(); i++) {
        port<module_t*> p = ki_ports[index][i];
        p.modulep->set_be(p.portszam, ertek);
    }
}
/**
 * Destructor for the shell_module_t class.
 */
shell_module_t::~shell_module_t(){
}
