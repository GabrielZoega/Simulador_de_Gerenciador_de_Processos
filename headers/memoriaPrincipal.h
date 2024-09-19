#ifndef MEMORIAPRINCIPAL_H
#define MEMORIAPRINCIPAL_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct segmento {
    int inicioNaMemoria;                                    // Posição de inicio do processo na memória
    int idProcessoMemoria;                                  // id do processo "dono" desse segmento
    int tamanhoMemoriaProcesso;                             // Tamanho da memória ocupada pelo processo
} SegmentoProcesso;

typedef struct memoriaPrincipal{
    SegmentoProcesso *segmentos;                     // Vetor contendo os segmentos (mesmo tamanho da memória RAM pois podemos ter vários segmentos de tamanho 1)
    int *vetorMemoria;                               // Representação da memória principal usada pelos processos
    int tamanhoMemoria;
} MemoriaRAM;

void iniciaMemoria(MemoriaRAM *memoria);
SegmentoProcesso retornaSegmento(MemoriaRAM memoria, int idProcesso);

#endif