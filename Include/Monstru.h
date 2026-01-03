//
// Created by Nati on 12/30/2025.
//

#ifndef OOP_MONSTRU_H
#define OOP_MONSTRU_H

#include<iostream>
#include<string>

class Monstru {
protected:
    std::string nume;
    int viata;
    int puncteVictorie;
    int fulgere;
    bool inTokyo;
    int id;
    static int idGenerator;

public:
    Monstru(const std::string& nume_, const int& viata_);
    Monstru(const Monstru& m);
    virtual ~Monstru();

    Monstru& operator=(const Monstru& m);

    Monstru& operator+=(int p);
    Monstru& operator-=(int dmg);

    virtual void atac(Monstru* adversar) = 0;
    virtual void vindecare() = 0;
    virtual void folosestePutere() = 0;

    const std::string& getNume() const;
    int getViata() const;
    int getPuncteVictorie() const;
    int getFulgere() const;
    void adaugaFulgere(int val);
    bool getInTokyo() const;
    void setInTokyo( bool val);

    virtual int modificaDaune(int daune) const;
    virtual int bonusFulgere() const;
    virtual int bonusVindecare() const;

    friend std::ostream& operator<<(std::ostream& out, const Monstru& m);
};

#endif //OOP_MONSTRU_H