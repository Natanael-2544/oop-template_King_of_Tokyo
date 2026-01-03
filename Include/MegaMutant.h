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
    [[maybe_unused]] void atac(Monstru* t) override;
    void vindecare() override;
    [[maybe_unused]] void folosestePutere() override;
    int modificaDaune(int daune) const override;

};

#endif //OOP_MEGAMUTANT_H