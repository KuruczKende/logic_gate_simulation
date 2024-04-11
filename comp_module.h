#ifndef COMP_MODULE_H
#define COMP_MODULE_H
#include "shell_module.h"
#include "prot_modules.h"
class comp_module_t : public shell_module_t {
    shell_module_t end_module;
    module_t** modules;
    size_t m_db;
    char* modules_coms;
public:
    comp_module_t(char* modules_coms, lista<prot_module_t*>& prot_modules);
    //comp_module_t(const comp_module_t& refe);
    comp_module_t(size_t be_db, size_t ki_db, size_t m_db);
    module_t* copy() override;
    void set_ki_port(size_t ki_index, module_t* modulep, size_t be_index) {
        end_module.set_ki_port(ki_index, modulep, be_index);
    }
    uint8_t get_ki_ertek(size_t i) {
        return end_module.get_be_ertek(i);
    }
    void set_connection(char c, module_t*& base, size_t ki_index);
    void comp_fill_module(bool copy, lista<size_t>& vegk, lista<size_t>& kezk, lista<prot_module_t*>* prot_modules, module_t**& modules_ref);
    ~comp_module_t();
};
#endif
