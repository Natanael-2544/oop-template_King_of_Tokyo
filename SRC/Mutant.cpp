//
// Created by Nati on 12/30/2025.
//

#include "Mutant.h"

Mutant::Mutant(const std::string& n) : Monstru(n, 12) {}

void Mutant::atac(Monstru* t) {
    if (!t) return;
    *t -= 1;
    *this += 1;
}

void Mutant::vindecare() {
    viata += 2;
    if (viata > 12) viata = 12;
}

void Mutant::folosestePutere() {
    *this += 2;
}