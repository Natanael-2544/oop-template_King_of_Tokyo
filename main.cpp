#include "Joc.h"


int main(){
    Joc& joc = *Joc::getInstance();
    joc.setupJoc();
    joc.desfasurareJoc();
    Joc::deleteInstance();
    return 0;
}





