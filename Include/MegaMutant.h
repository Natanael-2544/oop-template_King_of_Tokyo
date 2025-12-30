//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_MEGAMUTANT_H
#define OOP_MEGAMUTANT_H

#include "Mutant.h"
#include "Dragon.h"
#include "Robot.h"

class MegaMutant : public Mutant, public Dragon, public Robot {
public:
    explicit MegaMutant(const std::string& n);
    void atac(Monstru* t) override;
    void vindecare() override;
    void folosestePutere() override;
};

#endif //OOP_MEGAMUTANT_H