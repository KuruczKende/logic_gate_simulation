#include "shell_module.h"
/**
 * Constructor for shell_module_t class.
 *
 * @param ports the number of ports to initialize
 */
shell_module_t::shell_module_t(size_t ports) {
    be_db = ki_db = ports;
    if (ports == 0)ki_wires = NULL;
    else {
        ki_wires = new wire_t * [ports];
        for (size_t i = 0; i < ports; i++)
            ki_wires[i] = NULL;
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
    be_db = ki_db = ports;
    delete[] ki_wires;
    if (ports == 0)ki_wires = NULL;
    else {
        ki_wires = new wire_t * [ports];
        for (size_t i = 0; i < ports; i++)
            ki_wires[i] = NULL;
    }
}
/**
 * A function that triggers a specific wire to be processed.
 *
 * @param wait_for_do list of module_t pointers to modules, waiting to be processed
 * @param idx the index of the wire to trigger
 *
 * @return false indicating the function executed successfully
 */
bool shell_module_t::tri_mods(lista<module_t*>& wait_for_do, size_t idx) {
    if(ki_wires[idx]!=NULL)
        ki_wires[idx]->doit(wait_for_do);
    return false;
}
/**
 * Retrieves the output number of the shell module.
 *
 * @return the value of the output number
 */
size_t shell_module_t::get_out_num() {
    return be_db;
}
/**
 * Get the value at index i from inputs.
 *
 * @param i the index of the value to retrieve
 *
 * @return the value at index i in inputs
 */
uint8_t shell_module_t::get_in_ertek(size_t i) {
    if(ki_wires[i]!=NULL)
        return ki_wires[i]->get();
    return undet;
}
/**
 * Sets the value at the specified index in the inputs.
 *
 * @param index the index at which to set the value
 * @param ertek the value to set
 */
void shell_module_t::setin(size_t index, uint8_t ertek) {
    if (index >= be_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    if(ki_wires[index]==NULL)return;
    ki_wires[index]->set(ertek);
    ki_wires[index]->setin();
}
/**
 * Get the value at index i from outputs.
 *
 * @param i the index of the value to retrieve
 *
 * @return the value at index i in outputs
 */
uint8_t shell_module_t::get_out_ertek(size_t i) {
    if(ki_wires[i]!=NULL)
        return ki_wires[i]->get();
    return undet;
}
/**
 * Destructor for the shell_module_t class.
 */
shell_module_t::~shell_module_t(){
}
