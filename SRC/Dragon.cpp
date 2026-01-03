//
// Created by Nati on 12/30/2025.
//

#include "Dragon.h"
Dragon::Dragon(const std::string& n) : Monstru(n, 10) {}

void Dragon::atac(Monstru* t) {
    if (!t) return;
    *t -= 2;
    *this += 1;
}

void Dragon::vindecare() {
    viata += 1;
    if (viata > 10) viata = 10;
}

void Dragon::folosestePutere() {
    *this += 3;
}

int Dragon::bonusVindecare() const {
    return 1;
}
