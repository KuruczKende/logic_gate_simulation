#include "text_module.h"
uint8_t mynot(uint8_t a) {
    switch (a) {
    case low:return high;
    case high:return low;
    default:return undet;
    }
}
uint8_t myand(uint8_t a, uint8_t b) {
    switch (a + b) {
    case undet + high:return undet;
    case undet + undet:return undet;
    case high + high:return high;
    default:return low;
    }
}
uint8_t myor(uint8_t a, uint8_t b) {
    switch (a + b) {
    case undet + low:return undet;
    case undet + undet:return undet;
    case low + low:return low;
    default:return high;
    }
}
uint8_t myxor(uint8_t a, uint8_t b) {
    if (a == undet || b == undet)return undet;
    return a != b ? high : low;
}
void lepteto(size_t torlendo, size_t index, lista<size_t>& hely, char*& ideiglenes, size_t& hossz) {
    for (size_t k = hely[index]; k < hossz - torlendo; k++)
        ideiglenes[k] = ideiglenes[k + torlendo];
    for (size_t k = index; k < hely.length(); k++)
        hely[k] -= torlendo;
    hossz -= torlendo;
}
bool muvs(size_t index, lista<size_t>& hely, char*& ideiglenes, size_t& hossz, bool neg, uint8_t& ertek, size_t& nertek) {
    uint8_t findex = hely[index] + (neg ? 1 : 0);
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
    nertek = hely[index] - 1;
    lepteto(neg ? 3 : 2, index, hely, ideiglenes, hossz);
    if (neg)ertek = mynot(ertek);
    return true;
}
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
    ki_ertek = new uint8_t[ki_db]{ undet };
    be_ertek = new uint8_t[be_db]{ undet };
    be_old = new uint8_t[be_db]{ undet };
    ki_wires = new wire_t * [ki_db];
}
text_module_t::text_module_t(const text_module_t& refe) {
    *this = text_module_t(refe.parancsok);
}
module_t* text_module_t::copy() {
    return new text_module_t(this->parancsok);
}
void text_module_t::vegrehajtas(lista<wire_t*>& wait_for_do) {
    size_t kez = 0, veg = 0;
    for (size_t i = 0; i < ki_db; i++) {
        while (parancsok[veg] != ',' && parancsok[veg] != '\0')veg++;
        bool trigger = true;
        if (parancsok[kez] == '[') {
            trigger = false;
            kez++;
            while (parancsok[kez] != ']')
                if (be_ertek[parancsok[kez] - 'a'] != be_old[parancsok[kez++] - 'a'])
                    trigger = true;
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
                switch (ideiglenes[index]) {
                case '~':
                    if (parancsok[moz + 1] == '|' || parancsok[moz + 1] == '&' || parancsok[moz + 1] == '^') {
                        hely.add(index);
                        fsag.add(fs);
                        if (fs > maxfsag)maxfsag = fs;
                        moz++;
                        index++;
                        ideiglenes[index] = parancsok[moz];
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
                    if (ideiglenes[index] != '0' && ideiglenes[index] != '1')
                        ideiglenes[index] = be_ertek[ideiglenes[index] - 'a'];
                    break;
                }
                moz++;
                index++;
            }//mûveleti lista befejezve
            for (int j = maxfsag; j >= 0; j--) {
                for (size_t i = 0; i < hely.length(); i++) {
                    if (fsag[i] == j) {
                        size_t nertek;
                        uint8_t ertek;
                        if (ideiglenes[hely[i]] == '~') {
                            if (!muvs(i, hely, ideiglenes, hossz, true, ertek, nertek)) {
                                nertek = hely[i];
                                ertek = mynot(ideiglenes[hely[i] + 1]);
                                lepteto(1, i, hely, ideiglenes, hossz);
                            }
                        }
                        else
                            muvs(i, hely, ideiglenes, hossz, false, ertek, nertek);
                        if (nertek > 0 && nertek < hossz)
                            if (ideiglenes[nertek - 1] == '(' && ideiglenes[nertek + 1] == ')') {
                                for (size_t k = i; k < hely.length(); k++)
                                    hely[k] -= 2;
                                for (size_t k = nertek; k < hossz - 2; k++)
                                    ideiglenes[k] = ideiglenes[k + 2];
                                nertek--;
                            }
                        ideiglenes[nertek] = ertek;
                    }
                }
            }
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
void text_module_t::setin(size_t index, uint8_t ertek) {
    if (index >= be_db)throw "over indexed";
    if (index < 0)throw "under indexed";
    be_ertek[index] = ertek;
}