#ifndef ESTADOEXECUCAO_H
#define ESTADOEXECUCAO_H

#include "stdlib.h"
#include "stdio.h"

// Vetor com os ids dos processos em Execução
typedef struct EstadoExecucao {
    int *processoExec;
} EstadoExecucao;

#endif