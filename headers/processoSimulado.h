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
    int idProcessoPai;              // id do processo pai (caso não tenha um pai, o id é -1)
    int programCounter;
    int prioridade;                 // Prioridade atual do processo
    Estado estado;                  // Estado atual do processo (Pronto, Em execução e Bloqueado)  
    int inicioTempo;                // Momento em que o processo foi alocado na CPU 
    int tempoUsadoCPU;              // Tempo de CPU usado até então
    int *memoriaDoProcesso;         //simula a memoria do processo simulado, eh feito um malloc com a instrucao N
    int tempoBloqueado;             // O Gerenciador de processos ira diminuir esse int a cada unidade de tempo, quando o valor chegar a 0 significará que o processo deve ir para o estado pronto.
    char** vetorPrograma;           // Vetor contendo as instruções do processo
    int tamanhoMemoriaDoProcesso;
    int inicioMemoria;              // Endereço inicial do processo na memória principal
    int inicioDisco;                // Endereço inicial do processo no disco
    int tempoUltimoAcessoAMemoria;  // Tempo no qual a memória do processo foi acessada pela ultima vez
    int estaNaMemoria;              // indica se um processo está na memória (0 pra não e 1 pra sim)
}Processo;

void lerInstrucoes(Processo *processo, char *pathProcesso);

#endif
