//
// Created by Nati on 12/30/2025.
//

#include "Carte.h"
#include "Joc.h"
Carte::Carte(const std::string& nume_, int cost_, int valoare_)
    : nume(nume_), cost(cost_), valoare(valoare_) {}

Carte::~Carte() = default;

const std::string& Carte::getNume() const { return nume; }
int Carte::getCost() const { return cost; }
