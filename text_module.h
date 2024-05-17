#ifndef TEXT_MODULE_H
#define TEXT_MODULE_H
#include "module.h"
class text_module_t : public module_t {
    trilean* beOld;
    char* instuctions;
    void setKi(size_t Idx, trilean ertek, lista<module_t*>& waitForDo);
    void lepteto(size_t torlendo, size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz);
    bool muvs(size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, trilean& ertek, size_t& iertek);
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
