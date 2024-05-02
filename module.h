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
    size_t be_db;
    size_t ki_db;
    uint8_t* be_ertek;
    uint8_t* ki_ertek;
    lista<port<module_t*>>* ki_ports;
public:
    module_t() :be_db(0), ki_db(0), be_ertek(nullptr), ki_ertek(nullptr), ki_ports(nullptr){};
    virtual module_t* copy() = 0;
    virtual void vegrehajtas(lista<module_t*>& wait_for_do) { return; }
    virtual void add_to_list(lista<module_t*>& wait_for_do, size_t be) { wait_for_do.add(this);}
    virtual void set_be(size_t index, uint8_t ertek) { be_ertek[index] = ertek; };
    virtual void set_ki_port(size_t ki_index, module_t* modulep, size_t be_index);
    virtual uint8_t get_ki_ertek(size_t i) { return ki_ertek[i]; }
    virtual size_t get_ki_num() { return ki_db; }
    bool is_be_good(size_t n) { return n == be_db; }
    virtual bool is_ki_good(size_t n) { return n == get_ki_num(); }
    virtual uint8_t testModule(const char* str, size_t& k, size_t& v);
    void print(std::ostream& os, bool kezd = true, bool lezar = true);
    void setInputsTo(uint8_t* inputs, lista<module_t*>& wait_to_do_modules);
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
        delete prot;//ez még valamiért el van baszva
        delete[] nev;
    }
};

#endif
