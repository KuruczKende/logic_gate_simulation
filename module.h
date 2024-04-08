#ifndef MODULE_H
#define MODULE_H
#include "ossz.h"
#include "wire.h"
class module_t {
protected:
    size_t be_db;
    size_t ki_db;
    wire_t** ki_wires;
public:
    module_t() :be_db(0), ki_db(0), ki_wires(NULL) {};
    virtual module_t* copy() = 0;
    virtual void vegrehajtas(lista<wire_t*>& wait_for_do) {};
    virtual void setin(size_t index, uint8_t ertek) = 0;
    virtual void set_wire(size_t index, wire_t* wire, bool del);
    virtual bool tri_mods(lista<module_t*>& wait_for_do, size_t idx) { return true; };
    virtual size_t get_out_num() { return ki_db; }
    virtual uint8_t get_out_ertek(size_t i) { return ki_wires[i]->get(); }
    virtual uint8_t get_in_ertek(size_t i) = 0;
    size_t get_in_num() { return be_db; }
    virtual ~module_t();
};
#endif
