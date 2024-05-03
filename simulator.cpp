#include "simulator.h"

/**
 * Modifies the given mods variable based on the input character.
 *
 * @param c the character input to determine the modification
 * @param mods the variable to be modified based on the input character
 */
void simulator_t::modulator(uint8_t c) {
    switch (c) {
    case '%':
        mode |= 0b00000010;
        break;
    case '-':
        mode &= 0b11111110;
        break;
    case '+':
        mode |= 0b00000001;
        break;
    case '!':
        mode |= 0b10000000;
        break;
    }
}

/**
 * A template function to handle different types of input characters and modify state accordingly.
 *
 * @param inputs pointer to an array of uint8_t to store inputs
 * @param c the input character to handle
 * @param state a reference to a template type T representing the current state
 * @param mods a reference to a uint8_t to store modifiers
 * @param number a reference to a size_t to store a number
 *
 * @return true if the input character is processed successfully, false otherwise
 */
template<typename T>
bool simulator_t::instructHandlerCharHandler(uint8_t* inputs, uint8_t c, T& state, size_t& number) {
    enum { input, num, mod };
    if (isalpha(c) && state == (T)input) {
        if (isupper(c))
            inputs[c - 'A'] = '1';
        if (islower(c))
            inputs[c - 'a'] = '0';
        return true;
    }
    else if (isdigit(c) && (state == (T)input || state == (T)num)) {
        state = (T)num;
        number *= 10;
        number += c - '0';
        return true;
    }
    else if (ismod(c) && (state == (T)input || state == (T)num || state == (T)mod)) {
        state = (T)mod;
        modulator(c);
        return true;
    }
    return false;
}

/**
 * A function to handle instructions.
 *
 * @param s the instruction string
 * @param w_inputs an array of wire_t inputs
 * @param waitToDo_wires a list of wire_t pointers to wires, waiting to be processed
 * @param mods a uint8_t representing modifications
 * @param number a size_t representing a number
 *
 * @return true if the function execution is successful, false otherwise
 */
bool simulator_t::instructHandler(char* s, size_t& number) {
    enum { input, num, mod }state = input;
    uint8_t inputs[26];
    for (size_t i = 0; i < 26; i++)
        inputs[i] = '?';
    number = 0;
    for (size_t i = 0; i < strlen(s); i++)
        if (!instructHandlerCharHandler(inputs, s[i], state, number))return false;
    if (mMain != nullptr) {
        mMain->setInputsTo(inputs, waitToDoModules);
    }
    return true;
}
/**
 * Recursively reads characters from the input stream and stores them in a dynamically allocated char array.
 *
 * @param in the input stream to read from
 * @param h the current size of the char array being built
 *
 * @return a dynamically allocated char array containing the characters read from the input stream
 */
char* simulator_t::getstring(std::istream& in, size_t h) {
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

/**
 * Handles input for new module and sets the main module if the module is "_main".
 *
 * @param s input string
 * @param w_inputs array of wire inputs
 * @param modulok list of modules
 * @param mMain pointer to the main module
 */
void simulator_t::inputHandlerModule(char* s) {
    if (printModuleError(testModule(s))) {
        if (strcmp(modulok[modulok.length() - 1]->nev, "_main") == 0) {
            outStream << "main setted\n";
            mMain = modulok[modulok.length() - 1]->prot->copy();
        }
    }
}
/**
 * A function to handle reading file, processing it.
 *
 * @param s the input file name
 * @param w_inputs array of wire inputs
 * @param waitToDo_wires list of wire_t pointers to wires, waiting to be processed
 * @param mods a uint8_t representing modifications
 * @param modulok list of modules
 * @param mMain pointer to the main module
 * @param insts list of instructions
 */
void simulator_t::inputHandlerRead(char* s) {
    std::ifstream inf(&(s[1]));
    if (inf.fail()) {
        inf.clear(); return;
    }
    outStream << "sikeres megnyitas\n";
    while (!inf.eof()) {
        inputHandler(inf);
    }
    inf.close();
}
/**
 * A function to handle writing instructions to file if the user wants.
 *
 * @param s the output file name
 * @param insts list of instructions
 */
void simulator_t::inputHandlerWrite(char* s) {
    std::ofstream outf(&(s[1]));
    if (outf.fail()) {
        outf.clear(); return;
    }
    outStream << "sikeres megnyitas\n";
    for (size_t i = 0; i < insts.length(); i++) {
        if (insts[i][0] != '>') {
            outStream << insts[i] << "\nI/N: ";
            char c;
            inStream >> c;
            if (c == 'I')
                outf << insts[i] << '\n';
        }
    }
    outf.close();
}
/**
 * A function that handles input based on the given parameters.
 *
 * @param s the input character array
 * @param w_inputs array of wire inputs
 * @param waitToDo_wires list of wire_t pointers to wires, waiting to be processed
 * @param mods  a uint8_t representing modifications
 * @param mMain pointer to the main module
 *
 * @return true if input handling is successful, false otherwise
 */
bool simulator_t::inputHandlerDo(char* s) {
    size_t number;
    bool addmain = false;
    if (!instructHandler(s, number))return false;
    if ((mode & 0b00000010) == 0b00000010) {
        mode &= 0b11111101;
        //console clear
    }
    for (size_t i = 0; i < number; i++) {
        lista<module_t*> waitToDoModules2;
        while (waitToDoModules.length() > 0) {
            waitToDoModules[0]->vegrehajtas(waitToDoModules2);
            waitToDoModules.rem(0);
        }
        waitToDoModules.add(waitToDoModules2);
        if ((mode & 0b00000001) == 0b00000001 && mMain != nullptr)
            mMain->print(outStream, i == 0, i == number - 1);
    }
    if ((mode & 0b00000001) != 0b00000001 && number != 0 && mMain != nullptr)
        mMain->print(outStream);
    return true;
}

/**
 * Handles input from the given input stream and performs various operations based on the input.
 *
 * @param in the input stream to read from
 * @param w_inputs array of wire inputs
 * @param waitToDo_wires list of wire_t pointers to wires, waiting to be processed
 * @param mods uint8_t representing modifications
 * @param modulok list of prot_module_t pointers representing modules
 * @param mMain pointer to the main module
 * @param insts list of instructions
 */
void simulator_t::inputHandler(std::istream& in) {
    if (end()) return;
    char* s = getstring(in);
    if (s[0] == '\0') { delete[] s; return; }
    insts.add(s);
    if (s[0] == '_') {//új module
        inputHandlerModule(s);
    }
    else if (s[0] == '<') {//fájlból olvasás
        inputHandlerRead(s);
    }
    else if (s[0] == '>') {//fájlba írás
        inputHandlerWrite(s);
    }
    else {//végrehajtás
        if (!inputHandlerDo(s))outStream << "rossz vegrehajtas utasitas\n";
    }
}
simulator_t::~simulator_t() {
    insts.dinl();
    delete mMain;
}
