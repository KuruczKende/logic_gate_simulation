#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H
#include "module.h"
class text_module_t : public module_t {
    uint8_t* be_ertek;
    uint8_t* be_old;
    uint8_t* ki_ertek;
    char* parancsok;
public:
    text_module_t(const char* parancsok);
    text_module_t(const text_module_t& refe);
    module_t* copy() override;
    void vegrehajtas(lista<wire_t*>& wait_for_do) override;
    uint8_t get_in_ertek(size_t i)override;
    void setin(size_t index, uint8_t ertek) override;
    ~text_module_t();
};
#endif
