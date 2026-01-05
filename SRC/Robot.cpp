//
// Created by Nati on 12/30/2025.
//

#include "Robot.h"

Robot::Robot(const std::string& n) : Monstru(n, 14) {}

void Robot::vindecare() {
    viata += 2;
    if (viata > 14) viata = 14;
}

int Robot::modificaDaune(int daune) const {
    return daune - 1;
}