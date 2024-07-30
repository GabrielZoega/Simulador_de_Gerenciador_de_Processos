#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H

#define INIT "../Documentos/init"

#include "cpu.h"
#include "EstadoBloqueado.h"
#include "EstadoExecucao.h"
#include "EstadoPronto.h"
#include "tabelaDeProcessos.h"
#include "processoSimulado.h"
#include "pipe.h"

#include "unistd.h"

typedef struct gerenciadorProcesso{
    int Tempo;
    CPU Cpu;
    TabelaDeProcessos tabelaProcessos;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
} GerenciadorProcesso;

void gerenciarProcesso(int *fd);
void init(Processo *processoSimulado);
void executaIntrucao(Processo *processoSimulado, char *linhaDeInstrucao);

#endif