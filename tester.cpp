#include "tester.h"

bool tester_t::eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}
/**
 * Check if the character is a special symbol.
 *
 * @param c the character to be checked
 *
 * @return true if the character is '%', '-', '+', or '!', false otherwise
 */
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

/**
 * Check if the given name meets certain criteria and is not already in use.
 *
 * @param nev The name to be checked
 * @param modules A list of modules to compare the name against
 *
 * @return 0 if the name is valid and not in use, 1 if the name not starts with '_', 2 if the name contains invalid characters, 3 if the name is already in use
 */
uint8_t tester_t::ujmnevEll(const char* nev) {
    if (nev[0] != '_') return 1;//nincs _
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[(size_t)(nev[i])]) return 2;// rossz karakterek
    for (size_t i = 0; i < modulok.length(); i++)
        if (strcmp(nev, modulok[i]->nev) == 0) return 3;//már foglalt
    return 0;
}

/**
 * Checks if the input string contains at least one of each lowercase letter up to the "biggest" letter in use. And not contains syntactic error.
 *
 * @param str pointer to the input string
 *
 * @return 2 if wrong format, 1 if wrong character usage, 0 if it's valid
 */
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

/**
 * Checks if the input string contains at least one of each lowercase letter up to the "biggest" letter in use and after a specific character every letter used as output.
 *
 * @param str pointer to the input string
 *
 * @return 1 if a letter used as an output more than once, 2 if it's not valid, 0 if it's valid
 */
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

/**
 * A function that checks the wiring connections of uppercase letters in the input string.
 *
 * @param str a pointer to the input string to be checked
 *
 * @return 0 if the wiring connections are correct, 1 if a letter used as an output more than once, 2 if there are incorrect wiring connections
 */
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

/**
 * Function to check and validate modules based on input string.
 *
 * @param str The input string to check against modules.
 * @param modules A list of modules to compare against the input string.
 *
 * @return 0 if successful, 1 if module does not exist, 2 if wrong input number, 3 if wrong output number.
 */
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

/**
 * Function to test a module with the given name and commands.
 *
 * @param str the name and commands of the module to be tested
 * @param modulok a list of module pointers to be tested against
 * @param add flag to indicate whether to add the module
 *
 * @return 0 if successful, error code otherwise
 */
uint8_t tester_t::testModule(const char* str, bool add) {
    char* nev = new char[strlen(str) + 1];
    char* parancsok = nev;
    strcpy_s(nev, strlen(str) + 1, str);
    while (*parancsok != ':' && *parancsok != '\0') parancsok++;
    if (*parancsok == '\0') {
        delete[] nev; return 1;//nincs :
    }
    *parancsok = '\0';
    parancsok++;
    uint8_t un = ujmnevEll(nev);
    if (un != 0) { delete[] nev; return un + 1; }// rossz név
    if (parancsok[0] == '_') {//comp_module
        uint8_t kb = kisbetujo2(parancsok), nb = nagybetujo(parancsok), mt = modulesteszt(parancsok);
        if (kb != 0) { delete[] nev; return kb + 4; }
        if (nb != 0) { delete[] nev; return nb + 4; }
        if (mt != 0) { delete[] nev; return mt + 6; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new comp_module_t(parancsok, modulok)));
        delete[] nev; return 0;
    }
    else {//text_module
        uint8_t kb = kisbetujo(parancsok);
        if (kb != 0) { delete[] nev; return kb + 9; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new text_module_t(parancsok)));
        delete[] nev; return 0;
    }
}

/**
 * A function that prints error messages based on the error code passed in.
 *
 * @param err the error code to determine which error message to print
 *
 * @return true if error code is 0, false otherwise
 */
bool tester_t::printModuleError(uint8_t err) {
    switch (err)
    {
    case 0:  return true;
    case 1:  outStream << "nincs : jel\n"; return false;
    case 2:  outStream << "nem _ val kezdodo nev\n"; return false;
    case 3:  outStream << "rossz karakter a nevben\n"; return false;
    case 4:  outStream << "mar foglalt nev\n"; return false;
    case 5:  outStream << "masodik kivezetes comp_module-ban\n"; return false;
    case 6:  outStream << "nem jo bekotes comp_module-ban\n"; return false;
    case 7:  outStream << "nemletezo module comp_module-ban\n"; return false;
    case 8:  outStream << "rossz inputszam comp_module-ban\n"; return false;
    case 9:  outStream << "rossz outputszam comp_module-ban\n"; return false;
    case 10: outStream << "nem jo bekotes text_module-ban\n"; return false;
    case 11: outStream << "nem jo forma text_module-ban\n"; return false;
    case 12: outStream << "rossz karakterek a text_module-ban\n"; return false;
    default: outStream << "unhandlered error\n"; return false;
    }
}