//
// Created by Nati on 12/30/2025.
//

#include "Robot.h"

Robot::Robot(const std::string& n) : Monstru(n, 14) {}

void Robot::atac(Monstru* t) {
    if (!t) return;
    *t -= 1;
    *this += 1;
}

void Robot::vindecare() {
    viata += 2;
    if (viata > 14) viata = 14;
}

void Robot::folosestePutere() {
    *this += 2;
}