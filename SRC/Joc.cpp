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

int citesteIntre(int min, int max, const std::string& mesaj) {
    for(int incercare = 1; incercare <= 2; ++incercare) {
        int val;
        std::cout << mesaj;
        if (std::cin >> val && val >= min && val <= max) {
            return val;
        }
        std::cin.clear();
        char ch;
        while (std::cin.get(ch) && ch != '\n');

        if(incercare == 1) {
            std::cout << "Input invalid! Mai ai o sansa.\n";
        } else {
            std::cout << "Input invalid din nou! Se va trece peste aceasta alegere.\n";
        }
    }
    return -1;
}

// Instanta statica
Joc* Joc::instance = nullptr;

// Constructor privat
Joc::Joc() {}

// Destructor
Joc::~Joc() {
    for ( auto m: jucatori) {delete m;}
    jucatori.clear();

    for (Carte* c : carti) {
        delete c;
    }
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
    if (jucatori.size() >= maxMonstri) {
        delete m;
        throw std::runtime_error("Maximul Jucatorilor a fost atins!");
    }
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
                int dauneActuale = m->modificaDaune(daune);
                std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << m->getNume() << "\n";
                *m -= dauneActuale;
            }
        }
    } else if(tokyoOcupat) {
        Monstru* inTokyo = jucatori[indexTokyo];
        int dauneActuale = inTokyo->modificaDaune(daune);
        std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << inTokyo->getNume() << "\n";
        *inTokyo -= dauneActuale;
        int opt = citesteIntre(0, 1, inTokyo->getNume() + ", vrei sa iesi din Tokyo? 1=DA, 0=NU: ");
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
                int dauneActuale = target->modificaDaune(daune);
                *target -= dauneActuale;
                std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << target->getNume() << "\n";
            }
        }
    }
}

// Metoda privata: intra in Tokyo
void Joc::intraInTokyo(Monstru* j) {
    if(!tokyoOcupat){
        int opt = citesteIntre(0, 1, j->getNume() + ", vrei sa intri in Tokyo? 1=DA, 0=NU: ");
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
        int bonus = j->bonusFulgere();
        int totalFulgere = cnt[SimbolZar::Fulger] + bonus;
        j->adaugaFulgere(totalFulgere);
        std::cout << j->getNume() << " castiga " << (cnt[SimbolZar::Fulger] + bonus) << " fulgere *\n";
    }

    if(!j->getInTokyo() && cnt[SimbolZar::Inima] > 0){
        int heal = 1 + j->bonusVindecare();
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
    if (j==nullptr || j->getFulgere() < 4) return;

    std::vector<Carte*> oferte;
    oferte.push_back(new PutereAtac("PutereAtac", 4, 2));
    oferte.push_back(new PutereVindecare("PutereVindecare", 5, 2));
    oferte.push_back(new PutereEnergie("PutereEnergie", 4, 1));

    std::vector<Carte*> oferteValide;
    for(auto c : oferte) {
        if(j->getFulgere() >= c->getCost()) {
            oferteValide.push_back(c);
        }
    }
    if(oferteValide.empty()){
        std::cout << "Nu ai suficiente fulgere pentru nicio carte.\n";
        for(auto oc: oferte) delete oc;
        return;
    }

    int opt = citesteIntre(0, 1, "Vrei sa cumperi o carte? 1=DA, 0=NU: ");
    if (opt!=1) {
        for (auto oc : oferte) delete oc;
        return;
    }

    int optiune = citesteIntre(1, oferteValide.size(), "Alege o carte: ");
    if(optiune == -1) {
        for(auto oc: oferte) delete oc;
        return;
    }

    std::cout << "Oferte disponibile:\n";
    for(size_t i=0;i<oferteValide.size();i++)
        std::cout << i+1 << ". " << oferteValide[i]->getNume()
                  << ": " << oferteValide[i]->getDescriere()
                  << ". Costa " << oferteValide[i]->getCost() << " fulgere\n";

    int alegere=0;
    if (!(std::cin >> alegere)) {
        std::cin.clear();
        for(auto oc: oferte) delete oc;
        return;
    }

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
        if(tokyoOcupat && !j->getInTokyo() && indexTokyo>=0){
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

    for(auto oc: oferte) {delete oc;}
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

        std::cout << "\nTura lui " << *j << "\n";

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
    std::cout << "Bine ati venit la King of Tokyo!\n";
    int n = citesteIntre(2, 4, "Numar jucatori (2-4): ");
    if(n == -1) {return;}

    for (int i = 0; i < n; i++) {
        std::cout << "Jucator " << i + 1 << ": Alege monstru:\n1. Mutant\n2. Dragon\n3. Robot\n4. MegaMutant\n";
        int t = citesteIntre(1, 4, "Optiune: ");
        if(t == -1) {
            std::cout << "Jucatorul va fi sarit.\n";
            continue;
        }
        Monstru* m = nullptr;
        switch(t) {
            case 1: m = MonstruFactory::mutant(""); break;
            case 2: m = MonstruFactory::dragon(""); break;
            case 3: m = MonstruFactory::robot(""); break;
            case 4: m = MonstruFactory::megaMutant(""); break;
        }
        std::cin >> *m;
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

