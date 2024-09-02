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
#include "disco.h"

#include "unistd.h"

#define FILA_DE_PRIORIDADE 1
#define ROUND_ROBIN 2
#define FIRSTFIT 1
#define NEXTFIT 2
#define BESTFIT 3
#define WORSTFIT 4

// Filas de Prioridade para o escalonador
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
    int movimentosParaODisco;           // Número de Vezes que um processo precisou ser levado para o disco
    int numeroNosPercorridos;           // Numero de posições percorridas durante as alocações de memória
    int numeroAlocacoes;
} GerenciadorProcesso;

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador, Memoria *memoria, Disco *disco, int tecnicaAlocacao);
void init(Processo *processoSimulado, char *path, int *IDS);
void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria, Disco *disco, int tecnicaAlocacao);
void instrucaoN(GerenciadorProcesso *gerenciadorProcesso, int n, int cpuAtual, Memoria *memoria, Disco *disco, int tecnicaAlocacao);
void instrucaoD(GerenciadorProcesso *gerenciadorProcesso, int x, Memoria *memoria, Disco *disco, int cpuAtual);
void instrucaoV(GerenciadorProcesso *gerenciadorProcesso, int x, int n, Memoria *memoria, Disco *disco, int cpuAtual);
void instrucaoA(GerenciadorProcesso *gerenciadorProcesso, int x, int n, Memoria *memoria, Disco *disco, int cpuAtual);
void instrucaoS(GerenciadorProcesso *gerenciadorProcesso, int x, int n, Memoria *memoria, Disco *disco, int cpuAtual);
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria, Disco *disco, int tecnicaAlocacao);
void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual, Memoria *memoria, Disco *disco);
void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual, Memoria *memoria);
void desbloqueiaProcessos(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade);
void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso, int cpuAtual);
int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria);
void enfileiraFilaDePrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int idProcesso);
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu, GerenciadorProcesso *gerenciadorProcesso);
void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual, Memoria *memoria);

#endif
