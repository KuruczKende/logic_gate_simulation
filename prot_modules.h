#ifndef PROT_MODULES_H
#define PROT_MODULES_H
#include "module.h"
class prot_module_t {
    char* nev;
    module_t* prot;
public:
    prot_module_t(const char* nev = NULL, module_t* prot = NULL);
    char*& getnev(){return nev;}
    module_t*& getprot(){return prot;}
    ~prot_module_t();
};
#endif
