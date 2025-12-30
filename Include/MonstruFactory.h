//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_MONSTRUFACTORY_H
#define OOP_MONSTRUFACTORY_H


#include <string>
#include <stdexcept>
#include "Mutant.h"
#include "Dragon.h"
#include "Robot.h"
#include "MegaMutant.h"

class MonstruFactory {
public:
    static Monstru* creeazaMonstru(int tip, const std::string& nume) {
        switch (tip) {
            case 1: return new Mutant(nume);
            case 2: return new Dragon(nume);
            case 3: return new Robot(nume);
            case 4: return new MegaMutant(nume);
            default: throw std::runtime_error("Tip monstru invalid");
        }
    }
};

#endif //OOP_MONSTRUFACTORY_H