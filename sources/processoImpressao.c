#include "../headers/processoImpressao.h"

//Funções para a impressão

void MenuImpressao(GerenciadorProcesso *gerenciadorProcesso){
    //Ideia para o Menu - Tentar engoblar todos os campos definidos
    int opcao = 0;
    printf(INICIO2 "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU DE IMPRESSAO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" FINAL, BOLD, VERMELHO);
    printf(INICIO1 "1 - Apresentar Tudo\n", BOLD);
    printf("2 - Tempo de uso atual do sistema\n");
    printf("3 - Processos em estado bloqueado\n");
    printf("4 - Processos em estado pronto\n");
    printf("5 - Processos em estado de execução\n");
    printf("6 - Informações sobre a CPU no momento atual\n");
    printf("7 - Tabela de Processos atual\n");
    printf("8 - Sair da impressão\n" FINAL);
    printf(INICIO2 "================================================================================================================================\n" FINAL, BOLD, VERMELHO);
    printf(INICIO2 "Escolha uma opção:" FINAL " ", BOLD, UNDERLINE);
    scanf("%d",&opcao);
    
    if(opcao==1){
        ApresentarTudo(gerenciadorProcesso);
    }else if(opcao==2){
        
        printf(INICIO2 "\n\nTempo de uso do sistema no momento atual:" FINAL " %d unidades de tempo\n", BOLD, UNDERLINE, gerenciadorProcesso->Tempo);

    }else if(opcao==3){

        ImpressaoEstadosBloqueados(gerenciadorProcesso);

    }else if(opcao==4){

        ImpressaoEstadosProntos(gerenciadorProcesso);

    }else if(opcao==5){

        ImpressaoEstadosExecucao(gerenciadorProcesso);

    }else if(opcao==6){

        ImprimeCPU(&(gerenciadorProcesso)->Cpu);

    }else if(opcao==7){

        ImpressaoTabelaDeProcessos(gerenciadorProcesso); 
    }
}
//

void ApresentarTudo(GerenciadorProcesso *gerenciadorProcesso){
    printf("\n\n" INICIO2 "╒══════════════════════════════════════════════════════╡ ESTADO DO SISTEMA ╞════════════════════════════════════════════════════════╕" FINAL "\n\n", BOLD, FUNDO_AZUL); 
    printf(INICIO2 "Tempo de uso do sistema no momento atual:" FINAL" %d unidades de tempo", BOLD, UNDERLINE, gerenciadorProcesso->Tempo);
    printf("\n\n" INICIO3 "Processos em estado bloqueado:" FINAL "\n", BOLD, UNDERLINE, FUNDO_VERMELHO);
    ImpressaoEstadosBloqueados(gerenciadorProcesso);
    printf("\n\n" INICIO3 "Processos em estado pronto:" FINAL "\n", BOLD, UNDERLINE, FUNDO_VERDE);
    ImpressaoEstadosProntos(gerenciadorProcesso);
    printf("\n\n" INICIO3 "Processos em estado de execução:" FINAL "\n", BOLD, UNDERLINE, FUNDO_AMARELO);
    ImpressaoEstadosExecucao(gerenciadorProcesso);
    ImprimeCPU(&(gerenciadorProcesso)->Cpu);
    ImpressaoTabelaDeProcessos(gerenciadorProcesso);

}
void ImpressaoEstadosBloqueados(GerenciadorProcesso *gerenciadorProcesso){
   ImprimeFila(&(gerenciadorProcesso->estadoBloqueado.processosB));
}

void ImpressaoEstadosProntos(GerenciadorProcesso *gerenciadorProcesso){
    ImprimeFila(&(gerenciadorProcesso->estadoPronto.processosP));
}

void ImpressaoEstadosExecucao(GerenciadorProcesso *gerenciadorProcesso){
    printf("%d", gerenciadorProcesso->estadoExecucao.processoExec);
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
    printf("\n\n" INICIO2 "******************* Processo => %d *********************"  FINAL "\n\n", BOLD, INVERTIDO, processo->idProcesso);
    printf(INICIO2 "ID processo => %d"  FINAL "\n\n", BOLD, FUNDO_AMARELO, processo->idProcesso);
    printf(INICIO2 "ID processo pai => %d" FINAL "\n\n", BOLD, FUNDO_AZUL, processo->idProcessoPai);
    printf(INICIO2 "PC => %d" FINAL "\n\n", BOLD, FUNDO_ROXO, processo->programCounter);
    printf(INICIO2 "Prioridade => %d" FINAL "\n\n", BOLD, FUNDO_VERDE_AGUA, processo->prioridade);
    ImpressaoProcessoEstado(processo->estado);
    printf(INICIO2 "Tempo de início => %d" FINAL "\n\n", BOLD, FUNDO_VERDE, processo->inicioTempo);
    printf(INICIO2 "Tempo de CPU => %d" FINAL "\n\n", BOLD, FUNDO_VERMELHO, processo->tempoUsadoCPU);
}

void ImprimeMemoriaSimuladaCPU(CPU *cpu){
    printf(INICIO2 "Conteúdo da memória simulada:" FINAL "\n", BOLD, FUNDO_VERDE_AGUA);
    for(int i = 0; i < cpu->tamanhoMemoriaSimulada ; i++){
        printf( "\t"INICIO2 "[%d] => %d" FINAL "\n", BOLD, VERDE_AGUA, i, cpu->MemoriaSimulada[i]);
    }
}

void ImprimeCPU(CPU *cpu){
    printf("\n\n" INICIO2 ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" FINAL "\n\n", BOLD, FUNDO_VERDE);
    printf(INICIO2 "PC => %d" FINAL "\n\n", BOLD, FUNDO_ROXO, cpu->PC_Atual);
    printf(INICIO2 "Id Processo Atual => %d" FINAL "\n\n", BOLD, FUNDO_AMARELO, cpu->idprocesso);
    printf(INICIO2 "Fatia de Quantum => %d" FINAL "\n\n", BOLD, FUNDO_VERMELHO, cpu->FatiaQuantum);
    ImprimeMemoriaSimuladaCPU(cpu);
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
        