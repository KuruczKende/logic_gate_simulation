#include "port.h"
#include "module.h"

/**
 * Set the value of the module input specified by the port.
 *
 * @param ertek the value to set the module input specified by the port.
 */
void port_t::setin(uint8_t ertek) {
    modulep->setin(idx, ertek);
}
/**
 * Retrieves the module associated with the port.
 *
 * @return a pointer to the module
 */
module_t* port_t::get_module(){
    return modulep;
}
/**
 * Get the index value.
 *
 * @return the index value
 */
size_t port_t::get_idx(){
    return idx;
}
/**
 * Destructor for port_t class.
 */
port_t::~port_t(){}