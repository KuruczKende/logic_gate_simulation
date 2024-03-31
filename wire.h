#ifndef WIRE_H
#define WIRE_H
#include "ossz.h"
class wire_t {
    uint8_t ertek;
    lista<port_t*> ports;
public:
    wire_t();
    void add(port_t* newport);
    void add(module_t* modulep, size_t idx);
    void set(uint8_t ertek);
    void setin();
    uint8_t get();
    void doit(lista<module_t*>& wait_for_do);
};
#endif