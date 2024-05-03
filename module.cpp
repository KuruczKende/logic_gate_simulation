#include "module.h"

void module_t::setKiPort(size_t kiIdx, module_t* modulep, size_t beIdx) {
    if (kiIdx >= kiDb)throw "over Idxed";
    if (kiIdx < 0)throw "under Idxed";
    if (beIdx >= modulep->beDb)throw "over Idxed";
    if (beIdx < 0)throw "under Idxed";
    kiPorts[kiIdx].add(port<module_t*>{modulep, beIdx});
}

uint8_t module_t::testModule(const char* str, size_t& k, size_t& v){
    size_t out = this->getKiNum();
    v = k = v + 1;
    while (str[v] != ',' && v < k + beDb) v++;
    if (str[v] != ',' || v != k + beDb) return 1;//rossz inputszám
    v = k = v + 1;
    while (str[v] != ')' && v < k + out) v++;
    if (str[v] != ')' || v != k + out) return 2;//rossz outputszám
    v = k = v + 1;
    return 0;
}

/**
 * Prints the contents of the module to the console in a formatted manner.
 *
 * @param mMain a pointer to the module to be printed
 * @param kezd flag indicating whether to include the beginning formatting
 * @param lezar flag indicating whether to include the ending formatting
 */
void module_t::print( std::ostream& os, bool kezd, bool lezar) {
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

void module_t::setInputsTo(uint8_t* inputs, lista<module_t*>& waitToDoModules) {
    for (size_t i = 0; i < beDb; i++)
        if (inputs[i] != '?')
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
