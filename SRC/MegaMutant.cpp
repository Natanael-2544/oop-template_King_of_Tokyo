//
// Created by Nati on 12/30/2025.
//

#include "MegaMutant.h"

MegaMutant::MegaMutant(const std::string& n)
    : Monstru(n, 9), Mutant(n), Dragon(n), Robot(n) {}

void MegaMutant::atac(Monstru* t) {
    if (!t) return;
    *t -= 2;
    *this += 2;
}

void MegaMutant::vindecare() {
    viata += 1;
    if (viata > 9) viata = 9;
}

void MegaMutant::folosestePutere() {
    *this += 3;
}