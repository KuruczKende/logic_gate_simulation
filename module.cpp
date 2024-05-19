#include "module.h"
#include "memtrace.h"
/**
 * Sets the KiPort of the module.
 *
 * @param kiIdx The index of the KiPort.
 * @param modulep A pointer to the module.
 * @param beIdx The index of the BePort.
 */
void module_t::setKiPort(size_t kiIdx, module_t* modulep, size_t beIdx) {
    if (kiIdx >= kiDb)throw "over Idxed";
    if (kiIdx < 0)throw "under Idxed";
    if (beIdx >= modulep->beDb)throw "over Idxed";
    if (beIdx < 0)throw "under Idxed";
    kiPorts[kiIdx].add(port<module_t*>{modulep, beIdx});
}
/**
 * Tests the module input and output numbers.
 *
 * @param str The input string.
 * @param k The reference to the index of the input string.
 * @param v The reference to the index of the input string.
 */
void module_t::testModule(const char* str, size_t& k, size_t& v) const{
    size_t out = this->getKiNum();
    v = k = v + 1;
    while (str[v] != ',' && v < k + beDb) v++;
    if (str[v] != ',' || v != k + beDb) throw "rossz inputszam comp_module-ban\n";//rossz inputsz�m
    v = k = v + 1;
    while (str[v] != ')' && v < k + out) v++;
    if (str[v] != ')' || v != k + out) throw "rossz outputszam comp_module-ban\n";//rossz outputsz�m
    v = k = v + 1;
}
/**
 * Prints the contents of the module to the console in a formatted manner.
 *
 * @param os ostream written to
 * @param kezd flag indicating whether to include the beginning formatting
 * @param lezar flag indicating whether to include the ending formatting
 */
void module_t::print( std::ostream& os, bool kezd, bool lezar) const {
    size_t out = getKiNum();
    if (kezd) {
        os << (char)218;
        for (size_t i = 0; i < beDb; i++)os << (char)196;
        os << (char)194;
        for (size_t i = 0; i < out; i++)os << (char)196;
        os << (char)191 << '\n' << (char)179;
        for (size_t j = 0; j < out + beDb; j++) {
            if (j == beDb)os << (char)179;
            os << (char)(j + 'a');
        }
        os << (char)179 << '\n';
    }
    os << (char)179;
    for (size_t j = 0; j < beDb; j++)os << (char)beErtek[j];
    os << (char)179;
    for (size_t j = 0; j < out; j++)os << (char)getKiErtek(j);
    os << (char)179 << '\n';
    if (lezar) {
        os << (char)192;
        for (size_t i = 0; i < beDb; i++)os << (char)196;
        os << (char)193;
        for (size_t i = 0; i < out; i++)os << (char)196;
        os << (char)217 << '\n';
    }
}
/**
 * Sets the inputs of the module based on the provided array and updates the waitToDoModules list accordingly.
 *
 * @param inputs pointer to an array of input values
 * @param waitToDoModules list of modules to be updated
 */
void module_t::setInputsTo(trilean* inputs, lista<module_t*>& waitToDoModules) {
    for (size_t i = 0; i < beDb; i++)
        if (inputs[i] != undet)
            if (inputs[i] != beErtek[i]) {
                setBe(i, inputs[i]);
                addToList(waitToDoModules, i);
            }
}
/**
 * Destructor for the module_t class. Deletes all the output wires in the module.
 */
module_t::~module_t(){
    delete[] beErtek;
    if(kiErtek!=beErtek) delete[] kiErtek;
    delete[] kiPorts;
}
