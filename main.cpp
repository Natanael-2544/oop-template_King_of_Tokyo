#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include <map>
#include <memory>

//Enum SimbolZar
enum class SimbolZar {Punct1, Punct2, Punct3, Energie, Inima, Gheara};

//
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
    Monstru(const std::string& nume_, const int& viata_):
        nume(nume_), viata(viata_), puncteVictorie(0), fulgere(0), inTokyo(false), id(++idGenerator) {}
    Monstru(const Monstru& m):nume(m.nume), viata(m.viata), puncteVictorie(m.puncteVictorie), fulgere(m.fulgere), inTokyo(m.inTokyo), id(idGenerator++) {}
    virtual ~Monstru()=default;

    Monstru& operator=(const Monstru& m) {
        if (this != &m) {
            nume = m.nume;
            viata = m.viata;
            puncteVictorie = m.puncteVictorie;
            fulgere = m.fulgere;
            inTokyo = m.inTokyo;
        }
        return *this;
    }

    Monstru& operator+=(int p){ puncteVictorie+=p; return *this; }
    Monstru& operator-=(int p){ puncteVictorie-=p; return *this; }

    virtual void atac(Monstru* adversar) = 0;
    virtual void vindecare() = 0;
    virtual void folosestePutere() = 0;

    std::string getNume() const { return nume; }
    int getViata() const { return viata; }
    int getPuncteVictorie() const { return puncteVictorie; }
    int getFulgere() const { return fulgere; }
    bool getInTokyo() const { return inTokyo; }
    void setInTokyo( bool val){ inTokyo = val; }

    friend std::ostream& operator<<(std::ostream& out, const Monstru& m) {
        out << m.nume << " (Viata: " << m.viata << ", PV: " << m.puncteVictorie << ", Fulgere: "<<m.fulgere<<" ) ";
        return out;
    }
};
int Monstru::idGenerator = 0;

//Clase Derivate

class Mutant : virtual public Monstru {
public:
    Mutant(const std:: string& n) : Monstru(n,12) {}
    void atac(Monstru* t) override { *t -= 1; *this +=1; }
    void vindecare() override { viata += 2; if(viata>12) viata=12; }
    void folosestePutere() override { *this += 2; }
};

class Dragon : virtual public Monstru {
public:
    Dragon(const std::string& n) : Monstru(n,10) {}
    void atac(Monstru* t) override { *t -= 2; *this +=1; }
    void vindecare() override { viata += 1; if(viata>10) viata=10; }
    void folosestePutere() override { *this += 3; }
};

class Robot : virtual public Monstru {
public:
    Robot(const std::string& n) : Monstru(n,14) {}
    void atac(Monstru* t) override { *t -= 1; *this +=1; }
    void vindecare() override { viata += 2; if(viata>14) viata=14; }
    void folosestePutere() override { *this += 2; }
};

class MegaMutant : public Mutant, public Dragon, public Robot {
public:
    MegaMutant(const std::string& n) : Monstru(n,8), Mutant(n), Dragon(n), Robot(n) {}
    void atac(Monstru* t) override { *t -= 2; *this +=2; }
    void vindecare() override { viata += 1; if(viata>8) viata=8; }
    void folosestePutere() override { *this += 3; }
};

//Factory Monstru
class MonstruFactory {
public:
    static Monstru* creeazaMonstru(int tip, const std::string& nume){
        switch (tip) {
            case 1: return new Mutant(nume);
            case 2: return new Dragon(nume);
            case 3: return new MegaMutant(nume);
            case 4: return new MegaMutant(nume);
            default: throw std::runtime_error("Tip monstru invalid");
        }
    }
};

//CLASA ABSTRACTA CARTE
class Carte {
protected:
    std::string nume;
    int cost;
    int valoare;
public:
    Carte(const std::string& nume_, const int& cost_, const int& valoare_):
        nume(nume_), cost(cost_), valoare(valoare_) {}
    virtual ~Carte()=default;
    virtual void aplicare(Monstru *target)=0;
    std::string getNume() const { return nume;}
    int getCost() const { return cost; }
    int getValoare() const { return valoare; }
};

class PutereAtac : public Carte {
public:
    PutereAtac(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override {*m-=valoare;}
};

class PutereVindecare : public Carte {
public:
    PutereVindecare(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override { if(!m->getInTokyo()) *m += valoare; }
};

class PutereEnergie : public Carte {
public:
    PutereEnergie(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override { m->getFulgere(); *m += valoare; }
};

//template
template <class T>
class ContainerZaruri {
private:
    T zaruri;
public:
    void aruncaZaruri() {
        zaruri.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0,5);
        for(int i=0;i<6;i++){
            zaruri.push_back(static_cast<SimbolZar>(dis(gen)));
        }
    }
    T& getZaruri() { return zaruri; }
    void afisareRezultate(){
        for(auto &z: zaruri){
            switch(z){
                case SimbolZar::Punct1: std::cout<<"1 "; break;
                case SimbolZar::Punct2: std::cout<<"2 "; break;
                case SimbolZar::Punct3: std::cout<<"3 "; break;
                case SimbolZar::Energie: std::cout<<"⚡ "; break;
                case SimbolZar::Inima: std::cout<<"❤️ "; break;
                case SimbolZar::Gheara: std::cout<<"🐾 "; break;
            }
        }
        std::cout<<"\n";
    }
};

int main() {
    return 0;
}





