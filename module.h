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
    virtual void add_to_list(lista<module_t*>& wait_for_do, size_t be) { wait_for_do.add(this); }
    virtual void set_be(size_t index, uint8_t ertek) { be_ertek[index] = ertek; };
    virtual void set_ki_port(size_t ki_index, module_t* modulep, size_t be_index);
    virtual size_t get_ki_num() { return ki_db; }
    virtual uint8_t get_ki_ertek(size_t i) { return ki_ertek[i]; }
    size_t get_be_num() { return be_db; }
    uint8_t get_be_ertek(size_t i) { return be_ertek[i]; }
    virtual ~module_t();
};

template<>
struct port<module_t*>
{
    module_t* modulep;
    size_t portszam;
};
#endif
