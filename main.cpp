#include "Joc.h"
#include "Monstru.h"
#include "Carte.h"
#include "Joc.h"


int main(){
    Joc& joc = *Joc::getInstance();
    joc.setupJoc();
    joc.desfasurareJoc();
    Joc::deleteInstance();
    return 0;
}





