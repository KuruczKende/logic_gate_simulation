#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "tester.h"
#include "memtrace.h"
#include <fstream>
class simulator_t :public tester_t {
    module_t* mMain;
    lista<module_t*> waitToDoModules;
    lista<char*> insts;
    uint8_t mode;
    void modulator(char c);
    bool ismod(char c)const;
    template<typename T>
    void instructHandlerCharHandler(trilean* inputs, char c, T& state, size_t& number);
    char* getstring(std::istream& in, size_t h = 0) const;
    void instructHandler(char* s, size_t& number);
    void inputHandlerModule(char* s);
    void inputHandlerRead(char* s);
    void inputHandlerWrite(char* s);
    void inputHandlerDo(char* s);
    void inputHandler(std::istream& in);
public:
    simulator_t(std::istream& in, std::ostream& out) :tester_t(in, out), mMain(nullptr), mode(0){}
    void operator()();
    bool end() { return ((mode & 0b10000000) == 0b10000000); }
    ~simulator_t();
};
#endif
