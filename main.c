#include "EstruturasDeDados/headers/processoSimulado.h"


int main(){
    Processo p;
    char path[40];
    sprintf(path, "assets/processoS01.txt");
    lerInstrucoes(&p, path);
    return 0;
}
