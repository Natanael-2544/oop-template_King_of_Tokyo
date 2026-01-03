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
    static Monstru* mutant(const std::string& n) {
        return new Mutant(n);
    }
    static Monstru* dragon(const std::string& n) {
        return new Dragon(n);
    }
    static Monstru* robot(const std::string& n) {
        return new Robot(n);
    }
    static Monstru* megaMutant(const std::string& n) {
        return new MegaMutant(n);
    }
};

#endif //OOP_MONSTRUFACTORY_H