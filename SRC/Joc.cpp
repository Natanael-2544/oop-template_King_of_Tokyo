//
// Created by Nati on 12/30/2025.
//

#include "Joc.h"
#include "Monstru.h"
#include "Mutant.h"
#include "Dragon.h"
#include "Robot.h"
#include "MegaMutant.h"
#include "Carte.h"
#include "PutereAtac.h"
#include "PutereVindecare.h"
#include "PutereEnergie.h"
#include "SimbolZar.h"
#include "ContainerZaruri.h"
#include "MonstruFactory.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <map>
#include <iostream>
#include <string>
// Instanta statica
Joc* Joc::instance = nullptr;

// Constructor privat
Joc::Joc() {}

// Destructor
Joc::~Joc() {
    for ( auto m: jucatori) delete m;
    jucatori.clear();
    for (auto c: carti) delete c;
    carti.clear();
}

// Instanta unica
Joc* Joc::getInstance() {
    if(!instance) instance = new Joc();
    return instance;
}

void Joc::deleteInstance() {
    delete instance;
    instance = nullptr;
}

void Joc::adaugaJucatori(Monstru* m) {
    if (jucatori.size() >= maxMonstri)
        throw std::runtime_error("Maximul Jucatorilor a fost atins!");
    jucatori.push_back(m);
}

void Joc::afisareJucatori() {
    std::cout << "--- Stare jucatori ---\n";
    for(size_t i=0; i<jucatori.size(); i++)
        std::cout << i+1 << ". " << *jucatori[i] << "\n";
}

bool Joc::JocTerminat() {
    for (const Monstru*  m: jucatori)
        if (m->getPuncteVictorie() >= 8) return true;

    int alive = 0;
    for (const Monstru* m: jucatori)
        if (m->getViata() > 0) alive++;

    return alive <= 1;
}

// Metoda privata: aplica daune
void Joc::aplicaDaune(const Monstru*  atacator, int daune) {
    if (atacator->getInTokyo()) {
        for ( Monstru* const  m : jucatori) {
            if (m != atacator && m->getViata() > 0) {
                int dauneActuale = daune;
                if(dynamic_cast<Robot*>(m)) {dauneActuale = std::max(0, dauneActuale-1);}
                if(dynamic_cast<MegaMutant*>(m)) {dauneActuale += 2;}
                std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << m->getNume() << "\n";
                *m -= dauneActuale;
            }
        }
    } else if(tokyoOcupat) {
        Monstru* inTokyo = jucatori[indexTokyo];
        int dauneActuale = daune;
        if(dynamic_cast<Robot*>(inTokyo)) {dauneActuale = std::max(0, dauneActuale-1);}
        if(dynamic_cast<MegaMutant*>(inTokyo)) {dauneActuale += 1;}
        std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << inTokyo->getNume() << "\n";
        *inTokyo -= dauneActuale;

        std::cout << inTokyo->getNume() << ", vrei sa iesi din Tokyo? 1=DA, 0=NU: ";
        int opt; std::cin >> opt;
        if(opt==1){
            inTokyo->setInTokyo(false);
            tokyoOcupat = false;
            indexTokyo = -1;
        }
    } else {
        std::vector<Monstru*> potentiali;
        for(auto m : jucatori)
            if(m != atacator && m->getViata() > 0) potentiali.push_back(m);

        if(!potentiali.empty()) {
            std::cout << "Alege un jucator pe care sa il ataci:\n";
            for(size_t i=0;i<potentiali.size();i++)
                std::cout << i+1 << ". " << potentiali[i]->getNume() << "\n";
            int opt; std::cin >> opt;
            if(opt >= 1 && opt <= (int)potentiali.size()) {
                Monstru* target = potentiali[opt-1];
                int dauneActuale = daune;
                if(dynamic_cast<Robot*>(target)) {dauneActuale = std::max(0, dauneActuale-1);}
                if( dynamic_cast<MegaMutant*>(target)) {dauneActuale += 1;}

                *target -= dauneActuale;
                std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << target->getNume() << "\n";
            }
        }
    }
}

// Metoda privata: intra in Tokyo
void Joc::intraInTokyo(Monstru* j) {
    if(!tokyoOcupat){
        std::cout << j->getNume() << ", vrei sa intri in Tokyo? 1=DA,0=NU: ";
        int opt; std::cin >> opt;
        if(opt==1){
            tokyoOcupat = true;
            indexTokyo = std::distance(jucatori.begin(), std::find(jucatori.begin(), jucatori.end(), j));
            j->setInTokyo(true);
            std::cout << j->getNume() << " a intrat in Tokyo!\n";
        }
    }
}


// Metoda privata: aplica simboluri de zar
void Joc::aplicaSimboluri(Monstru* j, std::map<SimbolZar,int>& cnt) {
    for(int p=1; p<=3; p++) {
        SimbolZar s = static_cast<SimbolZar>(p-1);
        int count = cnt[s];

        int triplete = count / 3;
        if(triplete > 0){
            *j += triplete * p;
            count -= triplete * 3;
            std::cout << j->getNume() << " a castigat " << triplete * p << " PV pentru " << triplete << " triplete!\n";
            std::cout << *j << "\n";
        }

        int rest = count % 3;
        if(rest == 2){
            j->adaugaFulgere(p);
            std::cout << j->getNume() << " a castigat " << p << " fulgere pentru dublet!\n";
        }
    }

    if(cnt[SimbolZar::Fulger] > 0){
        int bonus = 0;
        if( dynamic_cast<Mutant*>(j)) {bonus += cnt[SimbolZar::Fulger];}
        j->adaugaFulgere(cnt[SimbolZar::Fulger] + bonus);
        std::cout << j->getNume() << " castiga " << (cnt[SimbolZar::Fulger] + bonus) << " fulgere *\n";
    }

    if(!j->getInTokyo() && cnt[SimbolZar::Inima] > 0){
        int heal = 1;
        if( dynamic_cast<Dragon*>(j)) {heal += 1;}
        for(int i=0;i<heal;i++) j->vindecare();
        std::cout << j->getNume() << " s-a vindecat\n";
        std::cout << *j << "\n";
    }

    if(cnt[SimbolZar::Gheara] > 0){
        aplicaDaune(j, cnt[SimbolZar::Gheara]);
        if(!j->getInTokyo() && !tokyoOcupat){
            tokyoOcupat = true;
            indexTokyo = std::distance(jucatori.begin(), std::find(jucatori.begin(), jucatori.end(), j));
            j->setInTokyo(true);
            std::cout << j->getNume() << " a intrat in Tokyo!\n";
            std::cout << *j << "\n";
        }
    }
}

// Metoda privata: verifica cumparare carte
void Joc::verificaCumparareCarte(Monstru* j){
    if (j->getFulgere() < 4) return;

    std::vector<Carte*> oferte;
    oferte.push_back(new PutereAtac("PutereAtac", 4, 2));
    oferte.push_back(new PutereVindecare("PutereVindecare", 5, 2));
    oferte.push_back(new PutereEnergie("PutereEnergie", 4, 1));

    std::vector<Carte*> oferteValide;
    for(auto c : oferte)
        if(j->getFulgere() >= c->getCost())
            oferteValide.push_back(c);

    if(oferteValide.empty()){
        std::cout << "Nu ai suficiente fulgere pentru nicio carte.\n";
        for(auto oc: oferte) delete oc;
        return;
    }

    std::cout << "Vrei sa cumperi o carte? 1=DA, 0=NU: ";
    int opt; std::cin >> opt;
    if(opt != 1){
        for(auto oc: oferte) delete oc;
        return;
    }

    std::cout << "Oferte disponibile:\n";
    for(size_t i=0;i<oferteValide.size();i++)
        std::cout << i+1 << ". " << oferteValide[i]->getNume()
                  << ": " << oferteValide[i]->getDescriere()
                  << ". Costa " << oferteValide[i]->getCost() << " fulgere\n";

    int alegere;
    std::cin >> alegere;

    if(alegere < 1 || alegere > (int)oferteValide.size()){
        std::cout << "Alegere invalida!\n";
        for(auto oc: oferte) delete oc;
        return;
    }

    Carte* c = oferteValide[alegere-1];
    if(j->getFulgere() < c->getCost())
        throw std::runtime_error("Nu ai suficiente fulgere pentru a cumpara aceasta carte!");

    j->adaugaFulgere(-c->getCost());

    if(PutereAtac* pa = dynamic_cast<PutereAtac*>(c)){
        if(tokyoOcupat && !j->getInTokyo()){
            Monstru* target = jucatori[indexTokyo];
            pa->aplicare(target);
        } else if(j->getInTokyo()){
            for(auto m: jucatori)
                if(m != j && m->getViata() > 0)
                    pa->aplicare(m);
        }
    } else {
        c->aplicare(j);
    }

    for(auto oc: oferte) delete oc;
}

void Joc::determinaJucatorStart() {
    std::vector<int> zaruriStart(jucatori.size(), 0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    bool egalitate = true;
    std::vector<int> candidati(jucatori.size());
    std::iota(candidati.begin(), candidati.end(), 0);

    while (egalitate){
        egalitate = false;
        int maxZar = 0;
        std::vector<int> ceiMaiBuni;

        for (int i : candidati){
            zaruriStart[i] = dis(gen);
            std::cout << jucatori[i]->getNume() << " a aruncat zarul: " << zaruriStart[i] << "\n";
            if (zaruriStart[i] > maxZar){
                maxZar = zaruriStart[i];
                ceiMaiBuni = {i};
            } else if(zaruriStart[i] == maxZar){
                ceiMaiBuni.push_back(i);
            }
        }

        if(ceiMaiBuni.size() > 1){
            std::cout << "Egalitate! Se reia aruncarea pentru cei cu zar " << maxZar << "\n";
            candidati = ceiMaiBuni;
            egalitate = true;
        } else {
            std::swap(jucatori[0], jucatori[ceiMaiBuni[0]]);
            std::cout << jucatori[0]->getNume() << " incepe jocul!\n";
        }
    }
}

void Joc::runda() {
    for(size_t i=0;i<jucatori.size();i++){
        Monstru* j = jucatori[i];
        if(j->getViata() <= 0) continue;

        std::cout << "\nTura lui " << j->getNume() << " (" << j->getViata() << " viata, " << j->getPuncteVictorie() << " PV)\n";

        ContainerZaruri<std::vector<SimbolZar>> zar;
        zar.aruncaZar();
        std::cout << "Rezultat zaruri: "; zar.afisareRezultate();

        std::map<SimbolZar,int> cnt;
        for(auto z : zar.getZaruri()) cnt[z]++;

        aplicaSimboluri(j, cnt);
        verificaCumparareCarte(j);
        if(!tokyoOcupat && cnt[SimbolZar::Gheara] > 0)
            intraInTokyo(j);
    }

    // La finalul rundei, acorda puncte de victorie
    for(auto m: jucatori){
        if(m->getViata() <= 0) continue;
        if(m->getInTokyo())
            *m += 2;
        else
            *m += 1;
    }
}

void Joc::afisareClasament() {
    std::sort(jucatori.begin(), jucatori.end(), [](const Monstru* a, const Monstru* b){ return a->getPuncteVictorie() > b->getPuncteVictorie(); });
    std::cout << "\n=== Clasament final ===\n";
    for(size_t i=0;i<jucatori.size();i++)
        std::cout << i+1 << ". " << *jucatori[i] << "\n";
}
void Joc::setupJoc() {
    int n;
    std::cout << "Bine ati venit la King of Tokyo!\n";
    do {
        std::cout << "Numar jucatori (2-4): ";
        std::cin >> n;
    } while (n < 2 || n > 4);

    for (int i = 0; i < n; i++) {
        std::cout << "Jucator " << i + 1 << ": Alege monstru:\n1. Mutant\n2. Dragon\n3. Robot\n4. MegaMutant\nOptiune: ";
        int t; std::cin >> t;
        std::string nume;
        std::cout << "Nume jucator: "; std::cin >> nume;
        Monstru* m = MonstruFactory::creeazaMonstru(t, nume);
        adaugaJucatori(m);
    }

    determinaJucatorStart();
}

void Joc::desfasurareJoc() {
    bool stop = false;
    int nrrunda = 1;

    while (!stop && !JocTerminat()) {
        std::cout << "\n=== Runda " << nrrunda << " ===\n";
        runda();
        std::cout << "Vrei sa inchei jocul acum? 1=DA,0=NU: ";
        int opt; std::cin >> opt;
        if (opt == 1) stop = true;
        afisareJucatori();
        nrrunda++;
    }

    afisareClasament();
    std::cout << "Joc incheiat!\n";
}

