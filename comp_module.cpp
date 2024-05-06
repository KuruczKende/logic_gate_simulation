#include "comp_module.h"
#include "text_module.h"
/**
 * Checks if a substring of str matches str2 within the specified range.
 *
 * @param str pointer to the string to be checked
 * @param str2 pointer to the string to compare against
 * @param kez starting Idx of the substring to compare
 * @param veg ending Idx of the substring to compare (exclusive)
 *
 * @return true if the substring matches, false otherwise
 */
bool comp_module_t::eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}
/**
 * Calculates various counts and values based on the input string.
 *
 * @param modulesComs the character array containing module command
 * @param vegk the list of the starter Idxes
 * @param kezk the list of the end Idxes
 * @param mDb the calculated number of modules based on characters in modulesComs
 * @param beDb the calculated number of inputs based on characters in modulesComs
 * @param kiDb the calculated number of outputs based on characters in modulesComs
 * @param wDb the calculated number of wires based on characters in modulesComs
 */
void comp_module_t::muvcount( lista<size_t>& vegk, lista<size_t>& kezk) {
    mDb = 0;
    bool port = false, outport = false;
    uint8_t maxInner = 'A' - 1, maxIn = 'a' - 1, maxOut = 'a' - 1, minOut = 'z' + 1;
    kezk.add(0);
    for (size_t i = 0; i < strlen(modulesComs); i++) {
        if (modulesComs[i] == '(') {
            mDb++;
            port = true;
            vegk.add(i);
        }
        else if (modulesComs[i] == ')') {
            port = false;
            outport = false;
            kezk.add(i + 1);
        }
        else if (port) {
            if (modulesComs[i] == ',')
                outport = true;
            else if (!outport && modulesComs[i] > maxIn && modulesComs[i] <= 'z')
                maxIn = modulesComs[i];
            else if (outport && modulesComs[i] > maxOut && modulesComs[i] <= 'z')
                maxOut = modulesComs[i];
            else if (modulesComs[i] > maxInner && modulesComs[i] <= 'Z')
                maxInner = modulesComs[i];
            if (outport && modulesComs[i] < minOut && modulesComs[i] >= 'a')
                minOut = modulesComs[i];
        }
    }
    beDb = (minOut - 1 < maxIn ? minOut - 1 : maxIn) - 'a' + 1;
    kiDb = maxOut - 'a' + 1 - beDb;
}
void comp_module_t::setConnection(char c, module_t*& base, size_t kiIdx) {
    size_t mIdx = 0;
    size_t portszam = 0;
    for (size_t i = 0; i < strlen(modulesComs); i++) {
        while (modulesComs[i] != '(' && i < strlen(modulesComs))i++;
        if (i < strlen(modulesComs)) {
            i++;
            portszam = 0;
            while (modulesComs[i] != ',') {
                if (modulesComs[i] == c) {
                    base->setKiPort(kiIdx, modules[mIdx], portszam);
                }
                i++;
                portszam++;
            }
        }
        mIdx++;
    }
}
/**
 * Fills modules based on previous calculations.
 *
 * @param copy if for coping modules
 * @param mDb number of the modules
 * @param beDb number of inputs
 * @param kiDb number of outputs
 * @param wDb number of wires
 * @param modulesComs the character array containing module command
 * @param vegk the list of the starter Idxes
 * @param kezk the list of the end Idxes
 * @param modules array of modules
 * @param endModule the end module
 * @param ki_wires output wires(inputs)
 * @param wires inner wires
 * @param protModules list of modules prototypes
 * @param moduleRef reference to modules
 */
void comp_module_t::compCreateModules(bool copy, lista<size_t>& vegk, lista<size_t>& kezk, lista<prot_module_t*>* protModules, module_t**& moduleRef) {
    for (size_t i = 0; i < mDb; i++) {
        if (!copy) {
            size_t j = 0;
            while (!eggyezik((*protModules)[j]->nev, modulesComs, kezk[i], vegk[i])) j++;
            modules[i] = (*protModules)[j]->prot->copy();
        }
        else
            modules[i] = moduleRef[i]->copy();
    }
}
void comp_module_t::compFillModule(lista<size_t>& vegk) {
    for (size_t i = 0; i < mDb; i++) {
        size_t j = vegk[i] + 1;
        size_t k = 0;
        while (modulesComs[j] != ',') {
            if (modulesComs[j] == '0' || modulesComs[j] == '1')
                modules[i]->setBe(k, modulesComs[j]);
            else if (modulesComs[j] >= 'a' && modulesComs[j] < 'a' + (char)beDb)
                kiPorts[modulesComs[j] - 'a'].add(port<module_t*>{modules[i], k});
            k++;j++;
        }
        j++;k = 0;
        while (modulesComs[j] != ')') {
            if (modulesComs[j] == '-') {
                k++;j++;
            }
            else {
                if (modulesComs[j] >= 'a' + (char)beDb)
                    modules[i]->setKiPort(k, &endModule, modulesComs[j] - 'a' - beDb);
                setConnection(modulesComs[j++], modules[i], k++);
            }
        }
    }

}//ezt ketté kell választani elõször minden modult létre kell hozni, majd utána csinálni a bekötéseket

/**
 * Constructor for the comp_module_t class.
 *
 * @param modulesComs  the character array containing module command
 * @param protModules list of modules prototypes
 */
comp_module_t::comp_module_t(char* modulesComs, lista<prot_module_t*>& protModules) {
    this->modulesComs = new char[strlen(modulesComs) + 1];
    strcpy(this->modulesComs, modulesComs);
    size_t kiDab;
    lista<size_t> vegk;
    lista<size_t> kezk;
    muvcount(vegk, kezk);
    kiDab = kiDb;
    beErtek = kiErtek = new uint8_t[beDb];
    for (size_t i = 0; i < beDb; i++) {
        beErtek[i] = '?';
    }
    kiPorts = new lista<port<module_t*>>[beDb];
    endModule.init(kiDab);
    modules = new module_t * [mDb];
    compCreateModules(false, vegk, kezk, &protModules, modules);
    compFillModule(vegk);
    kiDb = beDb;
}
/**
 * Constructor for comp_module_t class.
 *
 * @param beDb number of inputs
 * @param kiDb number of outputs
 * @param mDb number of the modules
 * @param wDb number of wires
 */
comp_module_t::comp_module_t(size_t beDab, size_t kiDab, size_t mDab) {
    this->beDb = this->kiDb = beDab;
    this->mDb = mDab;
    endModule.init(kiDab);
    modules = new module_t * [mDab];
    beErtek = kiErtek = new uint8_t[beDab];
    for (size_t i = 0; i < beDab; i++) {
        beErtek[i] = '?';
    }
    kiPorts = new lista<port<module_t*>>[beDab];
    for (size_t i = 0; i < beDab; i++) {
        kiErtek[i] = '?';
    }
}
module_t* comp_module_t::copy() {
    size_t kiDab = getKiNum();
    comp_module_t* ret = new comp_module_t(beDb, kiDab, mDb);
    ret->modulesComs = new char[strlen(modulesComs) + 1];
    strcpy(ret->modulesComs, modulesComs);
    lista<size_t> vegk;
    lista<size_t> kezk;
    ret->muvcount(vegk, kezk);
    ret->compCreateModules(true, vegk, kezk, nullptr, modules);
    ret->compFillModule(vegk);
    ret->kiDb = ret->beDb;
    return ret;
}
/**
 * Destructor for the comp_module_t class, responsible for cleaning up memory and resources.
 */
comp_module_t::~comp_module_t(){
    if (modules != nullptr) {
        for (size_t i = 0; i < mDb; i++) {
            delete modules[i];
        }
        delete[] modules;
    }
    delete[] modulesComs;
}
