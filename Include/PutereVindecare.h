//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_PUTEREVINDECARE_H
#define OOP_PUTEREVINDECARE_H


#include "Carte.h"

class PutereVindecare : public Carte {
public:
    PutereVindecare(const std::string& nume_, int cost_, int valoare_);

    void aplicare(Monstru* m) override;
    std::string getDescriere() const override;
};


#endif //OOP_PUTEREVINDECARE_H