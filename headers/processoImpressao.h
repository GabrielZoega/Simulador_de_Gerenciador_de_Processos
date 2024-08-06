#include "gerenciadorProcessos.h"

//Funções para a impressão
void MenuImpressao(GerenciadorProcesso *gerenciadorProcesso);
void ApresentarTudo(GerenciadorProcesso *gerenciadorProcesso);
void ImprimeCPU(CPU *cpu);
void ImprimeMemoriaSimuladaCPU(CPU *cpu);
void ImpressaoProcesso(Processo *processo);
void ImpressaoProcessoEstado(Estado estadoprocesso);
void ImpressaoEstadosBloqueados(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoEstadosProntos(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoEstadosExecucao(GerenciadorProcesso *gerenciadorProcesso);
void ImpressaoTabelaDeProcessos(GerenciadorProcesso *gerenciadorProcesso);
