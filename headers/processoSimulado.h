#ifndef PROCESSOSIMULADO_H
#define PROCESSOSIMULADO_H

#define TAM_INST 40 //tamanho maximo da linha de instrucao

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}Processo;

void instrucaoN(Processo *processo, int n);
void instrucaoD(Processo *processo, int x);
void instrucaoV(Processo *processo, int x, int n);
void instrucaoA(Processo *processo, int x, int n);
void instrucaoS(Processo *processo, int x, int n);
void instrucaoB(Processo *processo, int n);
void instrucaoT(Processo *processo);
void instrucaoF(Processo *processo, int n);
void instrucaoR(Processo *processo, char *nome_do_arquivo);

void lerInstrucoes(Processo *processo, char *pathProcesso);

#endif