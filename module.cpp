#include "module.h"

void module_t::set_ki_port(size_t ki_index, module_t* modulep, size_t be_index) {
    if (ki_index >= ki_db)throw "over indexed";
    if (ki_index < 0)throw "under indexed";
    if (be_index >= modulep->be_db)throw "over indexed";
    if (be_index < 0)throw "under indexed";
    ki_ports[ki_index].add(port<module_t*>{modulep, be_index});
}

uint8_t module_t::testModule(const char* str, size_t& k, size_t& v){
    size_t out = this->get_ki_num();
    v = k = v + 1;
    while (str[v] != ',' && v < k + be_db) v++;
    if (str[v] != ',' || v != k + be_db) return 1;//rossz inputszám
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
    size_t out = get_ki_num();
    if (kezd) {
        os << (char)218;
        for (size_t i = 0; i < be_db; i++)os << (char)196;
        os << (char)194;
        for (size_t i = 0; i < out; i++)os << (char)196;
        os << (char)191 << '\n' << (char)179;
        for (size_t j = 0; j < out + be_db; j++) {
            if (j == be_db)os << (char)179;
            os << (char)(j + 'a');
        }
        os << (char)179 << '\n';
    }
    os << (char)179;
    for (size_t j = 0; j < be_db; j++)os << (char)be_ertek[j];
    os << (char)179;
    for (size_t j = 0; j < out; j++)os << (char)get_ki_ertek(j);
    os << (char)179 << '\n';
    if (lezar) {
        os << (char)192;
        for (size_t i = 0; i < be_db; i++)os << (char)196;
        os << (char)193;
        for (size_t i = 0; i < out; i++)os << (char)196;
        os << (char)217 << '\n';
    }
}

void module_t::setInputsTo(uint8_t* inputs, lista<module_t*>& wait_to_do_modules) {
    for (size_t i = 0; i < be_db; i++)
        if (inputs[i] != '?')
            if (inputs[i] != be_ertek[i]) {
                set_be(i, inputs[i]);
                add_to_list(wait_to_do_modules, i);
            }
}
/**
 * Destructor for the module_t class. Deletes all the output wires in the module.
 */
module_t::~module_t(){
    delete[] be_ertek;
    if(ki_ertek!=be_ertek) delete[] ki_ertek;
    delete[] ki_ports;
}
