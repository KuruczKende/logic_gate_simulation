// nharamkor_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <sstream>
#include "memtrace.h"
#include "simulator.h"
#include "gtest_lite.h"

#define IS_TEST

#ifndef IS_TEST
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
    TEST(modul, errors) {
        std::istringstream iss("_anda&b\n_&nd:a&b\n_and:a&c\n_and:ab\n_and:A&b\n_and:a&b\n_and:a&b\n_and2:_an(ab,c)\n_and2:_and(ab,c)_and(ab,c)\n_and2:_and(ac,b)\n_and2:_and(abc,d)\n_and2:_and(ab,cd)\n");
        simulator_t sim(iss, oss);
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("nincs : jel\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("rossz karakter a nevben\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("nem jo bekotes text_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("nem jo forma text_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("rossz karakterek a text_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("", oss.str().c_str());
        sim.inputHandler(iss);
        EXPECT_STREQ("mar foglalt nev\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("nemletezo module comp_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("masodik kivezetes comp_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("nem jo bekotes comp_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("rossz inputszam comp_module-ban\n", oss.str().c_str());
        oss.str("");
        sim.inputHandler(iss);
        EXPECT_STREQ("rossz outputszam comp_module-ban\n", oss.str().c_str());
        oss.str("");
    } END;
    std::istringstream issAnd("_main:a&b\nAb2+\nB3\n");
    simulator_t simAnd(issAnd, oss);
    TEST(and, create); {
        simAnd.inputHandler(issAnd);
        EXPECT_STREQ("main setted\n", oss.str().c_str());
        oss.str("");
    } END;
    TEST(and, test); {
        simAnd.inputHandler(issAnd);
        char exp[] = {  (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '0', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp, oss.str().c_str());
        oss.str("");
        simAnd.inputHandler(issAnd);
        char exp2[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '1', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '1', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp2, oss.str().c_str());
        oss.str("");
    } END;
    std::istringstream issHalfAdder("_main:a^b,a&b\nAb2+\nB3\n");
    simulator_t simHalfAdder(issHalfAdder, oss);
    TEST(halfAdder, create); {
        simHalfAdder.inputHandler(issHalfAdder);
        EXPECT_STREQ("main setted\n", oss.str().c_str());
        oss.str("");
    } END;
    TEST(halfAdder, test); {
        simHalfAdder.inputHandler(issHalfAdder);
        char exp[] = {  (char)218, (char)196, (char)196, (char)194, (char)196, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', 'd', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '1', '0', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '1', '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp, oss.str().c_str());
        oss.str("");
        simHalfAdder.inputHandler(issHalfAdder);
        char exp2[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', 'd', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '0', '1', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '0', '1', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '0', '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp2, oss.str().c_str());
        oss.str("");
    } END;
    std::istringstream issFullAdder("_and:a&b\n_xor:a^b\n_halfAdder:_and(ab,d)_xor(ab,c)\n_main:_halfAdder(ab,AB)_halfAdder(Ac,dC)_xor(BC,e)\nAbc2+\nB3\n");
    simulator_t simFullAdder(issFullAdder, oss);
    TEST(fullAdder, create); {
        simFullAdder.inputHandler(issFullAdder);
        simFullAdder.inputHandler(issFullAdder);
        simFullAdder.inputHandler(issFullAdder);
        simFullAdder.inputHandler(issFullAdder);
        EXPECT_STREQ("main setted\n", oss.str().c_str());
        oss.str("");
    } END;
    TEST(fullAdder, test); {
        simFullAdder.inputHandler(issFullAdder);
        char exp[] = {  (char)218, (char)196, (char)196, (char)196, (char)194, (char)196, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', 'c', (char)179, 'd', 'e', (char)179, '\n',
                        (char)179, '1', '0', '0', (char)179, '1', '?', (char)179, '\n',
                        (char)179, '1', '0', '0', (char)179, '1', '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)196, (char)193, (char)196, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp, oss.str().c_str());
        oss.str("");
        simFullAdder.inputHandler(issFullAdder);
        char exp2[] = { (char)218, (char)196, (char)196, (char)196, (char)194, (char)196, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', 'c', (char)179, 'd', 'e', (char)179, '\n',
                        (char)179, '1', '1', '0', (char)179, '1', '0', (char)179, '\n',
                        (char)179, '1', '1', '0', (char)179, '0', '1', (char)179, '\n',
                        (char)179, '1', '1', '0', (char)179, '0', '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)196, (char)193, (char)196, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp2, oss.str().c_str());
        oss.str("");
    } END;
    std::istringstream issTrigg("_main:[b]a\nA2-\nB3\na1\nb1\nB1\nA1\na1\nA2\nb1\n");
    simulator_t simTrigg(issTrigg, oss);
    TEST(trigger, create); {
        simTrigg.inputHandler(issTrigg);
        EXPECT_STREQ("main setted\n", oss.str().c_str());
        oss.str("");
    } END;
    TEST(trigger, test); {
        simTrigg.inputHandler(issTrigg);
        char exp[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '?', (char)179, '?', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp2[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp2, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp3[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '0', '1', (char)179, '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp3, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp4[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '0', '0', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp4, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp5[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '0', '1', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp5, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp6[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp6, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp7[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '0', '1', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp7, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp8[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '1', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp8, oss.str().c_str());
        oss.str("");
        simTrigg.inputHandler(issTrigg);
        char exp9[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '1', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        EXPECT_STREQ(exp9, oss.str().c_str());
        oss.str("");
    } END;
    TEST(file, write); {
        std::istringstream issFileOut("_and:a&b\n_main:_and(ab,c)\nAb2+\n>file.txt\nI\nI\nI\n");
        simulator_t simFileOut(issFileOut, oss);
        simFileOut.inputHandler(issFileOut);
        simFileOut.inputHandler(issFileOut);
        simFileOut.inputHandler(issFileOut);
        oss.str("");
        simFileOut.inputHandler(issFileOut);
        EXPECT_STREQ("sikeres megnyitas\n_and:a&b\nI/N: _main:_and(ab,c)\nI/N: Ab2+\nI/N: sikeres mentes\n", oss.str().c_str());
        oss.str("");
        std::ifstream f("file.txt");
        std::stringstream fs;
        fs << f.rdbuf();
        EXPECT_STREQ("_and:a&b\n_main:_and(ab,c)\nAb2+\n", fs.str().c_str());
        f.close();
    } END;
    TEST(file, read); {
        std::istringstream issFileIn("<file.txt\n");
        simulator_t simFileIn(issFileIn, oss);
        simFileIn.inputHandler(issFileIn);
        std::stringstream fs;
        char exp[] = { (char)218, (char)196, (char)196, (char)194, (char)196, (char)191, '\n',
                        (char)179, 'a', 'b', (char)179, 'c', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '0', (char)179, '\n',
                        (char)179, '1', '0', (char)179, '0', (char)179, '\n',
                        (char)192, (char)196, (char)196, (char)193, (char)196, (char)217, '\n', '\0' };
        fs << "sikeres megnyitas\nmain setted\n" << exp;
        EXPECT_STREQ( fs.str().c_str() , oss.str().c_str());
    } END;
    return 0;
}
#endif