#include "prot_modules.h"
prot_module_t::prot_module_t(const char* nev, module_t* prot):nev(NULL) {
    this->prot = prot;
    if (nev == NULL) return;
    this->nev = new char[strlen(nev) + 1];
    strcpy(this->nev, nev);
}