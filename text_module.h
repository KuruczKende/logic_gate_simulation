#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H
#include "module.h"
class text_module_t : public module_t {
    uint8_t* beOld;
    char* instuctions;
    void setKi(size_t Idx, uint8_t ertek, lista<module_t*>& waitForDo);
    uint8_t mynot(uint8_t a);
    uint8_t myand(uint8_t a, uint8_t b);
    uint8_t myor(uint8_t a, uint8_t b);
    uint8_t myxor(uint8_t a, uint8_t b);
    void lepteto(size_t torlendo, size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz);
    bool muvs(size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, uint8_t& ertek, size_t& iertek);
    void muvList(char& c, char& cn, size_t& Idx, lista<size_t>& hely, lista<size_t>& fsag, size_t& moz, size_t& fs, size_t& maxfsag);
    void vegrehajt(size_t& maxfsag, lista<size_t>& hely, lista<size_t>& fsag, char*& ideiglenes, size_t& hossz);
public:
    text_module_t(const char* instuctions);
    text_module_t(const text_module_t& refe);
    module_t* copy() override;
    void vegrehajtas(lista<module_t*>& waitForDo) override;
    ~text_module_t();
};
#endif
