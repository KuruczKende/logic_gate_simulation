// nharamkor_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <sstream>
#include "memtrace.h"
#include "simulator.h"
#include "gtest_lite.h"

//#define IS_TEST

#ifdef IS_TEST
/**
 * Main function... That's all.
 */
int main()
{
    simulator_t* sim=new simulator_t(std::cin,std::cout);
    while (!sim->end()) {
        sim->inputHandler(std::cin);
    }
    delete sim;
    return 0;
}
#else
/**
 * Test function... That's all.
 */
int main()
{
    std::ostringstream oss;
    for (uint32_t i = 0; i < 1023; i++) {
        std::istringstream iss("_and:a&b\n_xor:a^b\n_main:_and(ab,d)_xor(ab,c)\nAB2+\naB2+\nA2-\n");
        simulator_t* sim = new simulator_t(iss, std::cout);
        /*TEST("modul", "text_module"); {
            EXPECT_STREQ("", oss.str().c_str());
        } END; */
        sim->inputHandler(iss);
        sim->inputHandler(iss);
        sim->inputHandler(iss);
        sim->inputHandler(iss);
        sim->inputHandler(iss);
        sim->inputHandler(iss);
        delete sim;
    }
    std::cout << "faszom kivan";
    return 0;
}
#endif
//