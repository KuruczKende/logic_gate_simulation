#ifndef SHELL_MODULE_H
#define SHELL_MODULE_H
#include "module.h"
class shell_module_t : public module_t {
public:
    shell_module_t(size_t ports = 0);
    module_t* copy() override;
    bool tri_mods(lista<module_t*>& wait_for_do, size_t idx) override;//trigger next modules
    size_t get_out_num() override;
    uint8_t get_out_ertek(size_t i) override;
    uint8_t get_in_ertek(size_t i) override;
    void setin(size_t index, uint8_t ertek) override;
    ~shell_module_t() {}
};
#endif