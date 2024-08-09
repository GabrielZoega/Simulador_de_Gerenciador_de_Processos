#ifndef MULTIPLOSPROCESSADORES_H
#define MULTIPLOSPROCESSADORES_H

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vetorCPUS{
    CPU *processadores;
    int ultimaCpuUsada;
    int numeroDeProcessadores;
    int cpusSendoUtilizadas;
} VetorCPUS;

int selecionaCPU(VetorCPUS *vetorCPUS);

#endif