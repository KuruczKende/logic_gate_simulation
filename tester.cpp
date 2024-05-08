#include "tester.h"

/**
 * Checks if a substring of str matches str2 within the specified range.
 *
 * @param str pointer to the string to be checked
 * @param str2 pointer to the string to compare against
 * @param kez starting index of the substring to compare
 * @param veg ending index of the substring to compare (exclusive)
 *
 * @return true if the substring matches, false otherwise
 */
bool tester_t::eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}

/**
 * Checks if a given character is a modifier character.
 *
 * @param c The character to be checked.
 *
 * @return True if the character is '%', '-', '+', or '!', false otherwise.
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
 * Checks if the given name meets certain criteria.
 *
 * @param nev The name to be checked.
 *
 * @return 1 if the name doesn't start with '_', 2 if it contains invalid characters, 3 if it's already in use, 0 if the name is valid.
 */
uint8_t tester_t::ujmnevEll(const char* nev) {
    if (nev[0] != '_') return 1;//nincs _
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[(size_t)(nev[i])]) return 2;// rossz karakterek
    for (size_t i = 0; i < modulok.length(); i++)
        if (strcmp(nev, modulok[i]->nev) == 0) return 3;//m�r foglalt
    return 0;
}

/**
 * Checks if a given string is a valid input.
 *
 * @param str The string to be checked.
 *
 * @return 0 if the string is valid, 1 if the characters are not in use, 2 if it has an invalid format, 3 if it contains an invalid character other than '(' or ')'.
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
 * Checks if a given string is a valid input for a comp_module_t
 *
 * @param str The string to be checked.
 *
 * @return Returns 0 if the string is valid, 1 if there is a second output use, 2 if there are non-adjacent inputs, or 3 if the string has an invalid format.
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
            if (outp && ob[str[i] - 'a']) return 1;//m�sodik kivezet�s
            (outp ? ob : ib)[str[i] - 'a'] = true;
        }
    }
    int j = 0;
    while (ib[j] && j++ < 26);
    while (ob[j] && j < 26)if (ib[j++]) return 2;//nem j� bek�t�sek
    while (j < 26)if (ib[j] || ob[j++]) return 2;//nem j� bek�t�sek
    return 0;
}

/**
 * Checks if a given string is a valid input for a comp_module_t.
 *
 * @param str The string to be checked.
 *
 * @return Returns 0 if the string is valid, 1 if there is a second output use, 2 if there are non-adjacent inputs, or 3 if the string has an invalid format.
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
            if (outp && ob[str[i] - 'A']) return 1;//m�sodik kivezet�s
            (outp ? ob : ib)[str[i] - 'A'] = true;
        }
    }
    size_t j = 0;
    while (ob[j]) {
        if (ob[j] != ib[j])return 2;//nem j� bek�t�sek
        j++;
    }
    while (j < 26) {
        if (ob[j] || ib[j])return 2;//nem j� bek�t�sek
        j++;
    }
    return 0;
}

/**
 * Tests the modules in the given string.
 *
 * @param str the string containing the modules to be tested
 *
 * @return 0 if all modules were tested successfully, 1 if a non-existing module was found,
 *         or the error code of the first module that failed the test plus 1.
 */
uint8_t tester_t::modulesteszt(const char* str) {
    size_t k = 0, v = 0;
    while (k < strlen(str)) {
        while (str[v] != '(' && v < strlen(str)) v++;
        int j = -1;
        for (size_t i = 0; i < modulok.length(); i++)
            if (eggyezik(modulok[i]->nev, str, k, v)) j = i;
        if (j == -1) return 1;//neml�tez� modul
        uint8_t moduleRet = modulok[j]->prot->testModule(str,k,v);
        if (moduleRet > 0) return moduleRet + 1;
    }
    return 0;
}

/**
 * A description of the entire C++ function.
 *
 * @param str the string containing the modules to be tested
 * @param add a boolean flag indicating whether to add a module
 *
 * @throws 1 int if ':' is not found in the input string
 * @throws 2 int if the module name is incorrect
 * @throws 3 int if any of the subfunctions fail
 */
void tester_t::testModule(const char* str, bool add) {
    char* nev = new char[strlen(str) + 1];
    char* instuctions = nev;
    strcpy(nev, str);
    while (*instuctions != ':' && *instuctions != '\0') instuctions++;
    if (*instuctions == '\0') {
        delete[] nev; throw 1 ;//nincs :
    }
    *instuctions = '\0';
    instuctions++;
    uint8_t un = ujmnevEll(nev);
    if (un != 0) { delete[] nev; throw un + 1; }// rossz n�v
    if (instuctions[0] == '_') {//comp_module
        uint8_t kb = kisbetujo2(instuctions), nb = nagybetujo(instuctions), mt = modulesteszt(instuctions);
        if (kb != 0) { delete[] nev; throw kb + 4; }
        if (nb != 0) { delete[] nev; throw nb + 4; }
        if (mt != 0) { delete[] nev; throw mt + 6; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new comp_module_t(instuctions, modulok)));
        delete[] nev;
    }
    else {//text_module
        uint8_t kb = kisbetujo(instuctions);
        if (kb != 0) { delete[] nev; throw kb + 9; }
        if (add) modulok.add(new prot_module_t(nev, (module_t*) new text_module_t(instuctions)));
        delete[] nev;
    }
}