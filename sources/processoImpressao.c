#include "../headers/processoImpressao.h"

//Funções para a impressão

void MenuImpressao(GerenciadorProcesso *gerenciadorProcesso){
    //Ideia para o Menu - Tentar engoblar todos os campos definidos
    int opcao = 0;
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU DE IMPRESSAO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    printf("1 - Apresentar Tudo\n");
    printf("2 - Tempo de uso atual do sistema\n");
    printf("3 - Processos em estado bloqueado\n");
    printf("4 - Processos em estado pronto\n");
    printf("5 - Processos em estado de execução\n");
    printf("6 - Informações sobre a CPU no momento atual\n");
    printf("7 - Tabela de Processos atual\n");
    printf("8 - Sair da impressão\n");
    printf("=============================================================\n");
    printf("Escolha uma opção: ");
    scanf("%d",&opcao);
    while(opcao!=8){
        if(opcao==1){
            ApresentarTudo(gerenciadorProcesso);
        }else if(opcao==2){
            
            printf("\n\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciadorProcesso->Tempo);

        }else if(opcao==3){

            ImpressaoEstados(gerenciadorProcesso);
    
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
}
//

void ApresentarTudo(GerenciadorProcesso *gerenciadorProcesso){
    printf("\n╒══════════════════════════════════════════════════════╡ ESTADO DO SISTEMA ╞════════════════════════════════════════════════════════╕"); 
    printf("\nTempo de uso do sistema no momento atual: %d unidades de tempo",gerenciadorProcesso->Tempo);
    printf("\n\nProcessos em estado bloqueado:\n");
    ImpressaoEstadosBloqueados(gerenciadorProcesso);
    printf("\n\nProcessos em estado pronto:\n");
    ImpressaoEstadosProntos(gerenciadorProcesso);
    printf("\n\nProcessos em estado de execução:\n");
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
    ImprimeFila(&(gerenciadorProcesso->estadoExecucao.processoExec));
}
//
void ImpressaoProcessoEstado(Estado estadoprocesso){
    switch (estadoprocesso)
    {
    case BLOQUEADO:
        printf("Estado => BLOQUEADO ");
        break;
    case PRONTO:
        printf("Estado => PRONTO ");
        break;
    case EM_EXECUCAO:
        printf("Estado => EM EXECUÇÃO");
        break;
    }
}

void ImpressaoProcesso(Processo *processo){
    printf("ID processo => %d\n",processo->idProcesso);
    printf("ID processo pai => %d\n",processo->idProcessoPai);
    printf("PC => %d\n",processo->programCounter);
    printf("Prioridad => %d\n",processo->prioridade);
    ImpressaoEstadosProntos(processo->estado);
    printf("Tempo de início => %d\n",processo->inicioTempo);
    printf("Tempo de CPU => %d\n",processo->tempoUsadoCPU);
}

void ImprimeMemoriaSimuladaCPU(CPU *cpu){
    printf("Conteúdo da memória simulada ==> \n");
    for(int i = 0; i < cpu->tamanhoMemoriaSimulada ; i++){
        printf("[%d] => %d",i,cpu->MemoriaSimulada[i]);
    }
}

void ImprimeCPU(CPU *cpu){
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("PC => %d\n", cpu->PC_Atual);
    printf("Id Processo Atual => %d\n", cpu->idprocesso);
    printf("Fatia de Quantum => %d\n", cpu->FatiaQuantum);
    ImprimeMemoriaSimuladaCPU(cpu);
}

void ImpressaoTabelaDeProcessos(GerenciadorProcesso *gerenciadorProcesso){
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TABELA DE PROCESSOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    for(int i = 0;i < 50;i++){
        ImpressaoProcesso(&(gerenciadorProcesso->tabelaProcessos.processos[i]));
    }
}
