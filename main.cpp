#include "Joc.h"
#include "Monstru.h"
#include "Carte.h"
#include "Joc.h"


int main(){
    try {
        Joc& joc = *Joc::getInstance();
        joc.setupJoc();
        joc.desfasurareJoc();
        Joc::deleteInstance();
    } catch (const std::exception& e) {
        std::cout << "A aparut o eroare: " << e.what() << "\n";
    }
    return 0;
}





