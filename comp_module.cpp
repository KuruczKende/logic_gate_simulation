#include "comp_module.h"
bool eggyezik(const char* str, const char* str2, size_t kez, size_t veg) {
    if (strlen(str) != veg - kez) return false;
    for (size_t i = 0; i + kez < veg; i++)
        if (str[i] != str2[kez + i])
            return false;
    return true;
}
comp_module_t::comp_module_t(char* modules_coms, lista<prot_module_t>& prot_modules) {
    this->modules_coms = new char[strlen(modules_coms) + 1];
    strcpy(this->modules_coms, modules_coms);
    m_db = 0;
    size_t max_inner = 'A' - 1;
    size_t max_in = 'a' - 1;
    size_t max_out = 'a' - 1;
    size_t min_out = 'z' + 1;

    bool port = false;
    bool outport = false;
    lista<size_t> vegk;
    lista<size_t> kezk;
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
    size_t be_db = (min_out - 1 < max_in ? min_out - 1 : max_in) - 'a' + 1;
    size_t ki_db = max_out - 'a' + 1 - be_db;
    this->be_db = this->ki_db = be_db;
    end_module = shell_module_t(ki_db);
    ki_wires = new wire_t * [be_db];
    for (size_t i = 0; i < be_db; i++)
        ki_wires[i] = new wire_t();
    modules = new module_t * [m_db];
    if (max_inner >= 'A')
        w_db = max_inner - 'A' + 2 + ki_db;
    else
        w_db = ki_db + 1;
    wires = new wire_t[w_db];
    for (size_t i = 0; i < m_db; i++) {
        size_t j = 0;
        while (!eggyezik(prot_modules[j].nev, modules_coms, kezk[i], vegk[i]))
            j++;
        modules[i] = prot_modules[j].prot->copy();//itt baszódik el, copy függvény megírása
        j = vegk[i] + 1;
        size_t k = 0;
        while (modules_coms[j] != ',') {
            if (modules_coms[j] == '0' || modules_coms[j] == '1')
                modules[i]->setin(k++, modules_coms[j++]);
            else if (modules_coms[j] - 'a' < be_db)
                ki_wires[modules_coms[j++] - 'a']->add(modules[i], k++);
            else if (modules_coms[j] - 'a' < be_db + ki_db)
                wires[modules_coms[j++] - 'a' - be_db].add(modules[i], k++);
            else
                wires[modules_coms[j++] - 'A' + ki_db].add(modules[i], k++);
        }
        j++;
        k = 0;
        while (modules_coms[j] != ')') {
            if (modules_coms[j] == '-') {
                modules[i]->set_wire(k++, &(wires[w_db - 1]));
                j++;
            }
            else if (modules_coms[j] - 'a' < be_db + ki_db)
                modules[i]->set_wire(k++, &(wires[modules_coms[j++] - 'a' - be_db]));
            else
                modules[i]->set_wire(k++, &(wires[modules_coms[j++] - 'A' + ki_db]));
        }
    }
    for (size_t i = 0; i < ki_db; i++) {
        wires[i].add(&end_module, i);
    }
}
comp_module_t::comp_module_t(size_t be_db, size_t ki_db, size_t m_db, size_t w_db) {
    this->be_db = this->ki_db = be_db;
    this->m_db = m_db;
    this->w_db = w_db;
    end_module = shell_module_t(ki_db);
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
    size_t j = 0;
    for (size_t i = 0; i < m_db; i++) {
        ret->modules[i] = this->modules[i]->copy();
        while (modules_coms[j] != '(')
            j++;
        j++;
        size_t k = 0;
        while (modules_coms[j] != ',') {
            if (modules_coms[j] == '0' || modules_coms[j] == '1')
                ret->modules[i]->setin(k++, modules_coms[j++]);
            else if (modules_coms[j] - 'a' < be_db)
                ret->ki_wires[modules_coms[j++] - 'a']->add(ret->modules[i], k++);
            else if (modules_coms[j] - 'a' < be_db + ki_db)
                ret->wires[modules_coms[j++] - 'a' - be_db].add(ret->modules[i], k++);
            else
                ret->wires[modules_coms[j++] - 'A' + ki_db].add(ret->modules[i], k++);
        }
        j++;
        k = 0;
        while (modules_coms[j] != ')') {
            if (modules_coms[j] == '-')
                modules[i]->set_wire(k++, &(wires[w_db - 1]));
            else if (modules_coms[j] - 'a' < be_db + ki_db)
                ret->modules[i]->set_wire(k++, &(ret->wires[modules_coms[j++] - 'a' - be_db]));
            else
                ret->modules[i]->set_wire(k++, &(ret->wires[modules_coms[j++] - 'A' + ki_db]));
        }
    }
    for (size_t i = 0; i < ki_db; i++) {
        ret->wires[i].add(&(ret->end_module), i);
    }
    ki_db = be_db;
    return ret;
}
size_t comp_module_t::get_out_num() {
    return end_module.get_out_num();
}
uint8_t comp_module_t::get_out_ertek(size_t i) {
    return end_module.get_out_ertek(i);
}
void comp_module_t::set_wire(size_t index, wire_t* wire) {
    end_module.set_wire(index, wire);
}
