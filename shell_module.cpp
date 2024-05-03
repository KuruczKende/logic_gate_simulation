#include "shell_module.h"
/**
 * Constructor for shell_module_t class.
 *
 * @param ports the number of ports to initialize
 */
shell_module_t::shell_module_t(size_t ports) {
    beDb = kiDb = ports;
    if (ports == 0) {
        kiErtek = beErtek = nullptr;
        kiPorts = nullptr;
    }
    else {
        kiErtek = beErtek = new uint8_t[ports];
        kiPorts = new lista<port<module_t*>>[ports];
    }
}
module_t* shell_module_t::copy() {
    return new shell_module_t(this->beDb);
}
/**
 * Initializes the shell module with the given number of ports.
 *
 * @param ports the number of ports to initialize
 */
void shell_module_t::init(size_t ports) {
    delete[] beErtek;
    delete[] kiPorts;
    beDb = kiDb = ports;
    if (ports == 0) {
        kiErtek = beErtek = nullptr;
        kiPorts = nullptr;
    }
    else {
        kiErtek = beErtek = new uint8_t[ports];
        for (size_t i = 0; i < ports; i++)
            kiErtek[i] = '?';
        kiPorts = new lista<port<module_t*>>[ports];
    }
}
/**
 * Sets the value at the specified Idx in the inputs.
 *
 * @param Idx the Idx at which to set the value
 * @param ertek the value to set
 */
void shell_module_t::setBe(size_t Idx, uint8_t ertek) {
    if (Idx >= kiDb)throw "over Idxed";
    if (Idx < 0)throw "under Idxed";
    kiErtek[Idx] = ertek;
    for (size_t i = 0; i < kiPorts[Idx].length(); i++) {
        port<module_t*> p = kiPorts[Idx][i];
        p.modulep->setBe(p.portszam, ertek);
    }
}

void shell_module_t::addToList(lista<module_t*>& waitForDo, size_t be) {
    for (size_t i = 0; i < kiPorts[be].length(); i++) {
        port<module_t*> p = kiPorts[be][i];
        p.modulep->addToList(waitForDo, p.portszam);
    }
}
/**
 * Destructor for the shell_module_t class.
 */
shell_module_t::~shell_module_t(){
}
