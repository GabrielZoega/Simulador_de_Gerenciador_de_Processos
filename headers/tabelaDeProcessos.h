#ifndef TABELADEPROCESSOS_H
#define TABELADEPROCESSOS_H

#include <stdio.h>
#include <stdlib.h>
#include "processoSimulado.h"

// A tabela de Processos é um vetor de Processos
typedef struct tabelaDeProcessos {
    Processo processos[50];
    int quantidadeDeProcessos;
}TabelaDeProcessos;

void iniciaTabela(TabelaDeProcessos *tabelaDeProcessos);

#endif