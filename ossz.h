#ifndef OSSZ_H
#define OSSZ_H

#include <iostream>
#include <cstring>
#include "memtrace.h"

#define low '0'
#define high '1'
#define undet '?'

class trilean{
    uint8_t v;
public:
    trilean(uint8_t v=undet) :v(v) {}
    trilean operator|(const trilean& b)  const {
        switch (v + uint8_t(b)) {
        case undet + low:
        case undet + undet:return trilean(undet);
        case low + low:return trilean(low);
        default:return trilean(high);
        }
    }
    trilean operator&(const trilean& b)  const {
        switch (v + uint8_t(b)) {
        case undet + high:
        case undet + undet:return trilean(undet);
        case high + high:return trilean(high);
        default:return trilean(low);
        }
    }
    trilean operator^(const trilean& b)  const {
        if ((v == undet )|| (uint8_t(b) == undet))return trilean(undet);
        return trilean((v != uint8_t(b)) ? high : low);
    }
    trilean operator!()  const {
        switch (v) {
        case low:return trilean(high);
        case high:return trilean(low);
        default:return trilean(undet);
        }
    }
    operator uint8_t& () {
        return v;
    }
    operator uint8_t () const {
        return v;
    }
};

template<typename T>
class lista{
    T elem;
    lista* next=nullptr;
    T* getin(size_t i);
public:
    lista():next(nullptr){}
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
