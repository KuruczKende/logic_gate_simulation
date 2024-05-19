#include "tester.h"
#include "memtrace.h"
/**
 * Checks if a substring of str matches str2 within the specified range.
 *
 * @param str pointer to the string to be checked
 * @param str2 pointer to the string to compare against
 * @param kez starting index of the substring to compare
 * @param veg ending index of the substring to compare (exclusive)
 */
bool tester_t::eggyezik(const char* str, const char* str2, size_t kez, size_t veg) const {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}
/**
 * Checks if the given name meets certain criteria.
 *
 * @param nev The name to be checked.
 */
void tester_t::ujmnevEll(const char* nev) const {
    if (nev[0] != '_') { delete[] nev; throw "nem _ val kezdodo nev\n"; }//nem fog bekövetkezni
    for (size_t i = 0; i < strlen(nev); i++)
        if (!kk[(size_t)(nev[i])]) throw "rossz karakter a nevben\n";// rossz karakterek
    for (size_t i = 0; i < modulok.length(); i++)
        if (strcmp(nev, modulok[i]->nev) == 0) throw "mar foglalt nev\n";//m�r foglalt
}
/**
 * Checks if a given string is a valid input.
 *
 * @param str The string to be checked.
 */
void tester_t::kisbetujo(const char* str) const {
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
            if (notch) throw "nem jo forma text_module-ban\n";//hibas forma
            ertek = false;
            notch = true;
        }
        else if (str[i] == '&' || str[i] == '|' || str[i] == '^' || str[i] == ',') {
            if (!(ertek || notch)) throw "nem jo forma text_module-ban\n";//hibas forma
            ertek = false;
            notch = false;
        }
        else if (islower(str[i]) || str[i] == '0' || str[i] == '1') {
            if (ertek) throw "nem jo forma text_module-ban\n";//hibas forma
            ertek = true;
            notch = false;
            if (islower(str[i])) b[str[i] - 'a'] = true;
        }
        else if (str[i] == '(') {
            ertek = false;
            notch = false;
        }
        else if (str[i] == ')') {
            ertek = true;
            notch = false;
        }
        else
            throw "rossz karakterek a text_module-ban\n";
    }
    int j = 0;
    while (b[j++]);
    while (j < 26) if (b[j++]) throw "nem jo bekotes text_module-ban\n";
}
/**
 * Checks if a given string is a valid input for a comp_module_t
 *
 * @param str The string to be checked.
 */
void tester_t::kisbetujo2(const char* str) const {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false; }
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (islower(str[i]) && port) {
            if (outp && ob[str[i] - 'a']) throw "masodik kivezetes comp_module-ban\n";//m�sodik kivezet�s
            (outp ? ob : ib)[str[i] - 'a'] = true;
        }
    }
    int j = 0;
    while (ib[j] && j++ < 26);
    while (ob[j] && j < 26)if (ib[j++]) throw "nem jo bekotes comp_module-ban\n";//nem j� bek�t�sek
    while (j < 26)if (ib[j] || ob[j++]) throw "nem jo bekotes comp_module-ban\n";//nem j� bek�t�sek
}
/**
 * Checks if a given string is a valid input for a comp_module_t.
 *
 * @param str The string to be checked.
 */
void  tester_t::nagybetujo(const char* str) const {
    bool ib[26]{ false };
    bool ob[26]{ false };
    bool outp = false;
    bool port = false;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { port = true; outp = false; }
        else if (str[i] == ')') port = false;
        else if (str[i] == ',') outp = true;
        else if (isupper(str[i]) && port) {
            if (outp && ob[str[i] - 'A']) throw "masodik kivezetes comp_module-ban\n";//m�sodik kivezet�s
            (outp ? ob : ib)[str[i] - 'A'] = true;
        }
    }
    size_t j = 0;
    while (ob[j]) {
        if (ob[j] != ib[j]) throw "nem jo bekotes comp_module-ban\n";//nem j� bek�t�sek
        j++;
    }
    while (j < 26) {
        if (ob[j] || ib[j]) throw "nem jo bekotes comp_module-ban\n";//nem j� bek�t�sek
        j++;
    }
}
/**
 * Tests the modules in the given string.
 *
 * @param str the string containing the modules to be tested
 */
void tester_t::modulesteszt(const char* str) const {
    size_t k = 0, v = 0;
    while (k < strlen(str)) {
        while (str[v] != '(' && v < strlen(str)) v++;
        int j = -1;
        for (size_t i = 0; i < modulok.length(); i++)
            if (eggyezik(modulok[i]->nev, str, k, v)) j = i;
        if (j == -1) throw "nemletezo module comp_module-ban\n";//neml�tez� modul
        modulok[j]->prot->testModule(str,k,v);
    }
}
/**
 * A description of the entire C++ function.
 *
 * @param str the string containing the modules to be tested
 * @param add a boolean flag indicating whether to add a module
 */
void tester_t::testModule(const char* str, bool add) {
    char* nev = new char[strlen(str) + 1];
    char* instuctions = nev;
    strcpy(nev, str);
    try{
        while (*instuctions != ':' && *instuctions != '\0') instuctions++;
        if (*instuctions == '\0') {
            throw "nincs : jel\n";//nincs :
        }
        *instuctions = '\0';
        instuctions++;
        ujmnevEll(nev);
        if (instuctions[0] == '_') {//comp_module
            kisbetujo2(instuctions);
            nagybetujo(instuctions);
            modulesteszt(instuctions);
            if (add) modulok.add(new prot_module_t(nev, (module_t*) new comp_module_t(instuctions, modulok)));
            delete[] nev;
        }
        else {//text_module
            kisbetujo(instuctions);
            if (add) modulok.add(new prot_module_t(nev, (module_t*) new text_module_t(instuctions)));
            delete[] nev;
        }
    }
    catch (const char* err) {
        delete[] nev;
        throw err;
    }
}