//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_PUTEREATAC_H
#define OOP_PUTEREATAC_H


#include "Carte.h"

class PutereAtac : public Carte {
public:
    PutereAtac(const std::string& nume_, int cost_, int valoare_);

    void aplicare(Monstru* m) override;
    std::string getDescriere() const override;
};


#endif //OOP_PUTEREATAC_H