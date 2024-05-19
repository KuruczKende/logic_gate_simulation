#ifndef TESTER_H
#define TESTER_H
#include "comp_module.h"
#include "text_module.h"
#include "karakter_keszlet.h"
#include "memtrace.h"
class tester_t {
protected:
    lista<prot_module_t*> modulok;
    std::istream& inStream;
    std::ostream& outStream;
    bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg);
    bool ismod(char c);
    uint8_t ujmnevEll(const char* nev);
    uint8_t kisbetujo(const char* str);
    uint8_t kisbetujo2(const char* str);
    uint8_t nagybetujo(const char* str);
    uint8_t modulesteszt(const char* str);
    void testModule(const char* str, bool add = true);
public:
    tester_t(std::istream& in, std::ostream& out) :inStream(in), outStream(out) {}
    ~tester_t() {
        modulok.din();
    }
};
#endif
