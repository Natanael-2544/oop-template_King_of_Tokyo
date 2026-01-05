//
// Created by Nati on 12/30/2025.
//

#include "Mutant.h"

Mutant::Mutant(const std::string& n) : Monstru(n, 12) {}

void Mutant::vindecare() {
    viata += 2;
    if (viata > 12) viata = 12;
}

int Mutant::bonusFulgere() const {
    return 1;
}