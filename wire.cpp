#include "wire.h"
#include "port.h"
#include "module.h"
/**
 * Constructor for the wire_t class.
 */
wire_t::wire_t() {
    ertek = undet;
    ports = lista<port_t*>();
}
/**
 * A function that adds the modules of ports to a list of modules after setting inputs.
 *
 * @param wait_for_do list of module_t pointers to modules, waiting to be processed
 */
void wire_t::doit(lista<module_t*>& wait_for_do){
    this->setin();
    for(size_t i=0;i<ports.length();i++){
        module_t* modulep=ports[i]->get_module();
        size_t idx=ports[i]->get_idx();
        if(modulep->tri_mods(wait_for_do, idx))
            wait_for_do.add(modulep);
    }
}
/**
 * Set the value of ertek.
 *
 * @param ertek The new value to set
 */
void wire_t::set(uint8_t ertek) {
    this->ertek = ertek;
}
/**
 * Set the input of all the ports.
*/
void wire_t::setin() {
    for (size_t i = 0; i < ports.length(); i++)
        ports[i]->setin(ertek);
}
/**
 * Return the value of ertek.
*/
uint8_t wire_t::get() {
    return ertek;
}
/**
 * Adds a new port to the wire.
 *
 * @param newport pointer to the port to be added
 */
void wire_t::add(port_t* newport){
    ports.add(newport);
}
/**
 * Adds a new port to the wire with the given module pointer and index.
 *
 * @param modulep pointer to the module to add
 * @param idx index of the port to add
 */
void wire_t::add(module_t* modulep, size_t idx){
    ports.add(new port_t(modulep,idx));
}
/**
 * Destructor for the wire_t class, delete all the ports.
 */
wire_t::~wire_t(){
    ports.din();
}
