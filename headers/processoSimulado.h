#ifndef PROCESSOSIMULADO_H
#define PROCESSOSIMULADO_H

#define TAM_INST 40 //tamanho maximo da linha de instrucao

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal_format.h"

typedef enum Estados_de_processos{
    BLOQUEADO,
    PRONTO,
    EM_EXECUCAO
}Estado;

typedef struct processo{
    int idProcesso;
    int idProcessoPai;
    int programCounter;
    int prioridade;
    Estado estado;
    int inicioTempo;
    int tempoUsadoCPU;
    int *memoriaDoProcesso; //simula a memoria do processo simulado, eh feito um malloc com a instrucao N
    int tempoBloqueado; // O Gerenciador de processos ira diminuir esse int a cada unidade de tempo, quando o valor chegar a 0 significará que o processo deve ir para o estado pronto.
    char** vetorPrograma;
    int tamanhoMemoriaDoProcesso;
}Processo;

void lerInstrucoes(Processo *processo, char *pathProcesso);

#endif
