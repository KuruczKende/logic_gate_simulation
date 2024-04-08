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
void muvcount(char* modules_coms, lista<size_t>& vegk, lista<size_t>& kezk, size_t& m_db, size_t& be_db, size_t& ki_db, size_t& w_db) {
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
    if (max_inner >= 'A')
        w_db = max_inner - 'A' + 2 + ki_db;
    else
        w_db = ki_db + 1;
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
void comp_fill_module(bool copy, size_t m_db, size_t be_db, size_t ki_db, size_t w_db, char* modules_coms, lista<size_t>& vegk, lista<size_t>& kezk, module_t**& modules, module_t& end_module, wire_t**& ki_wires, wire_t*& wires, lista<prot_module_t*>* prot_modules, module_t**& modules_ref) {
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
                modules[i]->setin(k++, modules_coms[j++]);
            else if ((size_t)(modules_coms[j] - 'a') < be_db)
                ki_wires[modules_coms[j++] - 'a']->add(modules[i], k++);
            else if ((size_t)(modules_coms[j] - 'a') < be_db + ki_db)
                wires[modules_coms[j++] - 'a' - be_db].add(modules[i], k++);
            else
                wires[modules_coms[j++] - 'A' + ki_db].add(modules[i], k++);
        }
        j++;
        k = 0;
        while (modules_coms[j] != ')') {
            if (modules_coms[j] == '-') {
                modules[i]->set_wire(k++, &(wires[w_db - 1]), true);
                j++;
            }
            else if ((size_t)(modules_coms[j] - 'a') < be_db + ki_db)
                modules[i]->set_wire(k++, &(wires[modules_coms[j++] - 'a' - be_db]), true);
            else
                modules[i]->set_wire(k++, &(wires[modules_coms[j++] - 'A' + ki_db]), true);
        }
    }
    for (size_t i = 0; i < ki_db; i++)
        wires[i].add(&end_module, i);
}

/**
 * Constructor for the comp_module_t class.
 *
 * @param modules_coms  the character array containing module command
 * @param prot_modules list of modules prototypes
 */
comp_module_t::comp_module_t(char* modules_coms, lista<prot_module_t*>& prot_modules) {
    if (this->ki_wires != NULL) {
        for (size_t i = 0; i < this->ki_db; i++)
            delete this->ki_wires[i];
        delete[] this->ki_wires;
        this->ki_wires = NULL;
    }
    this->modules_coms = new char[strlen(modules_coms) + 1];
    strcpy(this->modules_coms, modules_coms);
    size_t ki_db;
    lista<size_t> vegk;
    lista<size_t> kezk;
    muvcount(modules_coms, vegk, kezk, m_db, this->be_db, ki_db, w_db);
    this->ki_db = be_db;
    end_module.init(ki_db);
    ki_wires = new wire_t * [be_db];
    for (size_t i = 0; i < be_db; i++)
        ki_wires[i] = new wire_t();
    modules = new module_t * [m_db];
    wires = new wire_t[w_db];
    comp_fill_module(false, m_db, be_db, ki_db, w_db, modules_coms, vegk, kezk, modules, end_module, ki_wires, wires, &prot_modules, modules);
}
/**
 * Constructor for comp_module_t class.
 *
 * @param be_db number of inputs
 * @param ki_db number of outputs
 * @param m_db number of the modules
 * @param w_db number of wires
 */
comp_module_t::comp_module_t(size_t be_db, size_t ki_db, size_t m_db, size_t w_db) {
    modules_coms = NULL;
    if (this->ki_wires != NULL) {
        for (size_t i = 0; i < this->ki_db; i++)
            delete this->ki_wires[i];
        delete[] this->ki_wires;
        this->ki_wires = NULL;
    }
    this->be_db = this->ki_db = be_db;
    this->m_db = m_db;
    this->w_db = w_db;
    end_module.init(ki_db);
    modules = new module_t * [m_db];
    ki_wires = new wire_t * [be_db];
    for (size_t i = 0; i < be_db; i++)
        ki_wires[i] = new wire_t();
    wires = new wire_t[w_db];
}
module_t* comp_module_t::copy() {
    ki_db = get_out_num();
    comp_module_t* ret = new comp_module_t(be_db, ki_db, m_db, w_db);
    ret->modules_coms = new char[strlen(modules_coms) + 1];
    strcpy(ret->modules_coms, modules_coms);
    lista<size_t> vegk;
    lista<size_t> kezk;
    size_t kuka;
    muvcount(modules_coms, vegk, kezk, kuka, kuka, kuka, kuka);
    comp_fill_module(true, m_db, be_db, ki_db, w_db, modules_coms, vegk, kezk, ret->modules, ret->end_module, ret->ki_wires, ret->wires, NULL, this->modules);
    ki_db = be_db;
    return ret;
}
/**
 * Retrieves the output number of the comp module.
 *
 * @return the value of the output number
 */
size_t comp_module_t::get_out_num() {
    return end_module.get_out_num();
}
/**
 * Retrieves a value from the text module outputs at the specified index.
 *
 * @param i index of the value in outputs to retrieve
 *
 * @return the value of outputs at the specified index
 */
uint8_t comp_module_t::get_out_ertek(size_t i) {
    return end_module.get_out_ertek(i);
}
/**
 * Sets the output wire at the specified index in the module.
 *
 * @param index the index where the wire will be set
 * @param wire the wire to set at the specified index
 * @param del a boolean indicating whether to delete the existing wire at the index before setting the new wire
 */
void comp_module_t::set_wire(size_t index, wire_t* wire, bool del) {
    end_module.set_wire(index, wire, del);
}
/**
 * Destructor for the comp_module_t class, responsible for cleaning up memory and resources.
 */
comp_module_t::~comp_module_t(){
    delete[] wires;
    if (modules != NULL) {
        for (size_t i = 0; i < m_db; i++) {
            for(int j=0;j<modules[i]->get_out_num();j++)
                modules[i]->set_wire(j, NULL, false);
            delete (modules[i]);
            modules[i] = NULL;
        }
        delete[] modules;
        modules = NULL;
    }
    delete[] modules_coms;
    wires = NULL;
    modules_coms = NULL;
}
