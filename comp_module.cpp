#include "comp_module.h"
#include "text_module.h"
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
bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}
/**
 * Calculates various counts and values based on the input string.
 *
 * @param modules_coms the character array containing module command
 * @param vegk the list of the starter indexes
 * @param kezk the list of the end indexes
 * @param m_db the calculated number of modules based on characters in modules_coms
 * @param be_db the calculated number of inputs based on characters in modules_coms
 * @param ki_db the calculated number of outputs based on characters in modules_coms
 * @param w_db the calculated number of wires based on characters in modules_coms
 */
void muvcount(char* modules_coms, lista<size_t>& vegk, lista<size_t>& kezk, size_t& m_db, size_t& be_db, size_t& ki_db) {
    m_db = 0;
    bool port = false, outport = false;
    uint8_t max_inner = 'A' - 1, max_in = 'a' - 1, max_out = 'a' - 1, min_out = 'z' + 1;
    kezk.add(0);
    for (size_t i = 0; i < strlen(modules_coms); i++) {
        if (modules_coms[i] == '(') {
            m_db++;
            port = true;
            vegk.add(i);
        }
        else if (modules_coms[i] == ')') {
            port = false;
            outport = false;
            kezk.add(i + 1);
        }
        else if (port) {
            if (modules_coms[i] == ',')
                outport = true;
            else if (!outport && modules_coms[i] > max_in && modules_coms[i] <= 'z')
                max_in = modules_coms[i];
            else if (outport && modules_coms[i] > max_out && modules_coms[i] <= 'z')
                max_out = modules_coms[i];
            else if (modules_coms[i] > max_inner && modules_coms[i] <= 'Z')
                max_inner = modules_coms[i];
            if (outport && modules_coms[i] < min_out && modules_coms[i] >= 'a')
                min_out = modules_coms[i];
        }
    }
    be_db = (min_out - 1 < max_in ? min_out - 1 : max_in) - 'a' + 1;
    ki_db = max_out - 'a' + 1 - be_db;
}
void comp_module_t::set_connection(char c, module_t*& base, size_t ki_index) {
    size_t m_index = 0;
    size_t portszam = 0;
    for (size_t i = 0; i < strlen(modules_coms); i++) {
        while (modules_coms[i] != '(' && i < strlen(modules_coms))i++;
        if (i < strlen(modules_coms)) {
            i++;
            portszam = 0;
            while (modules_coms[i] != ',') {
                if (modules_coms[i] == c) {
                    if (c < be_db + 'a')
                        ki_ports[be_db - 'a'].add(port<module_t*>{modules[m_index], portszam});
                    else
                        base->set_ki_port(ki_index, modules[m_index], portszam);
                }
                i++;
                portszam++;
            }
        }
        m_index++;
    }
}
/**
 * Fills modules based on previous calculations.
 *
 * @param copy if for coping modules
 * @param m_db number of the modules
 * @param be_db number of inputs
 * @param ki_db number of outputs
 * @param w_db number of wires
 * @param modules_coms the character array containing module command
 * @param vegk the list of the starter indexes
 * @param kezk the list of the end indexes
 * @param modules array of modules
 * @param end_module the end module
 * @param ki_wires output wires(inputs)
 * @param wires inner wires
 * @param prot_modules list of modules prototypes
 * @param modules_ref reference to modules
 */
void comp_module_t::comp_fill_module(bool copy, lista<size_t>& vegk, lista<size_t>& kezk, lista<prot_module_t*>* prot_modules, module_t**& modules_ref) {
    for (size_t i = 0; i < m_db; i++) {
        size_t j = 0;
        if (!copy) {
            while (!eggyezik((*prot_modules)[j]->getnev(), modules_coms, kezk[i], vegk[i])) j++;
            modules[i] = (*prot_modules)[j]->getprot()->copy();
        }
        else
            modules[i] = modules_ref[i]->copy();
        j = vegk[i] + 1;
        size_t k = 0;
        while (modules_coms[j] != ',') {
            if (modules_coms[j] == '0' || modules_coms[j] == '1')
                modules[i]->set_be(k++, modules_coms[j++]);
        }
        j++;
        k = 0;
        while (modules_coms[j] != ')') {
            if (modules_coms[j] == '-') {
                k++;
                j++;
            }
            else
                set_connection(modules_coms[j++], modules[i], k++);
        }
    }
}

/**
 * Constructor for the comp_module_t class.
 *
 * @param modules_coms  the character array containing module command
 * @param prot_modules list of modules prototypes
 */
comp_module_t::comp_module_t(char* modules_coms, lista<prot_module_t*>& prot_modules) {
    this->modules_coms = new char[strlen(modules_coms) + 1];
    strcpy_s(this->modules_coms, strlen(modules_coms) + 1, modules_coms);
    size_t ki_db;
    lista<size_t> vegk;
    lista<size_t> kezk;
    muvcount(modules_coms, vegk, kezk, m_db, this->be_db, ki_db);
    this->ki_db = be_db;
    end_module.init(ki_db);
    modules = new module_t * [m_db];
    comp_fill_module(false, vegk, kezk, &prot_modules, modules);
}
/**
 * Constructor for comp_module_t class.
 *
 * @param be_db number of inputs
 * @param ki_db number of outputs
 * @param m_db number of the modules
 * @param w_db number of wires
 */
comp_module_t::comp_module_t(size_t be_db, size_t ki_db, size_t m_db) {
    this->be_db = this->ki_db = be_db;
    this->m_db = m_db;
    end_module.init(ki_db);
    modules = new module_t * [m_db];
}
module_t* comp_module_t::copy() {
    ki_db = get_ki_num();
    comp_module_t* ret = new comp_module_t(be_db, ki_db, m_db);
    ret->modules_coms = new char[strlen(modules_coms) + 1];
    strcpy_s(ret->modules_coms, strlen(modules_coms) + 1, modules_coms);
    lista<size_t> vegk;
    lista<size_t> kezk;
    size_t kuka;
    muvcount(modules_coms, vegk, kezk, kuka, kuka, kuka);
    ret->comp_fill_module(true, vegk, kezk, nullptr, modules);
    ki_db = be_db;
    return ret;
}
/**
 * Destructor for the comp_module_t class, responsible for cleaning up memory and resources.
 */
comp_module_t::~comp_module_t(){
    if (modules != nullptr) {
        for (size_t i = 0; i < m_db; i++) {
            delete modules[i];
        }
        delete[] modules;
    }
    delete[] modules_coms;
}
