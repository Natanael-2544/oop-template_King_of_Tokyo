//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_CARTE_H
#define OOP_CARTE_H


#include <string>
#include "Monstru.h"

class Carte {
protected:
    std::string nume;
    int cost;
    int valoare;
public:
    Carte(const std::string& nume_, int cost_, int valoare_);
    virtual ~Carte();

    virtual void aplicare(Monstru* m) = 0;
    virtual std::string getDescriere() const = 0;

    const std::string& getNume() const;
    int getCost() const;
    int getValoare() const;
};


#endif //OOP_CARTE_H