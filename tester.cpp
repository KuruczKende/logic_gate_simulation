#include "tester.h"

bool tester_t::eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}

bool tester_t::ismod(char c) {
    switch (c) {
    case '%':
    case '-':
    case '+':
    case '!':
        return true;
    default: return false;
    }
}

uint8_t tester_t::ujmnevEll(const char* nev) {
    if (nev[0] != '_') return 1;//nincs _
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[(size_t)(nev[i])]) return 2;// rossz karakterek
    for (size_t i = 0; i < modulok.length(); i++)
        if (strcmp(nev, modulok[i]->nev) == 0) return 3;//már foglalt
    return 0;
}

uint8_t tester_t::kisbetujo(const char* str) {
    bool b[26]{ false };
    bool ertek = false;
    bool notch = false;
    bool iserz = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '[')iserz = true;
        else if (str[i] == ']')iserz = false;
        else if (iserz) {
            if (islower(str[i])) b[str[i] - 'a'] = true;
        }
        else if (str[i] == '~') {
            if (notch) return 2;//hibas forma
            ertek = false;
            notch = true;
        }
        else if (str[i] == '&' || str[i] == '|' || str[i] == '^' || str[i] == ',') {
            if (!(ertek || notch)) return 2;//hibas forma
            ertek = false;
            notch = false;
        }
        else if (islower(str[i]) || str[i] == '0' || str[i] == '1') {
            if (ertek) return 2;//hibas forma
            ertek = true;
            notch = false;
            if (islower(str[i])) b[str[i] - 'a'] = true;
        }
        else if (str[i] != '(' && str[i] != ')')
            return 3;
    }
    int j = 0;
    while (b[j++]);
    while (j < 26) if (b[j++]) return 1;
    return 0;
}

uint8_t tester_t::kisbetujo2(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false; }
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (islower(str[i]) && port) {
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

uint8_t tester_t::nagybetujo(const char* str) {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false; }
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (isupper(str[i]) && port) {
            if (outp && ob[str[i] - 'A']) return 1;//második kivezetés
            (outp ? ob : ib)[str[i] - 'A'] = true;
        }
    }
    size_t j = 0;
    while (ob[j]) {
        if (ob[j] != ib[j])return 2;//nem jó bekötések
        j++;
    }
    while (j < 26) {
        if (ob[j] || ib[j])return 2;//nem jó bekötések
        j++;
    }
    return 0;
}

uint8_t tester_t::modulesteszt(const char* str) {
    size_t k = 0, v = 0;
    while (k < strlen(str)) {
        while (str[v] != '(' && v < strlen(str)) v++;
        int j = -1;
        for (size_t i = 0; i < modulok.length(); i++)
            if (eggyezik(modulok[i]->nev, str, k, v)) j = i;
        if (j == -1) return 1;//nemlétezõ modul
        uint8_t moduleRet = modulok[j]->prot->testModule(str,k,v);
        if (moduleRet > 0) return moduleRet + 1;
    }
    return 0;
}

void tester_t::testModule(const char* str, bool add) {
    char* nev = new char[strlen(str) + 1];
    char* parancsok = nev;
    strcpy(nev, str);
    while (*parancsok != ':' && *parancsok != '\0') parancsok++;
    if (*parancsok == '\0') {
        delete[] nev; throw 1 ;//nincs :
    }
    *parancsok = '\0';
    parancsok++;
    uint8_t un = ujmnevEll(nev);
    if (un != 0) { delete[] nev; throw un + 1; }// rossz név
    if (parancsok[0] == '_') {//comp_module
        uint8_t kb = kisbetujo2(parancsok), nb = nagybetujo(parancsok), mt = modulesteszt(parancsok);
        if (kb != 0) { delete[] nev; throw kb + 4; }
        if (nb != 0) { delete[] nev; throw nb + 4; }
        if (mt != 0) { delete[] nev; throw mt + 6; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new comp_module_t(parancsok, modulok)));
        delete[] nev;
    }
    else {//text_module
        uint8_t kb = kisbetujo(parancsok);
        if (kb != 0) { delete[] nev; throw kb + 9; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new text_module_t(parancsok)));
        delete[] nev;
    }
}