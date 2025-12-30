//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_CONTAINERZARURI_H
#define OOP_CONTAINERZARURI_H


#include <vector>
#include <list>
#include <map>
#include <random>
#include <iostream>
#include "SimbolZar.h"

template <class T>
class ContainerZaruri {
private:
    T zaruri;
public:
    void aruncaZar() {
        zaruri.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0,5);
        for(int i = 0; i < 6; i++) {
            zaruri.push_back(static_cast<SimbolZar>(dis(gen)));
        }
    }

    T& getZaruri() { return zaruri; }

    void afisareRezultate() {
        std::map<SimbolZar,std::string> simboluri {
                {SimbolZar::Punct1,"1"},
                {SimbolZar::Punct2,"2"},
                {SimbolZar::Punct3,"3"},
                {SimbolZar::Fulger,"*"},
                {SimbolZar::Inima,"H"},
                {SimbolZar::Gheara,"G"}
        };

        for(auto &z : zaruri) {
            std::cout << simboluri[z] << " ";
        }
        std::cout << "\n";
    }
};

template class ContainerZaruri<std::vector<SimbolZar>>;
template class ContainerZaruri<std::list<SimbolZar>>;

#endif //OOP_CONTAINERZARURI_H