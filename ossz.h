#ifndef OSSZ_H
#define OSSZ_H

#include <iostream>
#include <cstring>
#include "memtrace.h"

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
    void din();
    void dinl();
    ~lista(){
        delete next;
    }
};
#endif
