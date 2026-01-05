//
// Created by Nati on 12/30/2025.
//

#include "Dragon.h"
Dragon::Dragon(const std::string& n) : Monstru(n, 10) {}

void Dragon::vindecare() {
    viata += 1;
    if (viata > 10) viata = 10;
}

int Dragon::bonusVindecare() const {
    return 1;
}
