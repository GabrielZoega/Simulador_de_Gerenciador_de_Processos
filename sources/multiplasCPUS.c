#include "../headers/multiplasCPUS.h"

int selecionaCPU(Processadores processadores){
    if(processadores.ultimaCpuUsada == (processadores.numCpus - 1))
        return 0;
    else
        return processadores.ultimaCpuUsada + 1;
}
