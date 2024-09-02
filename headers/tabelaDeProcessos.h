#ifndef TABELADEPROCESSOS_H
#define TABELADEPROCESSOS_H

#include <stdio.h>
#include <stdlib.h>
#include "processoSimulado.h"
#include "disco.h"

// A tabela de Processos será um vetor do tipo processo
typedef struct tabelaDeProcessos {
    Processo processos[50];
    int quantidadeDeProcessos;
}TabelaDeProcessos;

void retiraProcessosDaMemoria(Disco *disco, Memoria *memoria, TabelaDeProcessos *tabelaDeProcessos, int tamanhoParaRetirar, int *movimentosParaODisco);
VetorSegmentos getSegmentosOcupados(Memoria memoria, TabelaDeProcessos tabelaDeProcessos);

#endif