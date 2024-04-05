// nharamkor_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
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
uint8_t ujmnev_ell(const char* nev, lista<prot_module_t>& modules) {
    if (nev[0] != '_') return 1;//nincs _
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[nev[i]]) return 2;// rossz karakterek
    for (size_t i = 0; i < modules.length(); i++)
        if (strcmp(nev, modules[i].nev)==0) return 3;//már foglalt
    return 0;
}

uint8_t kisbetujo(const char* str) {
    bool b[26]{ false };
    for (size_t i = 0; i < strlen(str); i++){
        if (islower(str[i])) b[str[i] - 'a'] = true;
    }
    int j = 0;
    while (b[j++]);
    while (j < 26) if (b[j++]) return 1;
    return 0;
}
uint8_t kisbetujo2(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false;}
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (islower(str[i])&&port) {
            if (outp && ob[str[i] - 'a']) return 1;//második kivezetés
            (outp ? ob : ib)[str[i] - 'a'] = true;
        }
    }
    int j = 0;
    while (ib[j] && j++ < 26);
    while (ob[j] && j < 26)if (ib[j++]) return 2;//nem jó bekötések
    while (j < 26)if (ib[j] || ob[j++]) return 2;//nem jó bekötések
    return 0;
}

uint8_t nagybetujo(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false;}
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (isupper(str[i])&&port) {
            if (outp && ob[str[i] - 'A']) return 1;//második kivezetés
            (outp ? ob : ib)[str[i] - 'A'] = true;
        }
    }
    int j = 0;
    while (ob[j])if (ob[j] != ib[j++]) return 2;//nem jó bekötések
    while (j < 26)if (ob[j] || ib[j++]) return 2;//nem jó bekötések
    return 0;
}

uint8_t modulesteszt(const char* str, lista<prot_module_t>& modules) {
    size_t k = 0, v = 0;
    while (k < strlen(str)) {
        while (str[v] != '(' && v < strlen(str)) v++;
        size_t j = -1;
        for (size_t i = 0; i < modules.length(); i++)
            if (eggyezik(modules[i].nev, str, k, v)) j = i;
        if (j == -1) return 1;//nemlétező modul
        size_t in = modules[j].prot->get_in_num();
        size_t out = modules[j].prot->get_out_num();
        v = k = v + 1;
        while (str[v] != ',' && v < k + in) v++;
        if (str[v] != ',' || v != k + in) return 2;//rossz inputszám
        v = k = v + 1;
        while (str[v] != ')' && v < k + out) v++;
        if (str[v] != ')' || v != k + out) return 3;//rossz outputszám
        v = k = v + 1;
    }
    return 0;
}

uint8_t test_module(const char* str, lista<prot_module_t>& modulok, bool add = true) {
    char* nev = new char[strlen(str)+1];
    char* parancsok = nev;
    strcpy(nev, str);
    while (*parancsok != ':' && *parancsok != '\0') parancsok++;
    if (*parancsok == '\0') {
        delete[] nev; return 1;//nincs :
    }
    *parancsok = '\0';
    parancsok++;
    uint8_t un = ujmnev_ell(nev, modulok);
    if (un != 0) { delete[] nev; return un + 2; }// rossz név
    if (parancsok[0] == '_') {//comp_module
        uint8_t kb = kisbetujo2(parancsok), nb = nagybetujo(parancsok), mt = modulesteszt(parancsok, modulok);
        if (kb != 0) { delete[] nev; return kb+5; }
        if (nb != 0) { delete[] nev; return nb+5; }
        if (mt != 0) { delete[] nev; return mt+7; }
        if(add) modulok.add(prot_module_t(nev, (module_t*) new comp_module_t(parancsok, modulok)));
        delete[] nev; return 0;
    }
    else {//text_module
        uint8_t kb = kisbetujo(parancsok);
        if (kb != 0) { delete[] nev; return kb; }
        for (size_t i = 0; i < strlen(parancsok)-1; i++) {
            char c = parancsok[i];
            if (!(islower(c) || c == '|' || c == '&' || c == '^' || c == '~' || c == ',' || c == '[' || c == ']' || c == '(' || c == ')')) {
                delete[] nev; return 2;//nem megfelelő karakterek
            }
        }
        if (add) modulok.add(prot_module_t(nev, (module_t*) new text_module_t(parancsok)));
        delete[] nev; return 0;
    }

}
template<typename T>
void instruct_handler_char_handler(uint8_t* inputs, uint8_t c, T& state, uint8_t& mods, size_t& number) {
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

void instruct_handler(char* s, wire_t (&w_inputs)[26], lista<wire_t*>& wait_to_do_wires, uint8_t& mods, size_t& number) {
    enum{input, num, mod}state = input;
    uint8_t inputs[26];
    for (size_t i = 0; i < 26; i++)
        inputs[i] = '?';
    number = 0;
    for(size_t i=0;i<strlen(s);i++)
        instruct_handler_char_handler(inputs, s[i], state, mods, number);
    for (size_t i = 0; i < 26; i++)
        if(inputs[i]!='?')
            if (inputs[i] != w_inputs[i].get()) {
                w_inputs[i].set(inputs[i]);
                wait_to_do_wires.add(&(w_inputs[i]));
            }
}
char* getstring(std::istream& in, size_t h = 0) {
    char c;
    char* ret;
    in.get(c);
    if (in.eof() || c == '\n') {
        ret = new char[h + 1];
        ret[h] = '\0';
    }
    else {
        ret = getstring(in, h + 1);
        ret[h] = c;
    }
    return ret;
}
bool print_module_error(uint8_t err) {
    switch (err)
    {
    case 0:  return true;
    case 1:  std::cout << "nincs : jel\n"; return false;
    case 2:  std::cout << "rossz karakterek a text_module-ban\n"; return false;
    case 3:  std::cout << "nem _ val kezdodo nev\n"; return false;
    case 4:  std::cout << "rossz karakter a nevben\n"; return false;
    case 5:  std::cout << "mar foglalt nev\n"; return false;
    case 6:  std::cout << "masodik kivezetes comp_module-ban\n"; return false;
    case 7:  std::cout << "nem jo bekotes comp_module-ban\n"; return false;
    case 8:  std::cout << "nemletezo module comp_module-ban\n"; return false;
    case 9:  std::cout << "rossz inputszam comp_module-ban\n"; return false;
    case 10: std::cout << "rossz outputszam comp_module-ban\n"; return false;
    default: std::cout << "unhandlered error\n"; return false;
    }
}
void print(module_t*& m_main, bool kezd = true, bool lezar = true) {
    size_t in = m_main->get_in_num();
    size_t out = m_main->get_out_num();
    if (kezd) {
        std::cout << (char)218;
        for(size_t i=0;i<in;i++)std::cout << (char)196;
        std::cout << (char)194;
        for (size_t i = 0; i < out; i++)std::cout << (char)196;
        std::cout << (char)191;
        std::cout << '\n';
        std::cout << (char)179;
        for (size_t j = 0; j < out + in; j++) {
            if (j == in)std::cout << (char)179;
            std::cout << (char)(j + 'a');
        }
        std::cout << (char)179;
        std::cout << '\n';
    }
    std::cout << (char)179;
    for (size_t j = 0; j < in; j++)std::cout << (char)m_main->get_in_ertek(j);
    std::cout << (char)179;
    for (size_t j = 0; j < out; j++)std::cout << (char)m_main->get_out_ertek(j);
    std::cout << (char)179;
    std::cout << '\n';
    if (lezar) {
        std::cout << (char)192;
        for (size_t i = 0; i < in; i++)std::cout << (char)196;
        std::cout << (char)193;
        for (size_t i = 0; i < out; i++)std::cout << (char)196;
        std::cout << (char)217;
        std::cout << '\n';
    }
}

void input_handler(std::istream& in, wire_t(&w_inputs)[26], lista<wire_t*>& wait_to_do_wires, uint8_t& mods, lista<prot_module_t>& modulok, module_t*& m_main, lista<char*>& insts) {
    if ((mods & 0b10000000) == 0b10000000) return;
    char* s = getstring(in);
    if (s[0] == '\0') return;
    insts.add(s);
    if (s[0] == '_') {//új module
        if (print_module_error(test_module(s, modulok))) {
            if (strcmp(modulok[modulok.length() - 1].nev, "_main") == 0) {
                std::cout << "main setted\n";
                m_main = modulok[modulok.length() - 1].prot->copy();
                for (size_t i = 0; i < m_main->get_in_num(); i++)
                    w_inputs[i].add(m_main, i);
            }
        }
    }
    else if (s[0] == '<') {//fájlból olvasás
        std::ifstream inf(&(s[1]));
        if (inf.fail()) {
            inf.clear(); return;
        }
        std::cout << "sikeres megnyias\n";
        while (!inf.eof()) {
            input_handler(inf, w_inputs, wait_to_do_wires, mods, modulok, m_main, insts);
        }
        inf.close();
    }
    else if (s[0] == '>') {//fájlba írás
        std::ofstream outf(&(s[1]));
        if (outf.fail()) {
            outf.clear(); return;
        }
        std::cout << "sikeres megnyias\n";
        for (size_t i = 0; i < insts.length(); i++) {
            if (insts[i][0] != '>') {
                std::cout << insts[i] << "\nI/N: ";
                char c;
                std::cin >> c;
                if (c == 'I')
                    outf << insts[i] << '\n';
            }
        }
        outf.close();
    }
    else {
        size_t number;
        instruct_handler(s, w_inputs, wait_to_do_wires, mods, number);
        if ((mods & 0b00000010) == 0b00000010) {
            mods &= 0b11111101;
            //console clear
        }
        lista<module_t*> wait_to_do_modules;
        for (size_t i = 0; i < number; i++) {
            while (wait_to_do_wires.length() > 0) {
                wait_to_do_wires[0]->doit(wait_to_do_modules);
                wait_to_do_wires.rem(0);
            }
            while (wait_to_do_modules.length() > 0) {
                wait_to_do_modules[0]->vegrehajtas(wait_to_do_wires);
                wait_to_do_modules.rem(0);
            }
            if ((mods & 0b00000001) == 0b00000001)
                print(m_main, i==0,i==number-1);
        }
        if ((mods & 0b00000001) != 0b00000001 && number != 0)
            print(m_main);
    }
}


int main()
{
    lista<prot_module_t> modulok;
    module_t* m_main = NULL;
    wire_t inputs[26];
    lista<wire_t*> wait_to_do_wires;
    lista<char*> insts;
    uint8_t mode=0;
    size_t number = 0;
    while (!((mode&0b10000000) == 0b10000000)) {
        input_handler(std::cin, inputs, wait_to_do_wires, mode, modulok, m_main, insts);
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
