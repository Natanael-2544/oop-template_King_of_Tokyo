#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include <map>
#include <memory>

//Enum SimbolZar
enum class SimbolZar {Punct1, Punct2, Punct3, Fulger, Inima, Gheara};

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
    Monstru& operator-=(int dmg) {
        viata -= dmg;
        if (viata < 0) viata = 0;
        return *this;
    }

    virtual void atac(Monstru* adversar) = 0;
    virtual void vindecare() = 0;
    virtual void folosestePutere() = 0;

    std::string getNume() const { return nume; }
    int getViata() const { return viata; }
    int getPuncteVictorie() const { return puncteVictorie; }
    int getFulgere() const { return fulgere; }
    void adaugaFulgere(int val){ fulgere += val; }
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
    MegaMutant(const std::string& n) : Monstru(n,9), Mutant(n), Dragon(n), Robot(n) {}
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
            case 3: return new Robot(nume);
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
    virtual void aplicare(Monstru* m) = 0;
    virtual std::string getDescriere() const = 0;
    std::string getNume() const { return nume;}
    int getCost() const { return cost; }
    int getValoare() const { return valoare; }
};

class PutereAtac : public Carte {
public:
    PutereAtac(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override {
        *m -= valoare;
    }
    std::string getDescriere() const override {
        return "Aplica 2 puncte de daune unui monstru adversar";
    }
};

class PutereVindecare : public Carte {
public:
    PutereVindecare(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override { if(!m->getInTokyo()) *m += valoare; }
    std::string getDescriere() const override {
        return "Adauga 2 puncte de viata propriului monstru (nu poate fi folosita în Tokyo)";
    }
};

class PutereEnergie : public Carte {
public:
    PutereEnergie(const std::string& nume_, const int& cost_, const int& valoare_): Carte(nume_,cost_,valoare_) {}
    void aplicare(Monstru* m) override {
        m->adaugaFulgere(valoare);
    }
    std::string getDescriere() const override {
        return "Adauga 1 punct de victorie la finalul rundei";
    }
};


//template
template <class T>
class ContainerZaruri {
private:
    T zaruri;
public:
    void aruncaZar() {
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
        std::map<SimbolZar,std::string> simboluri {
            {SimbolZar::Punct1,"1"},
            {SimbolZar::Punct2,"2"},
            {SimbolZar::Punct3,"3"},
            {SimbolZar::Fulger,"*"},
            {SimbolZar::Inima,"H"},
            {SimbolZar::Gheara,"G"}
        };

        for(auto &z: zaruri){
            std::cout << simboluri[z] << " ";
        }
        std::cout << "\n";
    }
};

// ===== SINGLETON JOC =====
class Joc {
private:
    std::vector<Monstru*> jucatori;
    std::vector<Carte*> carti;
    int maxViata = 14;
    size_t maxMonstri = 4;
    bool tokyoOcupat = false;
    int indexTokyo = -1;
    static Joc* instance;
    Joc(){}
    ~Joc() {
        for (auto m: jucatori) { delete m;}
        jucatori.clear();
        for (auto c: carti) { delete c; }
        carti.clear();
    }
    Joc(const Joc&) = delete; //blocare copiere
    Joc& operator=(const Joc&) = delete;  // blocare asignare
    // Aplica daune in functie de cine e in Tokyo

    void aplicaDaune(Monstru* atacator, int daune){
        if(atacator->getInTokyo()){
            // atac automat: toti ceilalti jucatori
            for(auto m : jucatori){
                if(m != atacator && m->getViata() > 0){
                    int dauneActuale = daune;
                    if(Robot* r = dynamic_cast<Robot*>(m)) dauneActuale = std::max(0, dauneActuale-1);
                    if(MegaMutant* mm = dynamic_cast<MegaMutant*>(m)) dauneActuale += 2;
                    std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << m->getNume() << "\n";
                    *m -= dauneActuale;
                }
            }
        } else if(tokyoOcupat){
            // atac catre cel din Tokyo
            Monstru* inTokyo = jucatori[indexTokyo];
            int dauneActuale = daune;
            if(Robot* r = dynamic_cast<Robot*>(inTokyo)) dauneActuale = std::max(0, dauneActuale-1);
            if(MegaMutant* mm = dynamic_cast<MegaMutant*>(inTokyo)) dauneActuale += 1;
            std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << inTokyo->getNume() << "\n";
            *inTokyo -= dauneActuale;

            // intreaba daca vrea sa iasa din Tokyo
            std::cout << inTokyo->getNume() << ", vrei sa iesi din Tokyo? 1=DA, 0=NU: ";
            int opt; std::cin >> opt;
            if(opt==1){
                inTokyo->setInTokyo(false);
                tokyoOcupat = false;
                indexTokyo = -1;
            }
        } else {
            // atac clasic: alegeti pe cine sa atace
            std::vector<Monstru*> potentiali;
            for(auto m : jucatori){
                if(m != atacator && m->getViata() > 0) potentiali.push_back(m);
            }

            if(!potentiali.empty()){
                std::cout << "Alege un jucator pe care sa il ataci:\n";
                for(size_t i=0;i<potentiali.size();i++) std::cout << i+1 << ". " << potentiali[i]->getNume() << "\n";
                int opt; std::cin >> opt;
                if(opt >= 1 && opt <= (int)potentiali.size()){
                    Monstru* target = potentiali[opt-1];
                    int dauneActuale = daune;
                    if(Robot* r = dynamic_cast<Robot*>(target)) dauneActuale = std::max(0, dauneActuale-1);
                    if(MegaMutant* mm = dynamic_cast<MegaMutant*>(target)) dauneActuale += 1;

                    *target -= dauneActuale;
                    std::cout << atacator->getNume() << " aplica " << dauneActuale << " daune catre " << target->getNume() << "\n";
                }
            }
        }
    }
    // Gestioneaza intrarea in Tokyo
    void intraInTokyo(Monstru* j){
        if(!tokyoOcupat){
            std::cout << j->getNume() << ", vrei sa intri in Tokyo? 1=DA,0=NU: ";
            int opt; std::cin >> opt;
            if(opt==1){
                tokyoOcupat = true;
                indexTokyo = std::distance(jucatori.begin(), std::find(jucatori.begin(), jucatori.end(), j));
                j->setInTokyo(true);
                std::cout << j->getNume() << " a intrat in Tokyo!\n";
            }
        }
    }
    void acordaPVLaFinalRunda() {
        for(size_t i=0;i<jucatori.size();i++){
            Monstru* j=jucatori[i];
            if(j->getViata()<=0) continue;
            if(j->getInTokyo()) *j += 2; // 2 PV pentru cel din Tokyo
            else *j += 1; // 1 PV pentru ceilalti
        }
    }
    void aplicaSimboluri(Monstru* j, std::map<SimbolZar,int>& cnt){
        for(int p=1; p<=3; p++) {
            SimbolZar s = static_cast<SimbolZar>(p-1);
            int count = cnt[s];

            // Acordă PV pentru fiecare triplet
            int triplete = count / 3;
            if(triplete > 0){
                *j += triplete * p;
                count -= triplete * 3;
                std::cout << j->getNume() << " a castigat " << triplete * p << " PV pentru " << triplete << " triplete!\n";
                std::cout << *j << "\n";
            }

            // Acordă fulgere pentru restul rămase
            int rest = count % 3;
            if(rest == 2){
                j->adaugaFulgere(p);
                std::cout << j->getNume() << " a castigat " << p << " fulgere pentru dublet!\n";
            }
        }

        if(cnt[SimbolZar::Fulger] > 0) {
            int bonus = 0;
            if(Mutant* m = dynamic_cast<Mutant*>(j)) bonus += cnt[SimbolZar::Fulger]; // Mutant sau MegaMutant
            j->adaugaFulgere(cnt[SimbolZar::Fulger] + bonus);
            std::cout << j->getNume() << " castiga " << (cnt[SimbolZar::Fulger] + bonus) << " fulgere *\n";
        }

        if(!j->getInTokyo() && cnt[SimbolZar::Inima]>0){
            int heal = 1; // valoarea standard
            if(Dragon* d = dynamic_cast<Dragon*>(j)) heal += 1; // bonus Dragon
            for(int i=0;i<heal;i++) j->vindecare();
            std::cout << j->getNume() << " s-a vindecat\n";
            std::cout << *j << "\n";
        }

        if(cnt[SimbolZar::Gheara]>0){
            aplicaDaune(j, cnt[SimbolZar::Gheara]);
            // daca jucatorul nu e in Tokyo si Tokyo nu e ocupat, intra automat
            if(!j->getInTokyo() && !tokyoOcupat){
                tokyoOcupat = true;
                indexTokyo = std::distance(jucatori.begin(), std::find(jucatori.begin(), jucatori.end(), j));
                j->setInTokyo(true);

                std::cout << j->getNume() << " a intrat in Tokyo!\n";
                std::cout << *j << "\n";
            }
        }
    }
    void verificaCumparareCarte(Monstru* j) {
        if (j->getFulgere() < 4) {return;}

        std::vector<Carte*> oferte;
        oferte.push_back(new PutereAtac("PutereAtac", 4, 2));
        oferte.push_back(new PutereVindecare("PutereVindecare", 5, 2));
        oferte.push_back(new PutereEnergie("PutereEnergie", 4, 1));

        std::vector<Carte*> oferteValide;
        for(auto c : oferte) {
            if(j->getFulgere() >= c->getCost())
                oferteValide.push_back(c);
        }

        if(oferteValide.empty()) {
            std::cout << "Nu ai suficiente fulgere pentru nicio carte.\n";
            for(auto oc: oferte) delete oc;
            return;
        }

        std::cout << "Vrei sa cumperi o carte? 1=DA, 0=NU: ";
        int opt; std::cin >> opt;
        if(opt != 1) {
            for(auto oc: oferte) delete oc;
            return;
        }

        // Afișează doar cărțile valide
        std::cout << "Oferte disponibile:\n";
        for(size_t i=0; i<oferteValide.size(); ++i) {
            std::cout << i+1 << ". " << oferteValide[i]->getNume()
                      << ": " << oferteValide[i]->getDescriere()
                      << ". Costa " << oferteValide[i]->getCost() << " fulgere\n";
        }

        int alegere;
        std::cin >> alegere;

        if(alegere < 1 || alegere > (int)oferteValide.size()) {
            std::cout << "Alegere invalida!\n";
            for(auto oc: oferte) delete oc;
            return;
        }

        Carte* c = oferteValide[alegere-1];

        // verifica iar dacă are destule fulgere
        if(j->getFulgere() < c->getCost())
            throw std::runtime_error("Nu ai suficiente fulgere pentru a cumpara aceasta carte!");

        j->adaugaFulgere(-c->getCost());

        if(PutereAtac* pa = dynamic_cast<PutereAtac*>(c)) {
            if(tokyoOcupat && !j->getInTokyo()) {
                Monstru* target = jucatori[indexTokyo];
                pa->aplicare(target);
            } else if(j->getInTokyo()) {
                for(auto m: jucatori) {
                    if(m != j && m->getViata() > 0)
                        pa->aplicare(m);
                }
            }
        } else {
            c->aplicare(j);
        }

        for(auto oc: oferte) delete oc;
    }

public:
    static Joc* getInstance() { // returneaza instanta unica
        if(!instance) instance = new Joc();
        return instance;
    }
    static void deleteInstance() {
        delete instance;
        instance = nullptr;
    }
    void determinaJucatorStart() {
        std::vector<int> zaruriStart(jucatori.size(), 0);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);

        bool egalitate = true;
        std::vector<int> candidati(jucatori.size());
        std::iota(candidati.begin(), candidati.end(), 0);

        while (egalitate) {
            egalitate = false;
            int maxZar = 0;
            std::vector<int> ceiMaiBuni;

            for (int i : candidati) {
                zaruriStart[i] = dis(gen);
                std::cout << jucatori[i]->getNume() << " a aruncat zarul: " << zaruriStart[i] << "\n";
                if (zaruriStart[i] > maxZar) {
                    maxZar = zaruriStart[i];
                    ceiMaiBuni = {i};
                } else if (zaruriStart[i] == maxZar) {
                    ceiMaiBuni.push_back(i);
                }
            }

            if (ceiMaiBuni.size() > 1) {
                std::cout << "Egalitate! Se reia aruncarea pentru cei cu zar " << maxZar << "\n";
                candidati = ceiMaiBuni;
                egalitate = true;
            } else {
                // Mutam castigatorul pe primul loc in vectorul jucatori
                std::swap(jucatori[0], jucatori[ceiMaiBuni[0]]);
                std::cout << jucatori[0]->getNume() << " incepe jocul!\n";
            }
        }
    }


    void adaugaJucatori(Monstru* m) {
        if (jucatori.size() >= maxMonstri) {
            throw std::runtime_error("Maximul Jucatorilor a fost atins! ");
        }
        jucatori.push_back(m);
    }
    void afisareJucatori(){
        std::cout<<"--- Stare jucatori ---\n";
        for(size_t i=0;i<jucatori.size();i++){
            std::cout<<i+1<<". "<<*jucatori[i]<<"\n";
        }
    }

    bool JocTerminat() {
        for (auto m: jucatori) {
            if (m->getPuncteVictorie()>=8) { return true;}
        }
        int alive=0;
        for (auto m: jucatori) {
            if (m->getViata()>0){ alive++;}
        }
        return alive<=1;
    }

    void runda() {
        for(size_t i=0;i<jucatori.size();i++){
            Monstru* j = jucatori[i];
            if(j->getViata()<=0) continue;

            std::cout << "\nTura lui " << j->getNume() << " (" << j->getViata() << " viata, " << j->getPuncteVictorie() << " PV)\n";

            ContainerZaruri<std::vector<SimbolZar>> zar;
            zar.aruncaZar();
            std::cout << "Rezultat zaruri: "; zar.afisareRezultate();

            std::map<SimbolZar,int> cnt;
            for(auto z : zar.getZaruri()) cnt[z]++;

            aplicaSimboluri(j, cnt);
            verificaCumparareCarte(j); // cumpara carte daca are minim 4 fulgere
            if(!tokyoOcupat && cnt[SimbolZar::Gheara] > 0) {
                intraInTokyo(j);
            }
        }

        // La finalul rundei, acorda puncte de victorie
        for(auto m : jucatori){
            if(m->getViata() <= 0) continue;

            if(m->getInTokyo()){
                *m += 2;  // jucatorul din Tokyo primeste 2 PV
            } else {
                *m += 1;  // ceilalti jucatori primesc 1 PV
            }
        }
    }
    void afisareClasament() {
        std::sort(jucatori.begin(),jucatori.end(),[](Monstru* a, Monstru* b){ return a->getPuncteVictorie() > b->getPuncteVictorie(); });
        std::cout<<"\n=== Clasament final ===\n";
        for(size_t i = 0; i < jucatori.size(); i++) {
            std::cout << i+1 << ". " << *jucatori[i] << "\n";
        }
    }
};
Joc* Joc::instance = nullptr;

// ===== MAIN =====
int main(){
    Joc& joc = *Joc::getInstance();
    int n;
    std::cout<<"Bine ati venit la King of Tokyo!\n";
    do{
        std::cout<<"Numar jucatori (2-4): "; std::cin>>n;
    }while(n<2 || n>4);

    // Alegere monstri
    for(int i=0;i<n;i++){
        std::cout<<"Jucator "<<i+1<<": Alege monstru:\n1. Mutant\n2. Dragon\n3. Robot\n4. MegaMutant\nOptiune: ";
        int t; std::cin>>t; std::string nume;
        std::cout<<"Nume jucator: "; std::cin>>nume;
        Monstru* m = MonstruFactory::creeazaMonstru(t,nume);
        joc.adaugaJucatori(m);
    }
    joc.determinaJucatorStart();

    // Rulari runde
    bool stop=false;
    int runda=1;
    while(!stop && !joc.JocTerminat()){
        std::cout<<"\n=== Runda "<<runda<<" ===\n";
        joc.runda();
        std::cout<<"Vrei sa inchei jocul acum? 1=DA,0=NU: "; int opt; std::cin>>opt;
        if(opt==1) stop=true;
        joc.afisareJucatori();
        runda++;
    }

    joc.afisareClasament();
    std::cout<<"Joc incheiat!\n";
    Joc::deleteInstance();
    return 0;
}





