#ifndef TESTER_H
#define TESTER_H
#include "comp_module.h"
#include "text_module.h"
#include "karakter_keszlet.h"
#include "memtrace.h"
class tester_t {
private:
    bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg) const;
    void ujmnevEll(const char* nev) const;
    void kisbetujo(const char* str) const;
    void kisbetujo2(const char* str) const;
    void nagybetujo(const char* str) const;
    void modulesteszt(const char* str) const;
protected:
    lista<prot_module_t*> modulok;
    std::istream& inStream;
    std::ostream& outStream;
    void testModule(const char* str, bool add = true);
public:
    tester_t(std::istream& in, std::ostream& out) :inStream(in), outStream(out) {}
    ~tester_t() {
        modulok.din();
    }
};
#endif
