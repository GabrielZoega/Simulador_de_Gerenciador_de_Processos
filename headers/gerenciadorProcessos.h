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
#include "multiplosProcessadores.h"

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
    VetorCPUS vetorCPUS;
    TabelaDeProcessos tabelaProcessos;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
} GerenciadorProcesso;

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador);
void init(Processo *processoSimulado, char *path, int *IDS);
void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
void instrucaoN(CPU *cpu, int n);
void instrucaoD(CPU *cpu, int x);
void instrucaoV(CPU *cpu, int x, int n);
void instrucaoA(CPU *cpu, int x, int n);
void instrucaoS(CPU *cpu, int x, int n);
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual);
void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual);
void desbloqueiaProcessos(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade);
void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso, int cpuAtual);
int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual);
void enfileiraFilaDePrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int idProcesso);
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu, GerenciadorProcesso *gerenciadorProcesso);
void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual);

#endif
