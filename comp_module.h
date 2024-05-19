#ifndef COMP_MODULE_H
#define COMP_MODULE_H
#include "shell_module.h"
#include "memtrace.h"
class comp_module_t : public shell_module_t {
    shell_module_t endModule;
    module_t** modules;
    size_t mDb;
    char* modulesComs;
    void muvCount(lista<size_t>& vegk, lista<size_t>& kezk);
    void setConnection(char c, module_t*& base, size_t kiIdx);
    void compCreateModules(bool copy, lista<size_t>& vegk, lista<size_t>& kezk, lista<prot_module_t*>* protModules, module_t**& moduleRef);
    void compFillModule(lista<size_t>& vegk);
    bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg);
public:
    comp_module_t(char* modulesComs, lista<prot_module_t*>& protModules);
    comp_module_t(size_t beDb, size_t kiDb, size_t mDb);
    module_t* copy() override;
    void setKiPort(size_t kiIdx, module_t* modulep, size_t beIdx) {endModule.setKiPort(kiIdx, modulep, beIdx);}
    trilean getKiErtek(size_t i) {return endModule.getKiErtek(i);}
    size_t getKiNum() {return endModule.getKiNum();}
    ~comp_module_t();
};
#endif
