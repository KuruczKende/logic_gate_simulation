#include "ossz.h"
#include "prot_modules.h"
template<typename T>
T& lista<T>::operator[](size_t i){
    if(0>i)throw "under indexed";
    if(this->length()>i)
        return *(this->getin(i));
    throw "over indexed";
}
template<typename T>
T* lista<T>::getin(size_t i){
    if(i==0)
        return &elem;
    return next->getin(i-1);
}
template<typename T>
void lista<T>::add(T ertek){
    if(next==NULL){
        next = new lista();
        elem=ertek;
    }
    else
        next->add(ertek);
}
template<typename T>
void lista<T>::add(lista<T>& addlist){
    for(size_t i=0;i<addlist.length();i++)
        add(addlist[i]);
}
template<typename T>
size_t lista<T>::length(){
    if(next==NULL)
        return 0;
    return next->length()+1;
}
template<typename T>
void lista<T>::rem(size_t i){
    if(0>i)throw "under indexed";
    if(length()>i){
        if(i==0){
            lista<T>* n=next;
            elem=n->elem;
            next=n->next;
            n->next=NULL;
            delete n;
        }
        else
            next->rem(i-1);
    }
    else throw "over indexed";
}

template<>
size_t lista<size_t>::length(){
    if(next==NULL)
        return 0;
    return next->length()+1;
}
template<>
size_t& lista<size_t>::operator[](size_t i){
    if(0>i)throw "under indexed";
    if(length()>i)
        return *getin(i);
    throw "over indexed";
}

template<>
void lista<size_t>::add(size_t ertek) {
    if (next == NULL){
        next = new lista();
        elem=ertek;
    }
    else
        next->add(ertek);
}
template<>
void lista<size_t>::rem(size_t i){
    if(0>i)throw "under indexed";
    if(length()>i){
        if(i==0){
            lista<size_t>* n=next;
            elem=n->elem;
            next=n->next;
            n->next=NULL;
            delete n;
        }
        else
            next->rem(i-1);
    }
    else throw "over indexed";
}

template<>
size_t lista<port_t*>::length() {
    if (next == NULL)
        return 0;
    return next->length() + 1;
}
template<>
port_t*& lista<port_t*>::operator[](size_t i) {
    if (0 > i)throw "under indexed";
    if (length() > i)
        return *getin(i);
    throw "over indexed";
}

template<>
void lista<port_t*>::add(port_t* ertek) {
    if (next == NULL){
        next = new lista();
        elem=ertek;
    }
    else
        next->add(ertek);
}
template<>
void lista<port_t*>::add(lista<port_t*>& addlist) {
    for (size_t i = 0; i < addlist.length(); i++)
        add(addlist[i]);
}

template<>
void lista<module_t*>::add(module_t* ertek) {
    if (next == NULL){
        next = new lista();
        elem=ertek;
    }
    else
        next->add(ertek);
}
template<>
void lista<module_t*>::add(lista<module_t*>& addlist) {
    for (size_t i = 0; i < addlist.length(); i++)
        add(addlist[i]);
}
template<>
void lista<module_t*>::rem(size_t i) {
    if (0 > i)throw "under indexed";
    if (length() > i) {
        if (i == 0) {
            lista<module_t*>* n = next;
            elem = n->elem;
            next = n->next;
            n->next = NULL;
            delete n;
        }
        else
            next->rem(i - 1);
    }
    else throw "over indexed";
}


template<>
size_t lista<wire_t*>::length() {
    if (next == NULL)
        return 0;
    return next->length() + 1;
}
template<>
wire_t*& lista<wire_t*>::operator[](size_t i) {
    if (0 > i)throw "under indexed";
    if (length() > i)
        return *getin(i);
    throw "over indexed";
}
template<>
void lista<wire_t*>::add(wire_t* ertek) {
    if (next == NULL) {
        next = new lista();
        elem = ertek;
    }
    else
        next->add(ertek);
}
template<>
void lista<wire_t*>::add(lista<wire_t*>& addlist) {
    for (size_t i = 0; i < addlist.length(); i++)
        add(addlist[i]);
}
template<>
void lista<wire_t*>::rem(size_t i) {
    if (0 > i)throw "under indexed";
    if (length() > i) {
        if (i == 0) {
            lista<wire_t*>* n = next;
            elem = n->elem;
            next = n->next;
            n->next = NULL;
            delete n;
        }
        else
            next->rem(i - 1);
    }
    else throw "over indexed";
}


template<>
size_t lista<prot_module_t>::length(){
    if(next==NULL)
        return 0;
    return next->length()+1;
}
template<>
prot_module_t& lista<prot_module_t>::operator[](size_t i){
    if(0>i)throw "under indexed";
    if(length()>i)
        return *getin(i);
    throw "over indexed";
}

template<>
void lista<prot_module_t>::add(prot_module_t ertek) {
    if (next == NULL){
        next = new lista();
        elem=ertek;
    }
    else
        next->add(ertek);
}


