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

typedef struct gerenciadorProcesso{
    int Tempo;
    CPU Cpu;
    TabelaDeProcessos tabelaProcessos;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
} GerenciadorProcesso;

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso);
void init(Processo *processoSimulado, char *path, int *IDS);
void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS);
void instrucaoN(CPU *cpu, int n);
void instrucaoD(CPU *cpu, int x);
void instrucaoV(CPU *cpu, int x, int n);
void instrucaoA(CPU *cpu, int x, int n);
void instrucaoS(CPU *cpu, int x, int n);
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n);
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso);
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS);
void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS);
void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado);


#endif
