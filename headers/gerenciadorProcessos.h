#ifndef GERENCIADORPROCESSOS_H
#define GERENCIADORPROCESSOS_H
#include "cpu.h"
#include "EstadoBloqueado.h"
#include "EstadoExecucao.h"
#include "EstadoPronto.h"
#include "tabelaDeProcessos.h"
#include "../../ProcessoSimulado/headers/processoSimulado.h"

typedef struct gerenciadorProcesso{
    int Tempo;
    CPU Cpu;
    TabelaDeProcessos tabelaProcessos;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
} GerenciadorProcesso;

void gerenciarProcesso();
void init(Processo *processoSimulado);
void executaIntrucao(Processo *processoSimulado, char *linhaDeInstrucao);



#endif