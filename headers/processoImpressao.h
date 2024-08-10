#ifndef PROCESSOIMPRESSAO_H
#define PROCESSOIMPRESSAO_H

#include "gerenciadorProcessos.h"
#include "terminal_format.h"

//Funções para a impressão
void ApresentarTudo(GerenciadorProcesso *gerenciadorProcesso);
void ImprimeCPU(CPU *cpu);
void ImprimeMemoriaSimuladaCPU(CPU *cpu);
void ImpressaoProcesso(Processo *processo);
void ImpressaoProcessoEstado(Estado estadoprocesso);
void ImpressaoEstadosBloqueados(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoEstadosProntos(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoEstadosExecucao(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoTabelaDeProcessos(GerenciadorProcesso *gerenciadorProcesso);
void Asteriscos(int cor);
//Funções para a impressão

#endif
