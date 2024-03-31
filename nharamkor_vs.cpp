// nharamkor_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "comp_module.h"
#include "text_module.h"
#include "wire.h"
#include "karakter_keszlet.h"

bool ismod(char c) {
    switch (c) {
    case '%':
    case '-':
    case '+':
    case '!':
        return true;
    default: return false;
    }
}
void modulator(uint8_t c, uint8_t& mods) {
    switch (c) {
    case '%':
        mods |= 0b00000010;
        break;
    case '-':
        mods &= 0b11111110;
        break;
    case '+':
        mods |= 0b00000001;
        break;
    case '!':
        mods |= 0b10000000;
        break;
    }
}
bool ujmnev_ell(const char* nev, lista<prot_module_t>& modules) {
    if (nev[0] != '_') return false;
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[nev[i]]) return false;
    for (size_t i = 0; i < modules.length(); i++)
        if (strcmp(nev, modules[i].nev)==0) return false;
    return true;
}

bool kisbetujo(const char* str) {
    bool b[26]{ false };
    for (size_t i = 0; i < strlen(str); i++){
        if (islower(str[i])) b[str[i] - 'a'] = true;
    }
    int j = 0;
    while (b[j++]);
    while (j < 26) if (b[j++]) return false;
    return true;
}
bool kisbetujo2(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false;}
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (islower(str[i])&&port) {
            if (outp && ob[str[i] - 'a']) return false;
            (outp ? ob : ib)[str[i] - 'a'] = true;
        }
    }
    int j = 0;
    while (ib[j] && j++ < 26);
    while (ob[j] && j < 26)if (ib[j++]) return false;
    while (j < 26)if (ib[j] || ob[j++]) return false;
    return true;
}

bool nagybetujo(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false;}
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (isupper(str[i])&&port) {
            if (outp && ob[str[i] - 'A']) return false;
            (outp ? ob : ib)[str[i] - 'A'] = true;
        }
    }
    int j = 0;
    while (ob[j])if (ob[j] != ib[j++]) return false;
    while (j < 26)if (ob[j] || ib[j++]) return false;
    return true;
}

bool karaktercheck(const char* str, bool is_comp){
    bool outp = false;
    for(size_t i=0;i<strlen(str);i++){
        if(str[i] == ',')outp = true;
        else if(islower(str[i]));
        else if(is_comp){
            if(isupper(str[i] || str[i] == ')'));
            else if(str[i] == '(') outp = false;
            else if(outp && str[i] == '-');
            else return false;
        }
        else return false;
    }
    return true;
}

bool modulesteszt(const char* str, lista<prot_module_t>& modules) {
    size_t k = 0, v = 0;
    while (k < strlen(str)) {
        while (str[v] != '(' && v < strlen(str)) v++;
        size_t j = -1;
        for (size_t i = 0; i < modules.length(); i++)
            if (eggyezik(modules[i].nev, str, k, v)) j = i;
        if (j == -1) return false;
        size_t in = modules[j].prot->get_in_num();
        size_t out = modules[j].prot->get_out_num();
        v = k = v + 1;
        while (str[v] != ',' && v < k + in) v++;
        if (str[v] != ',' || v != k + in) return false;
        v = k = v + 1;
        while (str[v] != ')' && v < k + out) v++;
        if (str[v] != ')' || v != k + out) return false;
        v = k = v + 1;
    }
    return true;
}

bool test_module(const char* str, lista<prot_module_t>& modulok, bool add = true) {
    char* nev = new char[strlen(str)+1];
    char* parancsok = nev;
    strcpy(nev, str);
    while (*parancsok != ':' && *parancsok != '\0') parancsok++;
    if (*parancsok == '\0') {
        delete[] nev; return false;
    }
    *parancsok = '\0';
    parancsok++;
    if (!ujmnev_ell(nev, modulok)) {
        delete[] nev; return false;
    }
    if (parancsok[0] == '_') {//comp_module
        if (!kisbetujo2(parancsok)|| !nagybetujo(parancsok)|| !modulesteszt(parancsok, modulok)) {
            delete[] nev; return false;
        }
        if(add) modulok.add(prot_module_t(nev, (module_t*) new comp_module_t(parancsok, modulok)));
        delete[] nev; return true;
    }
    else {//text_module
        if (!kisbetujo(parancsok)) {
            delete[] nev; return false;
        }
        for (size_t i = 0; i < strlen(parancsok)-1; i++) {
            char c = parancsok[i];
            if (!(islower(c) || c == '|' || c == '&' || c == '^' || c == '~' || c == ',' || c == '[' || c == ']' || c == '(' || c == ')')) {
                delete[] nev; return false;
            }
        }
        if (add) modulok.add(prot_module_t(nev, (module_t*) new text_module_t(parancsok)));
        delete[] nev; return true;
    }

}
template<typename T>
void input_handler_char_handler(uint8_t* inputs, uint8_t c, T& state, uint8_t& mods, size_t& number) {
    enum { input, num, mod };
    if (isalpha(c) && state == input) {
        if (isupper(c))
            inputs[c - 'A'] = '1';
        if (islower(c))
            inputs[c - 'a'] = '0';
    }
    else if (isdigit(c) && (state == input || state == num)) {
        state = (T)num;
        number *= 10;
        number += c - '0';
    }
    else if (ismod(c) && (state == input || state == num || state == mod)) {
        state = (T)mod;
        modulator(c, mods);
    }
    else {
        throw "nem jo parancs";
    }
}

void input_handler(std::istream& in, wire_t (&w_inputs)[26], lista<wire_t*>& wait_to_do_wires, uint8_t& mods, size_t& number) {
    enum{input, num, mod}state = input;
    uint8_t inputs[26];
    for (size_t i = 0; i < 26; i++)
        inputs[i] = '?';
    number = 0;
    char c;
    in.get(c);
    while (c != '\n'){
        input_handler_char_handler(inputs, c, state, mods, number);
        in.get(c);
     }
    for (size_t i = 0; i < 26; i++)
        if(inputs[i]!='?')
            if (inputs[i] != w_inputs[i].get()) {
                w_inputs[i].set(inputs[i]);
                wait_to_do_wires.add(&(w_inputs[i]));
            }
}

void printend(module_t& m_main, int i) {
    if(i<0)std::cout << '\n';
    else std::cout << i << '\n';

    for (int j = 0; j < m_main.get_out_num(); j++)
        std::cout << (char)(j + 'a');
    std::cout << '\n';
    for (int j = 0; j < m_main.get_out_num(); j++)
        std::cout << (char)m_main.get_out_ertek(j);
    std::cout << '\n';
}

int main()
{
    lista<prot_module_t> modulok;
    wire_t inputs[26];
    if (!test_module("_xor:a^b", modulok))std::cout << "0";
    if (!test_module("_or:a|b", modulok))std::cout << "0";
    if (!test_module("_andnot:a&~b", modulok))std::cout << "0";
    if (!test_module("_up:[a]a^b", modulok))std::cout << "0";
    if (!test_module("_hadder:a^b,a&b", modulok))std::cout << "0";
    if (!test_module("_dff:[b]a", modulok))std::cout << "0";
    if (!test_module("_sr_in:(c|a)&~b", modulok))std::cout << "0";
    if (!test_module("_sr:_sr_in(abc,c)", modulok))std::cout << "0";
    if (!test_module("_d_in:[b]b&a|(~b&c)", modulok))std::cout << "0";
    if (!test_module("_d:_d_in(abc,c)", modulok))std::cout << "0";
    if (!test_module("_d_r_in:[bc](b&a|(~b&d))&~c", modulok))std::cout << "0";
    if (!test_module("_d_r:_d_r_in(abcd,d)", modulok))std::cout << "0";
    if (!test_module("_d_hadder:_hadder(ad,Ae)_d_r(Abc,d)", modulok))std::cout << "0";
    if (!test_module("_xor_c:_xor(ab,b)", modulok))std::cout << "0";

    if (!test_module("_mux2:(a&~c)|(b&c)", modulok))std::cout << "1";
    if (!test_module("_mux4b2:_mux2(aei,j)_mux2(bfi,k)_mux2(cgi,l)_mux2(dhi,m)", modulok))std::cout << "1";
    if (!test_module("_mux4:(a&~e&~f)|(b&~e&f)|(c&e&~f)|(d&e&f)", modulok))std::cout << "1";
    if (!test_module("_mux4b4:_mux4(aeimqr,s)_mux4(bfjnqr,t)_mux4(cgkoqr,u)_mux4(dhlpqr,v)", modulok))std::cout << "1";

    if (!test_module("_and4:a&e,b&f,c&g,d&h", modulok))std::cout << "1";
    if (!test_module("_or4:a|e,b|f,c|g,d|h", modulok))std::cout << "1";
    if (!test_module("_xor4:a^e,b^f,c^g,d^h", modulok))std::cout << "1";
    if (!test_module("_not4:~a,~b,~c,~d", modulok))std::cout << "1";

    if (!test_module("_alu_log:_and4(abcdefgh,ABCD)_or4(abcdefgh,EFGH)_xor4(abcdefgh,IJKL)_not4(abcd,MNOP)_mux4b4(ABCDEFGHIJKLMNOPij,klmn)", modulok))std::cout << "2";

    if (!test_module("_adder:_hadder(ab,AB)_hadder(Ac,dC)_or(BC,e)", modulok))std::cout << "3";
    if (!test_module("_adder4:_adder(aei,jA)_adder(bfA,kB)_adder(cgB,lC)_adder(dhC,mn)", modulok))std::cout << "3";
    if (!test_module("_suber:a^b^c,b&c|~a&(b^c)", modulok))std::cout << "3";
    if (!test_module("_suber4:_suber(aei,jA)_suber(bfA,kB)_suber(cgB,lC)_suber(dhC,mn)", modulok))std::cout << "3";

    if (!test_module("_alu_alg:_adder4(abcdefghj,ABCDE)_adder4(abcdefghk,FGHIJ)_suber4(abcdefgh0,KLMNO)_mux4b4(ABCDABCDFGHIKLMNij,lmno)_mux4(EEJOij,p)", modulok))std::cout << "4";

    if (!test_module("_alu:_alu_log(abcdefghij,ABCD)_alu_alg(abcdefghijl,EFGHI)_mux4b2(ABCDEFGHk,mnop)_mux2(0Ik,q)", modulok))std::cout << "5";





    if (!test_module("_m_main:_d_hadder(1ab,cA)_d_hadder(Aab,dB)_d_hadder(Bab,eC)_d_hadder(Cab,f-)", modulok))std::cout << "bad_main\n";
    module_t* m_main = modulok[modulok.length() - 1].prot;
    for(size_t i=0;i<m_main->get_in_num();i++)
        inputs[i].add(m_main, i);
    lista<module_t*> wait_to_do_modules;
    lista<wire_t*> wait_to_do_wires;
    uint8_t mode=0;
    size_t number = 0;
    while (!((mode&0b10000000) == 0b10000000)) {
        for (size_t i = 0; i < number; i++) {
            while (wait_to_do_wires.length() > 0) {
                wait_to_do_wires[0]->doit(wait_to_do_modules);
                wait_to_do_wires.rem(0);
            }
            while (wait_to_do_modules.length() > 0) {
                wait_to_do_modules[0]->vegrehajtas(wait_to_do_wires);
                wait_to_do_modules.rem(0);
            }
            if ((mode & 0b00000001) == 0b00000001)
                printend(*m_main, i);
        }
        printend(*m_main, -1);
        input_handler(std::cin, inputs, wait_to_do_wires, mode, number);
        if ((mode & 0b00000010) == 0b00000010) {
            mode &= 0b11111101;
            //console clear
        }
    }
    return 0;
}

/*
* TODO: nem használt kimenetek '-'
* 
* comp_module_t::copy()
* comp_module_t::comp_module_t(char* modules_coms, lista<prot_module_t>& prot_modules)
* text_module_t::vegrehajtas(lista<wire_t*>& wait_for_do)
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
