#ifndef SHELL_MODULE_H
#define SHELL_MODULE_H
#include "module.h"
class shell_module_t : public module_t {
public:
    shell_module_t(size_t ports = 0);
    void init(size_t ports);
    module_t* copy() override;
    void setBe(size_t Idx, trilean ertek) override;
    void addToList(lista<module_t*>& waitForDo, size_t be) override;
    virtual ~shell_module_t();
};
#endif
