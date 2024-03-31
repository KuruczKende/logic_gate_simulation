#ifndef PROT_MODULES_H
#define PROT_MODULES_H
#include "ossz.h"
class prot_module_t {
public:
    char* nev;
    module_t* prot;
    prot_module_t(const char* nev = NULL, module_t* prot = NULL);
    ~prot_module_t() {}
};
#endif