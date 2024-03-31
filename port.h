#ifndef PORT_H
#define PORT_H
#include "ossz.h"
class port_t {
    module_t* modulep;
    int idx;
public:
    port_t(module_t* modulep, size_t idx) :modulep(modulep), idx(idx) {}
    module_t* doit(uint8_t ertek);
    void setin(uint8_t ertek);
    module_t* get_module();
    size_t get_idx();
    ~port_t() {}
};
#endif