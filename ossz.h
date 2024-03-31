#ifndef OSSZ_H
#define OSSZ_H

#include <iostream>
#include <cstring>

#define low '0'
#define high '1'
#define undet '?'

template<typename T>
class lista{
    T elem;
    lista* next=NULL;
    T* getin(size_t i);
public:
    lista():next(NULL){}
    T& operator[](size_t i);
    void add(T ertek);
    void add(lista<T>& addlist);
    size_t length();
    void rem(size_t i);
    ~lista(){
        delete next;
    }
};
class wire_t;
class module_t;
class text_module_t;
class shell_module_t;
class comp_module_t;
class port_t;
class prot_module_t;

bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg);
#endif
