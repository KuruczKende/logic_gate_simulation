#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "tester.h"
#include <fstream>

class simulator_t :public tester_t {
    module_t* mMain;
    lista<module_t*> wait_to_do_modules;
    lista<char*> insts;
    uint8_t mode;
    void modulator(uint8_t c);
    template<typename T>
    bool instruct_handler_char_handler(uint8_t* inputs, uint8_t c, T& state, size_t& number);
    char* getstring(std::istream& in, size_t h = 0);
    bool instruct_handler(char* s, size_t& number);
    void input_handler_module(char* s);
    void input_handler_read(char* s);
    void input_handler_write(char* s);
    bool input_handler_do(char* s);
public:
    simulator_t(std::istream& in, std::ostream& out) :tester_t(in, out), mode(0), mMain(nullptr) {}
    void input_handler(std::istream& in);
    bool end() { return ((mode & 0b10000000) == 0b10000000); }
    ~simulator_t();
};
#endif
