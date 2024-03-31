#include "wire.h"
#include "port.h"
#include "module.h"
wire_t::wire_t() {
    ertek = undet;
    ports = lista<port_t*>();
}
void wire_t::doit(lista<module_t*>& wait_for_do){
    this->setin();
    for(size_t i=0;i<ports.length();i++){
        module_t* modulep=ports[i]->get_module();
        size_t idx=ports[i]->get_idx();
        if(modulep->tri_mods(wait_for_do, idx))
            wait_for_do.add(modulep);
    }
}
void wire_t::set(uint8_t ertek) {
    this->ertek = ertek;
}
void wire_t::setin() {
    for (size_t i = 0; i < ports.length(); i++)
        ports[i]->setin(ertek);
}
uint8_t wire_t::get() {
    return ertek;
}
void wire_t::add(port_t* newport){
    ports.add(newport);
}
void wire_t::add(module_t* modulep, size_t idx){
    ports.add(new port_t(modulep,idx));
}
