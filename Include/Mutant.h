//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_MUTANT_H
#define OOP_MUTANT_H

#include "Monstru.h"

class Mutant : virtual public Monstru {
public:
    Mutant(const std::string& n);

    void atac(Monstru* t) override;
    void vindecare() override;
    void folosestePutere() override;
};


#endif //OOP_MUTANT_H