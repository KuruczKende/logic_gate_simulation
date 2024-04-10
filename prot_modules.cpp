#include "prot_modules.h"
#include "module.h"
/**
 * Constructor for prot_module_t class.
 *
 * @param nev string containing the name.
 * @param prot Pointer to a module.
 */
prot_module_t::prot_module_t(const char* nev, module_t* prot) {
    this->prot = prot;
    if (nev == NULL) return;
    this->nev = new char[strlen(nev) + 1];
    strcpy_s(this->nev, strlen(nev) + 1, nev);
}
/**
 * Destructor for the prot_module_t class.
 */
prot_module_t::~prot_module_t(){
    delete prot;
    delete[] nev;
}
