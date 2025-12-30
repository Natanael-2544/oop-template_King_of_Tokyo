//
// Created by Nati on 12/30/2025.
//

#include "../Include/PutereEnergie.h"

PutereEnergie::PutereEnergie(const std::string& nume_, int cost_, int valoare_)
    : Carte(nume_, cost_, valoare_) {}

void PutereEnergie::aplicare(Monstru* m) {
    m->adaugaFulgere(valoare);
}

std::string PutereEnergie::getDescriere() const {
    return "Adauga 1 punct de victorie la finalul rundei";
}