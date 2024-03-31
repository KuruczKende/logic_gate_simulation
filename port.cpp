#include "port.h"
#include "module.h"

void port_t::setin(uint8_t ertek) {
    modulep->setin(idx, ertek);
}
module_t* port_t::get_module(){
    return modulep;
}
size_t port_t::get_idx(){
    return idx;
}

