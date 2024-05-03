#ifndef MODULE_H
#define MODULE_H
#include "ossz.h"

template<typename T>
struct port
{
    T modulep;
    size_t portszam;
};

class module_t {
protected:
    size_t beDb;
    size_t kiDb;
    uint8_t* beErtek;
    uint8_t* kiErtek;
    lista<port<module_t*>>* kiPorts;
public:
    module_t() :beDb(0), kiDb(0), beErtek(nullptr), kiErtek(nullptr), kiPorts(nullptr){};
    virtual module_t* copy() = 0;
    virtual void vegrehajtas(lista<module_t*>& waitForDo) { return; }
    virtual void addToList(lista<module_t*>& waitForDo, size_t be) { waitForDo.add(this);}
    virtual void setBe(size_t Idx, uint8_t ertek) { beErtek[Idx] = ertek; };
    virtual void setKiPort(size_t kiIdx, module_t* modulep, size_t beIdx);
    virtual uint8_t getKiErtek(size_t i) { return kiErtek[i]; }
    virtual size_t getKiNum() { return kiDb; }
    virtual uint8_t testModule(const char* str, size_t& k, size_t& v);
    void print(std::ostream& os, bool kezd = true, bool lezar = true);
    void setInputsTo(uint8_t* inputs, lista<module_t*>& waitToDoModules);
    virtual ~module_t();
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
        strcpy_s(this->nev, strlen(nev) + 1, nev);
    }
    ~prot_module_t() {
        delete prot;//ez m�g valami�rt el van baszva
        delete[] nev;
    }
};

#endif
