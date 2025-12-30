//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_ROBOT_H
#define OOP_ROBOT_H

#include "Monstru.h"

class Robot : virtual public Monstru {
public:
    explicit Robot(const std::string& n);

    void atac(Monstru* t) override;
    void vindecare() override;
    void folosestePutere() override;
};


#endif //OOP_ROBOT_H