#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#define INIT "Documentos/init"

#include "cpu.h"
#include "EstadoBloqueado.h"
#include "EstadoExecucao.h"
#include "EstadoPronto.h"
#include "tabelaDeProcessos.h"
#include "processoSimulado.h"
#include "pipe.h"

#include "unistd.h"

#define FILA_DE_PRIORIDADE 1
#define ROUND_ROBIN 2

typedef struct filasDePrioridade{
	TFila prioridade0;
	TFila prioridade1;
	TFila prioridade2;
    TFila prioridade3;
}FilasDePrioridade;

typedef struct gerenciadorProcesso{
    int Tempo;
    CPU Cpu;
    TabelaDeProcessos tabelaProcessos;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
} GerenciadorProcesso;

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador);
void init(Processo *processoSimulado, char *path, int *IDS);
void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador);
void instrucaoN(CPU *cpu, int n);
void instrucaoD(CPU *cpu, int x);
void instrucaoV(CPU *cpu, int x, int n);
void instrucaoA(CPU *cpu, int x, int n);
void instrucaoS(CPU *cpu, int x, int n);
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador);
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador);
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador);
void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador);
void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado);
int escalonadorPrioridade(GerenciadorProcesso *gerenciadorProcesso);
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu);
void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso,Processo *processo, int escalonador);

#endif
