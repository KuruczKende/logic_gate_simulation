#include "text_module.h"
/**
 * A function that performs a NOT operation on the inputs.
 *
 * @param a The input value to perform the NOT operation on.
 *
 * @return The result of the NOT operation.
 */
uint8_t mynot(uint8_t a) {
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
uint8_t myand(uint8_t a, uint8_t b) {
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
uint8_t myor(uint8_t a, uint8_t b) {
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
uint8_t myxor(uint8_t a, uint8_t b) {
    if (a == undet || b == undet)return undet;
    return a != b ? high : low;
}
/**
 * Remove a specified number of elements from the given index in the list and update the list accordingly.
 *
 * @param torlendo the number of elements to remove
 * @param index the index from which to start removal
 * @param hely the list containing the indices
 * @param ideiglenes the temporary character array
 * @param hossz the length of the character array
 */
void lepteto(size_t torlendo, size_t index, lista<size_t>& hely, char*& ideiglenes, size_t& hossz) {
    for (size_t k = hely[index]; k < hossz - torlendo; k++)
        ideiglenes[k] = ideiglenes[k + torlendo];
    for (size_t k = index; k < hely.length(); k++)
        hely[k] -= torlendo;
    hossz -= torlendo;
}
/**
 * Function for performing a specific operation based on the input parameters.
 *
 * @param index The index parameter for the operation
 * @param hely the list containing the indices
 * @param ideiglenes the temporary character array
 * @param hossz the length of the character array
 * @param neg Boolean value indicating negation
 * @param ertek the return value
 * @param iertek the index of the return value to be placed
 *
 * @return True if the task is successfully performed, false otherwise
 */
bool muvs(size_t index, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, uint8_t& ertek, size_t& iertek) {
    size_t findex = hely[index] + (size_t)(neg ? 1 : 0);
    switch (ideiglenes[findex]) {
    case '&':
        ertek = myand(ideiglenes[hely[index] - 1], ideiglenes[findex + 1]);
        break;
    case '|':
        ertek = myor(ideiglenes[hely[index] - 1], ideiglenes[findex + 1]);
        break;
    case '^':
        ertek = myxor(ideiglenes[hely[index] - 1], ideiglenes[findex + 1]);
        break;
    default:
        return false;
    }
    iertek = hely[index] - 1;
    lepteto(neg ? 3 : 2, index, hely, ideiglenes, hossz);
    if (neg)ertek = mynot(ertek);
    return true;
}
/**
 * Constructor for text_module_t class that initializes the variables based on the input command string.
 *
 * @param parancsok The command string used to initialize the text_module_t object
 */
text_module_t::text_module_t(const char* parancsok) {
    ki_db = 1;
    be_db = 0;
    int idx = -1;
    this->parancsok = new char[strlen(parancsok) + 1];
    strcpy(this->parancsok, parancsok);
    while (parancsok[++idx] != '\0') {
        if (parancsok[idx] == ',')
            ki_db++;
        if (parancsok[idx] <= 'z' && (size_t)parancsok[idx] > be_db)
            be_db = parancsok[idx];
    }
    if (idx == 0)//nincs parancs
        ki_db = 0;
    if (be_db >= 'a')//van input
        be_db -= 'a' - 1;
    else
        be_db = 0;
    ki_ertek = new uint8_t[ki_db];
    for (size_t i = 0; i < ki_db; i++) ki_ertek[i] = undet;
    be_ertek = new uint8_t[be_db];
    for (size_t i = 0; i < be_db; i++) be_ertek[i] = undet;
    be_old = new uint8_t[be_db];
    for (size_t i = 0; i < be_db; i++) be_old[i] = undet;
    ki_wires = new wire_t * [ki_db];
    for (size_t i = 0; i < ki_db; i++) ki_wires[i] = new wire_t();
}
text_module_t::text_module_t(const text_module_t& refe):text_module_t(refe.parancsok) {
}
module_t* text_module_t::copy() {
    return new text_module_t(*this);
}
/**
 * Updates the muv list based on the given character.
 *
 * @param c the current character
 * @param cn the next character
 * @param index the index
 * @param hely the list of locations
 * @param fsag the list of priorities
 * @param moz the number of moves
 * @param fs the current priority value
 * @param maxfsag the maximum priority value in the list
 * @param be_ertek the input values
 */
void muv_list(char& c, char& cn, size_t& index, lista<size_t>& hely, lista<size_t>& fsag, size_t& moz, size_t& fs, size_t& maxfsag, uint8_t*& be_ertek) {
    switch (c) {
    case '~':
        if (cn == '|' || cn == '&' || cn == '^') {
            hely.add(index);
            fsag.add(fs);
            if (fs > maxfsag)maxfsag = fs;
            moz++;
            index++;
        }
        else {//bemenet/const/zarojeles ertek
            hely.add(index);
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
        hely.add(index);
        fsag.add(fs);
        if (fs > maxfsag)maxfsag = fs;
        break;
    default://bemenet/const
        if (c != '0' && c != '1')
            c = be_ertek[c - 'a'];
        break;
    }
    moz++;
    index++;
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
void vegrehajt(size_t& maxfsag, lista<size_t>& hely, lista<size_t>& fsag, char*& ideiglenes, size_t& hossz) {
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
/**
 * Executes the logic for vegrehajtas.
 *
 * @param wait_for_do list of wire_t pointers to wires, waiting to be processed
 */
void text_module_t::vegrehajtas(lista<wire_t*>& wait_for_do) {
    size_t kez = 0, veg = 0;
    for (size_t i = 0; i < ki_db; i++) {
        while (parancsok[veg] != ',' && parancsok[veg] != '\0')veg++;
        bool trigger = true;
        if (parancsok[kez] == '[') {
            trigger = false;
            kez++;
            while (parancsok[kez] != ']'){
                if (be_ertek[parancsok[kez] - 'a'] != be_old[parancsok[kez] - 'a'])
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
            size_t index = 0;
            size_t maxfsag = 0;
            while (moz < veg) {
                ideiglenes[index] = parancsok[moz];
                if(parancsok[moz] == '~' && (parancsok[moz + 1] == '|' || parancsok[moz + 1] == '&' || parancsok[moz + 1] == '^'))ideiglenes[index + 1] = parancsok[moz + 1];
                muv_list(ideiglenes[index], ideiglenes[index + 1], index, hely, fsag, moz, fs, maxfsag, be_ertek);
            }//m�veleti lista befejezve
            vegrehajt(maxfsag, hely, fsag, ideiglenes, hossz);
            if (ideiglenes[0] != ki_ertek[i]) {
                ki_ertek[i] = ideiglenes[0];
                ki_wires[i]->set(ki_ertek[i]);
                wait_for_do.add(ki_wires[i]);
            }
            delete[] ideiglenes;
        }
        veg++;
        kez = veg;
    }
    for (size_t i = 0; i < be_db; i++)
        be_old[i] = be_ertek[i];
}
/**
 * Retrieves a value from the text module inputs at the specified index.
 *
 * @param i index of the value in inputs to retrieve
 *
 * @return the value of inputs at the specified index
 */
uint8_t text_module_t::get_in_ertek(size_t i) {
    return be_ertek[i];
}
/**
 * Sets the value at the specified index in the inputs.
 *
 * @param index the index at which to set the value
 * @param ertek the value to set
 */
void text_module_t::setin(size_t index, uint8_t ertek) {
    if (index >= be_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    be_ertek[index] = ertek;
}
/**
 * Destructor for the text_module_t class. Deletes the dynamically allocated memory.
 */
text_module_t::~text_module_t(){
    delete[] be_ertek;
    delete[] be_old;
    delete[] ki_ertek;
    delete[] parancsok;
    be_ertek = NULL;
    be_old = NULL;
    ki_ertek = NULL;
    parancsok = NULL;
}
