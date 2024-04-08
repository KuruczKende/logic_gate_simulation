#ifndef COMP_MODULE_H
#define COMP_MODULE_H
#include "shell_module.h"
#include "prot_modules.h"
class comp_module_t : public shell_module_t {
    shell_module_t end_module;
    module_t** modules;
    wire_t* wires;
    size_t m_db;
    size_t w_db;
    char* modules_coms;
public:
    comp_module_t(char* modules_coms, lista<prot_module_t*>& prot_modules);
    //comp_module_t(const comp_module_t& refe);
    comp_module_t(size_t be_db, size_t ki_db, size_t m_db, size_t w_db);
    module_t* copy() override;
    size_t get_out_num();
    uint8_t get_out_ertek(size_t i);
    void set_wire(size_t index, wire_t* wire, bool del)override;
    ~comp_module_t();
};
#endif
