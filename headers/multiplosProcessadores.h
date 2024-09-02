#ifndef MULTIPLOSPROCESSADORES_H
#define MULTIPLOSPROCESSADORES_H

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vetorCPUS{
    CPU *processadores;                 // Vetor contendo vários CPUS
    int ultimaCpuUsada;                 // A última CPU utilizado pelo sistema
    int numeroDeProcessadores;          // Número de processadores especificado pelo usuário
    int cpusSendoUtilizadas;            // Número de CPUS sendo utilizadas atualmente.
} VetorCPUS;

int selecionaCPU(VetorCPUS *vetorCPUS);

#endif