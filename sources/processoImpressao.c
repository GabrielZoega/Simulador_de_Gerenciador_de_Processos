#include "../headers/processoImpressao.h"
#include "../headers/fila.h"

//Funções para a impressão

void ApresentarTudo(GerenciadorProcesso *gerenciadorProcesso, Memoria *memoria, int numeroFragmentosExternos){
	system("clear");
    printf("\n\n" INICIO2 "╒══════════════════════════════════════════════════════╡ ESTADO DO SISTEMA ╞════════════════════════════════════════════════════════╕" FINAL "\n\n", BOLD, FUNDO_AZUL);
    printf(INICIO2 "Tempo de uso do sistema no momento atual:" FINAL" %d unidades de tempo", BOLD, UNDERLINE, gerenciadorProcesso->Tempo);
    printf("\n\n" INICIO3 "Processos em estado bloqueado:" FINAL "\n", BOLD, UNDERLINE, FUNDO_VERMELHO);
    ImpressaoEstadosBloqueados(gerenciadorProcesso);
    printf("\n\n" INICIO3 "Processos em estado pronto:" FINAL "\n", BOLD, UNDERLINE, FUNDO_VERDE);
    ImpressaoEstadosProntos(gerenciadorProcesso);
    printf("\n\n" INICIO3 "Processos em estado de execução:" FINAL "\n", BOLD, UNDERLINE, FUNDO_AMARELO);
    ImpressaoEstadosExecucao(gerenciadorProcesso);
	for (int i = 0; i < gerenciadorProcesso->vetorCPUS.numeroDeProcessadores; ++i) {
		ImprimeCPU(&(gerenciadorProcesso->vetorCPUS.processadores[i]));

	}
    ImpressaoTabelaDeProcessos(gerenciadorProcesso);
    ImprimeMemoriaSimuladaCPU(memoria);
    printf("\n\n" INICIO3 "Numero medio de fragmentos externos: %.2f" FINAL "\n", BOLD, UNDERLINE, VERDE, ((float)numeroFragmentosExternos)/((float)gerenciadorProcesso->Tempo));
    printf("\n\n" INICIO3 "Tempo medio de alocacao: %.2f" FINAL "\n", BOLD, UNDERLINE, AZUL, ((float)gerenciadorProcesso->numeroNosPercorridos)/((float)gerenciadorProcesso->numeroAlocacoes));
    printf("\n\n" INICIO3 "Vezes que um processo teve que ser levado para o \"disco\": %d" FINAL "\n", BOLD, UNDERLINE, AMARELO, gerenciadorProcesso->movimentosParaODisco);

}
void ImpressaoEstadosBloqueados(GerenciadorProcesso *gerenciadorProcesso){
	ImprimeFila(&(gerenciadorProcesso->estadoBloqueado.processosB));
}

void ImpressaoEstadosProntos(GerenciadorProcesso *gerenciadorProcesso){
	ImprimeFila(&(gerenciadorProcesso->estadoPronto.processosP));
}

void ImpressaoEstadosExecucao(GerenciadorProcesso *gerenciadorProcesso){
	for (int i = 0; i < gerenciadorProcesso->vetorCPUS.numeroDeProcessadores; ++i) {
		if(gerenciadorProcesso->estadoExecucao.processoExec[i] >= 0)
			printf("pid: %d\n", gerenciadorProcesso->estadoExecucao.processoExec[i]);
	}
}
//
void ImpressaoProcessoEstado(Estado estadoprocesso){
    switch (estadoprocesso)
    {
    case BLOQUEADO:
        printf(INICIO2 "Estado => BLOQUEADO " FINAL "\n\n", BOLD, VERMELHO);
        break;
    case PRONTO:
        printf(INICIO2 "Estado => PRONTO " FINAL "\n\n", BOLD, VERDE);
        break;
    case EM_EXECUCAO:
        printf(INICIO2 "Estado => EM EXECUÇÃO" FINAL "\n\n", BOLD, AMARELO);
        break;
    }
}

void ImpressaoProcesso(Processo *processo){
	if (processo->idProcesso >= 0) {
		printf("\n\n" INICIO2 "******************* Processo => %d *********************"  FINAL "\n\n", BOLD, INVERTIDO, processo->idProcesso);
		printf(INICIO2 "ID processo => %d"  FINAL "\n\n", BOLD, FUNDO_AMARELO, processo->idProcesso);
		printf(INICIO2 "ID processo pai => %d" FINAL "\n\n", BOLD, FUNDO_AZUL, processo->idProcessoPai);
		printf(INICIO2 "PC => %d" FINAL "\n\n", BOLD, FUNDO_ROXO, processo->programCounter);
		printf(INICIO2 "Prioridade => %d" FINAL "\n\n", BOLD, FUNDO_VERDE_AGUA, processo->prioridade);
		ImpressaoProcessoEstado(processo->estado);
		printf(INICIO2 "Tempo de início => %d" FINAL "\n\n", BOLD, FUNDO_VERDE, processo->inicioTempo);
		printf(INICIO2 "Tempo de CPU => %d" FINAL "\n\n", BOLD, FUNDO_VERMELHO, processo->tempoUsadoCPU);
	}
}

void ImprimeMemoriaSimuladaCPU(Memoria *memoria){
    printf(INICIO2 "Conteúdo da memória simulada:" FINAL "\n", BOLD, FUNDO_VERDE_AGUA);
    for(int i = 0; i < memoria->tamanho ; i++){
        if(memoria->vetorMemoria[i] == INT_MIN) printf( "\t"INICIO2 "[%d] => VAZIO" FINAL "\n", BOLD, VERDE_AGUA, i);
        else printf( "\t"INICIO2 "[%d] => %d" FINAL "\n", BOLD, VERDE_AGUA, i, memoria->vetorMemoria[i]);
    }
}

void ImprimeCPU(CPU *cpu){
    printf("\n\n" INICIO2 ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" FINAL "\n\n", BOLD, FUNDO_VERDE);
    if(cpu->cpuOcupada == OCUPADA){
		printf(INICIO2 "PC => %d" FINAL "\n\n", BOLD, FUNDO_ROXO, cpu->PC_Atual);
		printf(INICIO2 "Id Processo Atual => %d" FINAL "\n\n", BOLD, FUNDO_AMARELO, cpu->idprocesso);
		printf(INICIO2 "Fatia de Quantum => %d" FINAL "\n\n", BOLD, FUNDO_VERMELHO, cpu->FatiaQuantum);
		//if(cpu->MemoriaSimulada != NULL) ImprimeMemoriaSimuladaCPU(cpu);
    }else{
    	printf("Ociosa.\n");
    }
}

void ImpressaoTabelaDeProcessos(GerenciadorProcesso *gerenciadorProcesso){
    printf("\n\n" INICIO2 ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TABELA DE PROCESSOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" FINAL "\n", BOLD, FUNDO_ROXO);
    for(int i = 0; i < 5; i++){
        ImpressaoProcesso(&(gerenciadorProcesso->tabelaProcessos.processos[i]));
    }
}
void Asteriscos(int cor){
    printf("\n" INICIO2 "*********************************************************************************************************************************" FINAL "\n\n", BOLD, cor);
}