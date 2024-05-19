#include "text_module.h"
#include "memtrace.h"
/**
 * Moves elements in the ideiglenes and hely array based on the given parameters.
 *
 * @param torlendo the number of elements to skip
 * @param Idx the starting index in the hely array
 * @param hely the list of indices
 * @param ideiglenes the array of characters to modify
 * @param hossz the size of the ideiglenes array
 */
void text_module_t::lepteto(size_t torlendo, size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz) {
    for (size_t k = hely[Idx]; k < hossz - torlendo; k++)
        ideiglenes[k] = ideiglenes[k + torlendo];
    for (size_t k = Idx; k < hely.length(); k++)
        hely[k] -= torlendo;
    hossz -= torlendo;
}
/**
 * Moves elements in the ideiglenes array based on the given parameters.
 *
 * @param Idx the index used to calculate fIdx
 * @param hely the list of indices used for calculations
 * @param ideiglenes the array of characters to switch on
 * @param hossz the size of the array
 * @param neg a flag indicating negation
 * @param ertek the result of the operation
 * @param iertek the index position
 *
 * @return true if operation succeeds, false otherwise
 */
bool text_module_t::muvs(size_t Idx, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, trilean& ertek, size_t& iertek) {
    size_t fIdx = hely[Idx] + (size_t)(neg ? 1 : 0);
    switch (ideiglenes[fIdx]) {
    case '&':
        ertek = trilean(ideiglenes[hely[Idx] - 1]) & trilean(ideiglenes[fIdx + 1]);
        break;
    case '|':
        ertek = trilean(ideiglenes[hely[Idx] - 1]) | trilean(ideiglenes[fIdx + 1]);
        break;
    case '^':
        ertek = trilean(ideiglenes[hely[Idx] - 1]) ^ trilean(ideiglenes[fIdx + 1]);
        break;
    default:
        return false;
    }
    iertek = hely[Idx] - 1;
    lepteto(neg ? 3 : 2, Idx, hely, ideiglenes, hossz);
    if (neg)ertek = ~ertek;
    return true;
}
/**
 * Constructor for initializing a text module based on input instructions.
 *
 * @param instuctions The input instructions to initialize the text module.
 */
text_module_t::text_module_t(const char* instuctions) {
    kiDb = 1;
    beDb = 0;
    int idx = -1;
    this->instuctions = new char[strlen(instuctions) + 1];
    strcpy(this->instuctions, instuctions);
    while (instuctions[++idx] != '\0') {
        if (instuctions[idx] == ',')
            kiDb++;
        if (instuctions[idx] <= 'z' && (size_t)instuctions[idx] > beDb)
            beDb = instuctions[idx];
    }
    if (beDb >= 'a')//van input
        beDb -= 'a' - 1;
    else
        beDb = 0;
    kiErtek = new trilean[kiDb];
    for (size_t i = 0; i < kiDb; i++) kiErtek[i] = undet;
    beErtek = new trilean[beDb];
    for (size_t i = 0; i < beDb; i++) beErtek[i] = undet;
    beOld = new trilean[beDb];
    for (size_t i = 0; i < beDb; i++) beOld[i] = undet;
    kiPorts = new lista<port<module_t*>> [kiDb];
}
text_module_t::text_module_t(const text_module_t& refe):text_module_t(refe.instuctions) {}
module_t* text_module_t::copy() const {
    return new text_module_t(*this);
}
/**
 * Updates the given lists and variables based on the character and its neighbor.
 *
 * @param c The current character being processed.
 * @param cn The neighboring character of the current character.
 * @param Idx The current index of the character being processed.
 * @param hely The list of indices where a gate starts.
 * @param fsag The list of gate depths at each index.
 * @param moz The current index of the character being processed.
 * @param fs The current depth of the gate being processed.
 * @param maxfsag The maximum depth of any gate in the list.
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
 * Executes certain operations based on the input parameters.
 *
 * @param maxfsag The maximum gate depth.
 * @param hely List of indices where gates start.
 * @param fsag List of gate depths at each index.
 * @param ideiglenes Temporary character array.
 * @param hossz Length of the character array.
 */
void text_module_t::vegrehajt(size_t& maxfsag, lista<size_t>& hely, lista<size_t>& fsag, char*& ideiglenes, size_t& hossz) {
    for (int j = maxfsag; j >= 0; j--) {
        for (size_t i = 0; i < hely.length(); i++) {
            if ((int)fsag[i] == j) {
                size_t iertek;
                trilean ertek;
                if (ideiglenes[hely[i]] == '~') {
                    if (!muvs(i, hely, ideiglenes, hossz, true, ertek, iertek)) {
                        iertek = hely[i];
                        ertek = ~trilean(ideiglenes[hely[i] + 1]);
                        lepteto(1, i, hely, ideiglenes, hossz);
                    }
                }
                else
                    muvs(i, hely, ideiglenes, hossz, false, ertek, iertek);
                if (iertek > 0 && iertek < hossz)
                    while (ideiglenes[iertek - 1] == '(' && ideiglenes[iertek + 1] == ')') {
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
 * Sets the value of a given input port and updates the corresponding output ports.
 *
 * @param Idx The index of the input port.
 * @param ertek The value to be set for the input port.
 * @param waitForDo A list of module pointers to be updated.
 */
void text_module_t::setKi(size_t Idx, trilean ertek, lista<module_t*>& waitForDo) {
    kiErtek[Idx] = ertek;
    for (size_t i = 0; i < kiPorts[Idx].length(); i++) {
        port<module_t*> p = kiPorts[Idx][i];
        p.modulep->setBe(p.portszam, ertek);
        p.modulep->addToList(waitForDo, p.portszam);
    }
}
/**
 * Executes a series of instructions based on certain triggers and updates the output ports accordingly.
 *
 * @param waitForDo A list of module pointers to be updated after execution.
 */
void text_module_t::vegrehajtas(lista<module_t*>& waitForDo) {
    size_t kez = 0, veg = 0;
    for (size_t i = 0; i < kiDb; i++) {
        while (instuctions[veg] != ',' && instuctions[veg] != '\0')veg++;
        bool trigger = true;
        if (instuctions[kez] == '[') {
            trigger = false;
            kez++;
            while (instuctions[kez] != ']'){
                if (beErtek[instuctions[kez] - 'a'] != beOld[instuctions[kez] - 'a'])
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
                ideiglenes[Idx] = instuctions[moz];
                if(instuctions[moz] == '~' && (instuctions[moz + 1] == '|' || instuctions[moz + 1] == '&' || instuctions[moz + 1] == '^'))ideiglenes[Idx + 1] = instuctions[moz + 1];
                muvList(ideiglenes[Idx], ideiglenes[Idx + 1], Idx, hely, fsag, moz, fs, maxfsag);
            }
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
 * Destructor for the text_module_t class.
 */
text_module_t::~text_module_t(){
    delete[] beErtek;
    delete[] beOld;
    delete[] kiErtek;
    delete[] instuctions;
    beErtek = nullptr;
    beOld = nullptr;
    kiErtek = nullptr;
    instuctions = nullptr;
}
