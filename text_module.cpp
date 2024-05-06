#include "text_module.h"
/**
 * A function that performs a NOT operation on the inputs.
 *
 * @param a The input value to perform the NOT operation on.
 *
 * @return The result of the NOT operation.
 */
uint8_t text_module_t::mynot(uint8_t a) {
    switch (a) {
    case low:return high;
    case high:return low;
    default:return undet;
    }
}
/**
 * Calculates the AND operation between two input values.
 *
 * @param a the first input
 * @param b the second input
 *
 * @return the result of the AND operation between the two inputs
 */
uint8_t text_module_t::myand(uint8_t a, uint8_t b) {
    switch (a + b) {
    case undet + high:return undet;
    case undet + undet:return undet;
    case high + high:return high;
    default:return low;
    }
}
/**
 * Calculates the OR operation between two input values.
 *
 * @param a the first input
 * @param b the second input
 *
 * @return the result of the OR operation between the two inputs
 */
uint8_t text_module_t::myor(uint8_t a, uint8_t b) {
    switch (a + b) {
    case undet + low:return undet;
    case undet + undet:return undet;
    case low + low:return low;
    default:return high;
    }
}
/**
 * Calculates the XOR operation between two input values.
 *
 * @param a the first input
 * @param b the second input
 *
 * @return the result of the XOR operation between the two inputs
 */
uint8_t text_module_t::myxor(uint8_t a, uint8_t b) {
    if (a == undet || b == undet)return undet;
    return a != b ? high : low;
}
/**
 * Remove a specified number of elements from the given Idx in the list and update the list accordingly.
 *
 * @param torlendo the number of elements to remove
 * @param Idx the Idx from which to start removal
 * @param hely the list containing the indices
 * @param ideiglenes the temporary character array
 * @param hossz the length of the character array
 */
void text_module_t::lepteto(size_t torlendo, size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz) {
    for (size_t k = hely[Idx]; k < hossz - torlendo; k++)
        ideiglenes[k] = ideiglenes[k + torlendo];
    for (size_t k = Idx; k < hely.length(); k++)
        hely[k] -= torlendo;
    hossz -= torlendo;
}
/**
 * Function for performing a specific operation based on the input parameters.
 *
 * @param Idx The Idx parameter for the operation
 * @param hely the list containing the indices
 * @param ideiglenes the temporary character array
 * @param hossz the length of the character array
 * @param neg Boolean value indicating negation
 * @param ertek the return value
 * @param iertek the Idx of the return value to be placed
 *
 * @return True if the task is successfully performed, false otherwise
 */
bool text_module_t::muvs(size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, uint8_t& ertek, size_t& iertek) {
    size_t fIdx = hely[Idx] + (size_t)(neg ? 1 : 0);
    switch (ideiglenes[fIdx]) {
    case '&':
        ertek = myand(ideiglenes[hely[Idx] - 1], ideiglenes[fIdx + 1]);
        break;
    case '|':
        ertek = myor(ideiglenes[hely[Idx] - 1], ideiglenes[fIdx + 1]);
        break;
    case '^':
        ertek = myxor(ideiglenes[hely[Idx] - 1], ideiglenes[fIdx + 1]);
        break;
    default:
        return false;
    }
    iertek = hely[Idx] - 1;
    lepteto(neg ? 3 : 2, Idx, hely, ideiglenes, hossz);
    if (neg)ertek = mynot(ertek);
    return true;
}
/**
 * Constructor for text_module_t class that initializes the variables based on the input command string.
 *
 * @param parancsok The command string used to initialize the text_module_t object
 */
text_module_t::text_module_t(const char* parancsok) {
    kiDb = 1;
    beDb = 0;
    int idx = -1;
    this->parancsok = new char[strlen(parancsok) + 1];
    strcpy(this->parancsok, parancsok);
    while (parancsok[++idx] != '\0') {
        if (parancsok[idx] == ',')
            kiDb++;
        if (parancsok[idx] <= 'z' && (size_t)parancsok[idx] > beDb)
            beDb = parancsok[idx];
    }
    if (idx == 0)//nincs parancs
        kiDb = 0;
    if (beDb >= 'a')//van input
        beDb -= 'a' - 1;
    else
        beDb = 0;
    kiErtek = new uint8_t[kiDb];
    for (size_t i = 0; i < kiDb; i++) kiErtek[i] = undet;
    beErtek = new uint8_t[beDb];
    for (size_t i = 0; i < beDb; i++) beErtek[i] = undet;
    beOld = new uint8_t[beDb];
    for (size_t i = 0; i < beDb; i++) beOld[i] = undet;
    kiPorts = new lista<port<module_t*>> [kiDb];
}
text_module_t::text_module_t(const text_module_t& refe):text_module_t(refe.parancsok) {}
module_t* text_module_t::copy() {
    return new text_module_t(*this);
}
/**
 * Updates the muv list based on the given character.
 *
 * @param c the current character
 * @param cn the next character
 * @param Idx the Idx
 * @param hely the list of locations
 * @param fsag the list of priorities
 * @param moz the number of moves
 * @param fs the current priority value
 * @param maxfsag the maximum priority value in the list
 * @param beErtek the input values
 */
void text_module_t::muvList(char& c, char& cn, size_t& Idx, lista<size_t>& hely, lista<size_t>& fsag, size_t& moz, size_t& fs, size_t& maxfsag) {
    switch (c) {
    case '~':
        if (cn == '|' || cn == '&' || cn == '^') {
            hely.add(Idx);
            fsag.add(fs);
            if (fs > maxfsag)maxfsag = fs;
            moz++;
            Idx++;
        }
        else {//bemenet/const/zarojeles ertek
            hely.add(Idx);
            fsag.add(fs + 1);
            if (fs + 1 > maxfsag)maxfsag = fs + 1;
        }
        break;
    case '(':
        fs += 2;
        break;
    case ')':
        fs -= 2;
        break;
    case '|':
    case '&':
    case '^':
        hely.add(Idx);
        fsag.add(fs);
        if (fs > maxfsag)maxfsag = fs;
        break;
    default://bemenet/const
        if (c != '0' && c != '1')
            c = beErtek[c - 'a'];
        break;
    }
    moz++;
    Idx++;
}
/**
 * Executes a series of operations on the input parameters to modify the ideiglenes array and the hely list.
 *
 * @param maxfsag the maximum priority value in the list
 * @param hely the list of locations
 * @param fsag the list of priorities
 * @param ideiglenes the character array to be modified
 * @param hossz the length of ideiglenes
 */
void text_module_t::vegrehajt(size_t& maxfsag, lista<size_t>& hely, lista<size_t>& fsag, char*& ideiglenes, size_t& hossz) {
    for (int j = maxfsag; j >= 0; j--) {
        for (size_t i = 0; i < hely.length(); i++) {
            if ((int)fsag[i] == j) {
                size_t iertek;
                uint8_t ertek;
                if (ideiglenes[hely[i]] == '~') {
                    if (!muvs(i, hely, ideiglenes, hossz, true, ertek, iertek)) {
                        iertek = hely[i];
                        ertek = mynot(ideiglenes[hely[i] + 1]);
                        lepteto(1, i, hely, ideiglenes, hossz);
                    }
                }
                else
                    muvs(i, hely, ideiglenes, hossz, false, ertek, iertek);
                if (iertek > 0 && iertek < hossz)
                    if (ideiglenes[iertek - 1] == '(' && ideiglenes[iertek + 1] == ')') {
                        for (size_t k = i; k < hely.length(); k++)
                            hely[k] -= 2;
                        for (size_t k = iertek; k < hossz - 2; k++)
                            ideiglenes[k] = ideiglenes[k + 2];
                        iertek--;
                    }
                ideiglenes[iertek] = ertek;
            }
        }
    }
}
void text_module_t::setKi(size_t Idx, uint8_t ertek, lista<module_t*>& waitForDo) {
    kiErtek[Idx] = ertek;
    for (size_t i = 0; i < kiPorts[Idx].length(); i++) {
        port<module_t*> p = kiPorts[Idx][i];
        p.modulep->setBe(p.portszam, ertek);
        p.modulep->addToList(waitForDo, p.portszam);
    }
}
/**
 * Executes the logic for vegrehajtas.
 *
 * @param waitForDo list of wire_t pointers to wires, waiting to be processed
 */
void text_module_t::vegrehajtas(lista<module_t*>& waitForDo) {
    size_t kez = 0, veg = 0;
    for (size_t i = 0; i < kiDb; i++) {
        while (parancsok[veg] != ',' && parancsok[veg] != '\0')veg++;
        bool trigger = true;
        if (parancsok[kez] == '[') {
            trigger = false;
            kez++;
            while (parancsok[kez] != ']'){
                if (beErtek[parancsok[kez] - 'a'] != beOld[parancsok[kez] - 'a'])
                    trigger = true;
                kez++;
            }
            kez++;
        }
        if (trigger) {
            size_t hossz = veg - kez;
            char* ideiglenes = new char[hossz];
            lista<size_t> hely;
            lista<size_t> fsag;
            size_t moz = kez;
            size_t fs = 0;
            size_t Idx = 0;
            size_t maxfsag = 0;
            while (moz < veg) {
                ideiglenes[Idx] = parancsok[moz];
                if(parancsok[moz] == '~' && (parancsok[moz + 1] == '|' || parancsok[moz + 1] == '&' || parancsok[moz + 1] == '^'))ideiglenes[Idx + 1] = parancsok[moz + 1];
                muvList(ideiglenes[Idx], ideiglenes[Idx + 1], Idx, hely, fsag, moz, fs, maxfsag);
            }//m�veleti lista befejezve
            vegrehajt(maxfsag, hely, fsag, ideiglenes, hossz);
            if (ideiglenes[0] != kiErtek[i]) {
                setKi(i, ideiglenes[0], waitForDo);
            }
            delete[] ideiglenes;
        }
        veg++;
        kez = veg;
    }
    for (size_t i = 0; i < beDb; i++)
        beOld[i] = beErtek[i];
}
/**
 * Destructor for the text_module_t class. Deletes the dynamically allocated memory.
 */
text_module_t::~text_module_t(){
    delete[] beErtek;
    delete[] beOld;
    delete[] kiErtek;
    delete[] parancsok;
    beErtek = NULL;
    beOld = NULL;
    kiErtek = NULL;
    parancsok = NULL;
}
