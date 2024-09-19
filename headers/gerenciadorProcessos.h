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
#include "memoriaPrincipal.h"
#include "multiplasCPUS.h"

#define FILA_DE_PRIORIDADE 1
#define ROUND_ROBIN 2
#define FIRSTFIT 1
#define NEXTFIT 2
#define BESTFIT 3
#define WORSTFIT 4

typedef struct filasDePrioridade{
    TFila prioridade0;
    TFila prioridade1;
    TFila prioridade2;
    TFila prioridade3;
} FilasDePrioridade;


typedef struct gerenciadorProcesso{
    int tempo;                                      // Tempo do sistema
    Processadores processadores;                             // Vetor contendo as CPUS do sistema
    TabelaDeProcessos tabelaDeProcessos;            // Tabela de Processos contendo os processos ainda em execução
    EstadoPronto estadoPronto;                      // Fila dos processos prontos para execução
    EstadoBloqueado estadoBloqueado;                // Fila dos processos bloqueados pelo sistema
    EstadoExecucao estadoExecucao;                  // Lista dos processos em execução no tempo atual
} GerenciadorProcesso;

void init(Processo *processoSimulado, char *path, int *ids, int tempo);

#endif