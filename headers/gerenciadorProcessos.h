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
#include "memoriaPrincipalBase.h"

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

// Declarações Antigas
// void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador);
// void init(Processo *processoSimulado, char *path, int *IDS);
// void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
// void instrucaoN(CPU *cpu, int n);
// void instrucaoD(CPU *cpu, int x);
// void instrucaoV(CPU *cpu, int x, int n);
// void instrucaoA(CPU *cpu, int x, int n);
// void instrucaoS(CPU *cpu, int x, int n);
// void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
// void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
// void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual);
// void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual);
// void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual);
// void desbloqueiaProcessos(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade);
// void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso, int cpuAtual);
// int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual);
// void enfileiraFilaDePrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int idProcesso);
// int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu, GerenciadorProcesso *gerenciadorProcesso);
// void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual);

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador, Memoria *memoria, int tecnicaAlocacao);
void init(Processo *processoSimulado, char *path, int *IDS);
void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoN(GerenciadorProcesso *gerenciadorProcesso, int n, int cpuAtual, Memoria *memoria);
void instrucaoD(CPU *cpu, int x, Memoria *memoria);
void instrucaoV(CPU *cpu, int x, int n, Memoria *memoria);
void instrucaoA(CPU *cpu, int x, int n, Memoria *memoria);
void instrucaoS(CPU *cpu, int x, int n, Memoria *memoria);
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual, Memoria *memoria);
void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual, Memoria *memoria);
void desbloqueiaProcessos(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade);
void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso, int cpuAtual);
int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void enfileiraFilaDePrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int idProcesso);
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu, GerenciadorProcesso *gerenciadorProcesso);
void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual, Memoria *memoria);
VetorSegmentos getSegmentosOcupados(Memoria memoria, TabelaDeProcessos tabelaDeProcessos);

#endif
