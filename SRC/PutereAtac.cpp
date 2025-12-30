//
// Created by Nati on 12/30/2025.
//

#include "PutereAtac.h"

PutereAtac::PutereAtac(const std::string& nume_, int cost_, int valoare_)
    : Carte(nume_, cost_, valoare_) {}

void PutereAtac::aplicare(Monstru* m) {
    *m -= valoare;
}

std::string PutereAtac::getDescriere() const {
    return "Aplica 2 puncte de daune unui monstru adversar";
}
