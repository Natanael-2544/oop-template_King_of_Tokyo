//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_DRAGON_H
#define OOP_DRAGON_H


#include "Monstru.h"

class Dragon : virtual public Monstru {
public:
    Dragon(const std::string& n);

    void atac(Monstru* t) override;
    void vindecare() override;
    void folosestePutere() override;
};

#endif //OOP_DRAGON_H