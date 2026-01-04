//
// Created by Nati on 12/30/2025.
//

#include "MegaMutant.h"

MegaMutant::MegaMutant(const std::string& n)
    : Monstru(n, 9), Mutant(), Dragon(), Robot() {}

MegaMutant::MegaMutant(const MegaMutant& m)
    : Monstru(m), Mutant(), Dragon(), Robot() {}

MegaMutant& MegaMutant::operator=(const MegaMutant& m) {
    if (this != &m) {
        Monstru::operator=(m);
        Mutant::operator=(m);
        Dragon::operator=(m);
        Robot::operator=(m);
    }
    return *this;
}

 void MegaMutant::atac(Monstru* /*t*/) {}

void MegaMutant::vindecare() {
    viata += 1;
    if (viata > 9) viata = 9;
}
void MegaMutant::folosestePutere() {}

int MegaMutant::bonusFulgere() const {
    return 1;
}

int MegaMutant::bonusVindecare() const {
    return Dragon::bonusVindecare();
}

int MegaMutant::modificaDaune(int daune) const {
    return Robot::modificaDaune(daune) + 2;
}