#ifndef MULTIPLASCPUS_H
#define MULTIPLASCPUS_H
#include "cpu.h"

typedef struct processadores{
    CPU *CPUs;
    int ultimaCpuUsada;                 // ultima CPU usada pelo sistema
    int numCpus;                        // Número de CPUs definido pelo usuário
    int cpusSendoUtilizadas;            // Número de CPUs em uso no tempo atual
} Processadores;

int selecionaCPU(Processadores processadores);

#endif