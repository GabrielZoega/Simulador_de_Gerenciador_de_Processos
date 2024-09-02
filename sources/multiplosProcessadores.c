#include "../headers/multiplosProcessadores.h"

// Com base na Última CPU Usada itera as CPUS (troca de um em um)
int selecionaCPU(VetorCPUS *vetorCPUS){
    if (vetorCPUS->ultimaCpuUsada == (vetorCPUS->numeroDeProcessadores - 1)){
        vetorCPUS->processadores[0].cpuOcupada = OCUPADA;
        return 0;
    }
    else{
        vetorCPUS->processadores[vetorCPUS->ultimaCpuUsada + 1].cpuOcupada = OCUPADA; 
        return vetorCPUS->ultimaCpuUsada + 1;
    }
    return -1;
}