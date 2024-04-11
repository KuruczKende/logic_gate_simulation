#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H
#include "module.h"
class text_module_t : public module_t {
    uint8_t* be_old;
    char* parancsok;
public:
    text_module_t(const char* parancsok);
    text_module_t(const text_module_t& refe);
    module_t* copy() override;
    void vegrehajtas(lista<module_t*>& wait_for_do) override;
    void set_ki(size_t index, uint8_t ertek, lista<module_t*>& wait_for_do);
    ~text_module_t();
};
#endif
