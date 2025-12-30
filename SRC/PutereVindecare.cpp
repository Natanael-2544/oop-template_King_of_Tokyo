//
// Created by Nati on 12/30/2025.
//

#include "../Include/PutereVindecare.h"

PutereVindecare::PutereVindecare(const std::string& nume_, int cost_, int valoare_)
    : Carte(nume_, cost_, valoare_) {}

void PutereVindecare::aplicare(Monstru* m) {
    if (!m->getInTokyo())
        *m += valoare;
}

std::string PutereVindecare::getDescriere() const {
    return "Adauga 2 puncte de viata propriului monstru (nu poate fi folosita în Tokyo)";
}