#ifndef MODULE_H
#define MODULE_H
#include "ossz.h"
#include "memtrace.h"
template<typename T>
struct port
{
    T* modulep;
    size_t portszam;
};
class module_t {
protected:
    size_t beDb;
    size_t kiDb;
    trilean* beErtek;
    trilean* kiErtek;
    lista<port<module_t*>>* kiPorts;
public:
    module_t() :beDb(0), kiDb(0), beErtek(nullptr), kiErtek(nullptr), kiPorts(nullptr){};
    virtual ~module_t();
    virtual module_t* copy() const = 0;
    virtual void setBe(size_t Idx, trilean ertek) { beErtek[Idx] = ertek; };
    virtual void setKiPort(size_t kiIdx, module_t* modulep, size_t beIdx);
    virtual trilean getKiErtek(size_t i) const{ return kiErtek[i]; }
    virtual size_t getKiNum() const{ return kiDb; }
    void testModule(const char* str, size_t& k, size_t& v) const;
    void print(std::ostream& os, bool kezd = true, bool lezar = true) const;
    void setInputsTo(trilean* inputs, lista<module_t*>& waitToDoModules);
    virtual void vegrehajtas(lista<module_t*>& waitForDo) { return; }
    virtual void addToList(lista<module_t*>& waitForDo, size_t be) { waitForDo.add(this);}
};
template<>
struct port<module_t*>
{
    module_t* modulep;
    size_t portszam;
};
struct prot_module_t {
    char* nev;
    module_t* prot;
    prot_module_t(const char* nev = nullptr, module_t* prot = nullptr) :nev(nullptr), prot(prot) {
        if (nev == nullptr) return;
        this->nev = new char[strlen(nev) + 1];
        strcpy(this->nev, nev);
    }
    ~prot_module_t() {
        delete prot;
        delete[] nev;
    }
};
#endif
