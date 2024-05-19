#include "ossz.h"
#include "module.h"
#include "memtrace.h"
/**
 * Retrieve the element at Idx i in the lista.
 *
 * @param i the Idx of the element to retrieve
 *
 * @return a reference to the element at Idx i
 */
template<typename T>
T& lista<T>::operator[](size_t i){
    if(this->length()>i)
        return *(this->getin(i));
    throw "over Idxed";
}
/**
 * Retrieve the element at Idx i in the lista.
 *
 * @param i the Idx of the element to retrieve
 *
 * @return a pointer to the element at Idx i
 */
template<typename T>
T* lista<T>::getin(size_t i){
    if(i==0)
        return &elem;
    return next->getin(i-1);
}
/**
 * Add a new element to the linked list.
 *
 * @param ertek the value to be added to the list
 */
template<typename T>
void lista<T>::add(T ertek){
    if(next==nullptr){
        next = new lista<T>();
        elem=ertek;
    }
    else
        next->add(ertek);
}
/**
 * Adds the elements from the given list to the current list.
 *
 * @param addlist the list to be added
 */
template<typename T>
void lista<T>::add(lista<T>& addlist){
    for(size_t i=0;i<addlist.length();i++)
        add(addlist[i]);
}
/**
 * Calculates the length of the lista.
 *
 * @return The length of the lista.
 */
template<typename T>
size_t lista<T>::length(){
    if(next==nullptr)
        return 0;
    return next->length()+1;
}
/**
 * Removes an element at the specified Idx in the lista object.
 *
 * @param i the Idx of the element to be removed
 */
template<typename T>
void lista<T>::rem(size_t i){
    if(length()>i){
        if(i==0){
            lista<T>* n=next;
            elem=n->elem;
            next=n->next;
            n->next=nullptr;
            delete n;
        }
        else
            next->rem(i-1);
    }
    else throw "over Idxed";
}
/**
 * A function that recursively deletes inner elements.
 */
template<typename T>
void lista<T>::din(){//delete inner
    if(next == nullptr)return;
    next->din();
    delete elem;
}
/**
 * A function that recursively deletes inner lists.
 */
template<typename T>
void lista<T>::dinl(){//delete inner list
    if(next == nullptr)return;
    next->dinl();
    delete[] elem;
}
//size_t
template<>
size_t lista<size_t>::length(){
    if(next==nullptr)
        return 0;
    return next->length()+1;
}
template<>
size_t& lista<size_t>::operator[](size_t i){
    if(length()>i)
        return *getin(i);
    throw "over Idxed";
}
template<>
void lista<size_t>::add(size_t ertek) {
    if (next == nullptr){
        next = new lista<size_t>();
        elem=ertek;
    }
    else
        next->add(ertek);
}
//module_t*
template<>
void lista<module_t*>::add(lista<module_t*>& addlist) {
    for (size_t i = 0; i < addlist.length(); i++)
        add(addlist[i]);
}
template<>
void lista<module_t*>::rem(size_t i) {
    if (length() > i) {
        if (i == 0) {
            lista<module_t*>* n = next;
            elem = n->elem;
            next = n->next;
            n->next = nullptr;
            delete n;
        }
        else
            next->rem(i - 1);
    }
    else throw "over Idxed";
}
//port_t*
template<>
size_t lista<port<module_t*>>::length() {
    if (next == nullptr)
        return 0;
    return next->length() + 1;
}
template<>
port<module_t*>& lista<port<module_t*>>::operator[](size_t i) {
    if (length() > i)
        return *getin(i);
    throw "over Idxed";
}
template<>
void lista<port<module_t*>>::add(port<module_t*> ertek) {
    if (next == nullptr){
        next = new lista<port<module_t*>>();
        elem=ertek;
    }
    else
        next->add(ertek);
}
//prot_module_t*
template<>
size_t lista<prot_module_t*>::length(){
    if(next==nullptr)
        return 0;
    return next->length()+1;
}
template<>
prot_module_t*& lista<prot_module_t*>::operator[](size_t i){
    if(length()>i)
        return *getin(i);
    throw "over Idxed";
}
template<>
void lista<prot_module_t*>::add(prot_module_t* ertek) {
    if (next == nullptr){
        next = new lista<prot_module_t*>();
        elem=ertek;
    }
    else
        next->add(ertek);
}
template<>
void lista<prot_module_t*>::din() {//delete inner list
    if (next == nullptr)return;
    next->din();
    delete elem;
}
//char*
template<>
void lista<char*>::add(char* ertek) {
    if (next == nullptr) {
        next = new lista<char*>();
        elem = ertek;
    }
    else
        next->add(ertek);
}
template<>
size_t lista<char*>::length() {
    if (next == nullptr)
        return 0;
    return next->length() + 1;
}
template<>
char*& lista<char*>::operator[](size_t i) {
    if (length() > i)
        return *getin(i);
    throw "over Idxed";
}
template<>
void lista<char*>::dinl() {//delete inner list
    if (next == nullptr)return;
    next->dinl();
    delete[] elem;
}
