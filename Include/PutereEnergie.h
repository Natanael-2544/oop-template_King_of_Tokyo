//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_PUTEREENERGIE_H
#define OOP_PUTEREENERGIE_H


#include "Carte.h"

class PutereEnergie : public Carte {
public:
    PutereEnergie(const std::string& nume_, int cost_, int valoare_);

    void aplicare(Monstru* m) override;
    std::string getDescriere() const override;
};



#endif //OOP_PUTEREENERGIE_H