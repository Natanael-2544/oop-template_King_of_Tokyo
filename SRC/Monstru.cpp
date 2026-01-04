//
// Created by Nati on 12/30/2025.
//

#include "Monstru.h"

int Monstru::idGenerator = 0;

// Constructori
Monstru::Monstru(const std::string& nume_, const int& viata_)
    : nume(nume_), viata(viata_), viataMaxima(viata_),puncteVictorie(0), fulgere(0), inTokyo(false), id(++idGenerator) {}

Monstru::Monstru(const Monstru& m)
    : nume(m.nume), viata(m.viata), viataMaxima(m.viataMaxima),puncteVictorie(m.puncteVictorie),
      fulgere(m.fulgere), inTokyo(m.inTokyo), id(idGenerator++) {}

// Destructor
Monstru::~Monstru() = default;

// Operator=
Monstru& Monstru::operator=(const Monstru& m) {
    if (this != &m) {
        id = m.id;
        nume = m.nume;
        viata = m.viata;
        viataMaxima = m.viataMaxima;
        puncteVictorie = m.puncteVictorie;
        fulgere = m.fulgere;
        inTokyo = m.inTokyo;
    }
    return *this;
}

// Alți operatori
Monstru& Monstru::operator+=(int p) {
    puncteVictorie += p;
    return *this;
}

Monstru& Monstru::operator-=(int dmg) {
    viata -= dmg;
    if (viata < 0) viata = 0;
    return *this;
}
 int Monstru::bonusFulgere() const { return 0; }
 int Monstru::bonusVindecare() const { return 0; }
 int Monstru::modificaDaune(int daune) const { return daune; }

// Getters / setters
const std::string& Monstru::getNume()  const { return nume; }
int Monstru::getViata() const { return viata; }
int Monstru::getPuncteVictorie() const { return puncteVictorie; }
int Monstru::getFulgere() const { return fulgere; }
void Monstru::adaugaFulgere(int val) { fulgere += val; }
bool Monstru::getInTokyo() const { return inTokyo; }
void Monstru::setInTokyo(bool val) { inTokyo = val; }
int Monstru::getViataMaxima() const { return viataMaxima; }
void Monstru::setViata(int v) { viata = v; }

// Operator pt citire:
std::istream& operator>>(std::istream& in, Monstru& m) {
    std::cout << "Nume monstru: ";
    in >> m.nume;
    return in;
}
// Operator << pentru afisare
std::ostream& operator<<(std::ostream& out, const Monstru& m) {
    out << m.nume << " (Viata: " << m.viata
        << ", PV: " << m.puncteVictorie
        << ", Fulgere: " << m.fulgere << ")";
    return out;
}
