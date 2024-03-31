#include "shell_module.h"
shell_module_t::shell_module_t(size_t ports) {
    be_db = ki_db = ports;
    ki_wires = new wire_t * [ports];
    for (size_t i = 0; i < ports; i++)
        ki_wires[i] = new wire_t();
}
module_t* shell_module_t::copy() {
    return new shell_module_t(this->be_db);
}
bool shell_module_t::tri_mods(lista<module_t*>& wait_for_do, size_t idx) {
    ki_wires[idx]->doit(wait_for_do);
    return false;
}
size_t shell_module_t::get_out_num() {
    return be_db;
}
void shell_module_t::setin(size_t index, uint8_t ertek) {
    if (index >= be_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    ki_wires[index]->set(ertek);
    ki_wires[index]->setin();
}
uint8_t shell_module_t::get_out_ertek(size_t i) {
    return ki_wires[i]->get();
}