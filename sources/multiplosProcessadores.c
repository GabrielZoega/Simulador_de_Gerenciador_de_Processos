#include "../headers/multiplosProcessadores.h"

int selecionaCPU(VetorCPUS *vetorCPUS){
    if (vetorCPUS->ultimaCpuUsada == vetorCPUS->numeroDeProcessadores){
        return 0;
    }
    else{
        return vetorCPUS->ultimaCpuUsada + 1;
    }
    return -1;
}