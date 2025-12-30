//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_JOC_H
#define OOP_JOC_H

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "Monstru.h"
#include "Carte.h"
#include "ContainerZaruri.h"

class Joc {
private:
    std::vector<Monstru*> jucatori;
    std::vector<Carte*> carti;
    int maxViata = 14;
    size_t maxMonstri = 4;
    bool tokyoOcupat = false;
    int indexTokyo = -1;
    static Joc* instance;

    Joc();
    ~Joc();

    Joc(const Joc&) = delete;
    Joc& operator=(const Joc&) = delete;

    void aplicaDaune(const Monstru*  atacator, int daune);
    void intraInTokyo(Monstru* j);
    void aplicaSimboluri(Monstru* j, std::map<SimbolZar,int>& cnt);
    void verificaCumparareCarte(Monstru* j);

public:
    static Joc* getInstance();
    static void deleteInstance();

    void determinaJucatorStart();
    void adaugaJucatori(Monstru* m);
    void afisareJucatori();
    bool JocTerminat();
    void runda();
    void afisareClasament();
    void setupJoc();
    void desfasurareJoc();
};

#endif //OOP_JOC_H