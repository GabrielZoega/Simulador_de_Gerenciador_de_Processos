#include "../headers/gerenciadorProcessos.h"
#include "../headers/processoImpressao.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso){
    FFVazia(&(gerenciadorProcesso->estadoBloqueado.processosB));
    FFVazia(&(gerenciadorProcesso->estadoPronto.processosP));
    gerenciadorProcesso->estadoExecucao.processoExec =  0;
    Processo processoSimulado;
    int IDS = 0;
    gerenciadorProcesso->Tempo = 0;

    init(&processoSimulado, INIT, &IDS);
    AlocarProcesso(&gerenciadorProcesso->Cpu, &processoSimulado);

    gerenciadorProcesso->tabelaProcessos.processos[0] = processoSimulado;

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        LerPipe(fd[0], &comandoEntrada);

        //printf("Entrou no filho: %c\n", comandoEntrada);
        
        if(comandoEntrada == 'U'){
            executaInstrucao(gerenciadorProcesso, &IDS);
            gerenciadorProcesso->Cpu.PC_Atual++;
            gerenciadorProcesso->Cpu.FatiaQuantum++;
            gerenciadorProcesso->Tempo++;
        }
        else if(comandoEntrada == 'I'){
            ApresentarTudo(gerenciadorProcesso);
            
        }
        else if(comandoEntrada == 'M'){
            ApresentarTudo(gerenciadorProcesso);
            Asteriscos(FUNDO_VERMELHO);
            break;
        }
        else{
            printf("\n" INICIO3 "Um comando invalido foi digitado!" FINAL "\n", BOLD, VERMELHO, PISCAR);
            printf("\n" INICIO2 "Programa Encerrado!" FINAL "\n", BOLD, VERMELHO);
            Asteriscos(FUNDO_VERMELHO);
            break;
        }
    }
}

void init(Processo *processoSimulado, char *path, int *IDS){  
    processoSimulado->idProcesso = *IDS;
    (*IDS)++;
    processoSimulado->idProcessoPai = -1;
    processoSimulado->inicioTempo = 0;
    processoSimulado->estado = EM_EXECUCAO;
    processoSimulado->prioridade = 0;
    processoSimulado->programCounter = 0;
    processoSimulado->tempoUsadoCPU = 0;
    processoSimulado->tempoBloqueado = 0;
    lerInstrucoes(processoSimulado, path);
}

void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;
    Processo processoSimulado;

    sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c ", &instrucao);

    switch (instrucao){
    case 'N':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoN(&(gerenciadorProcesso->Cpu), n);
        //printf("ENTROU N\n");
        break;
    case 'D':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &x);
        instrucaoD(&(gerenciadorProcesso->Cpu), x);
        //printf("ENTROU D\n");
        break;
    case 'V':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoV(&(gerenciadorProcesso->Cpu), x, n);
        //printf("ENTROU V\n");
        break;
    case 'A':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoA(&(gerenciadorProcesso->Cpu), x, n);
        //printf("ENTROU A\n");
        break;
    case 'S':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoS(&(gerenciadorProcesso->Cpu), x, n);
        //printf("ENTROU S\n");
        break;
    case 'B':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoB(gerenciadorProcesso, n);
        //printf("ENTROU B\n");
        break;
    case 'T':
        instrucaoT(gerenciadorProcesso);

        //printf("ENTROU T\n");
        break;
    case 'F':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        //printf("ENTROU F\n");
        instrucaoF(gerenciadorProcesso, n, IDS);
        break;
    case 'R':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %s", &instrucao, nome_do_arquivo);
        //printf("Nome do Arquivo: %s\n", nome_do_arquivo);
        //printf("ENTROU R\n");
        instrucaoR(gerenciadorProcesso, nome_do_arquivo, IDS);
        break;
    default:
        break;
    }
}

void instrucaoN(CPU *Cpu, int n){
    Cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * n);
    Cpu->tamanhoMemoriaSimulada = n;
}

void instrucaoD(CPU *Cpu, int x){
    Cpu->MemoriaSimulada[x] = 0;
    //printf("D %d\n", x);
}

void instrucaoV(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] = n;
    //printf("V %d %d\n", x, n);
}

void instrucaoA(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] += n;
    //printf("A %d %d\n", x, n);
}

void instrucaoS(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] -= n;
    //printf("S %d %d\n", x, n);
}

void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n){
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec].estado = BLOQUEADO;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec].tempoBloqueado = n;
    FEnfileira(&(gerenciadorProcesso->estadoBloqueado.processosB), gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec].idProcesso);
    trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[FDesenfileira(&(gerenciadorProcesso->estadoPronto.processosP))]));
    //printf("B %d\n", n);
}

void instrucaoT(GerenciadorProcesso* gerenciadorProcesso){
	free(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].memoriaDoProcesso);
	free(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].vetorPrograma);
	trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[FDesenfileira(&(gerenciadorProcesso->estadoPronto.processosP))]));
}

void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS){
    Processo novoProcesso;

    alocarVetorPrograma(&(gerenciadorProcesso->Cpu), &novoProcesso);
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->Cpu), &novoProcesso);
    novoProcesso.idProcesso = *IDS;
    (*IDS)++;
    novoProcesso.idProcessoPai = gerenciadorProcesso->Cpu.idprocesso;
    novoProcesso.inicioTempo = gerenciadorProcesso->Tempo;
    novoProcesso.estado = EM_EXECUCAO;
    novoProcesso.prioridade = gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].prioridade;
    novoProcesso.programCounter = gerenciadorProcesso->Cpu.PC_Atual+1;
    novoProcesso.tempoUsadoCPU = 0;
    novoProcesso.tempoBloqueado = 0;

    gerenciadorProcesso->Cpu.PC_Atual = n + 1;
    
    FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec].idProcesso);
    trocaDeContexto(gerenciadorProcesso, &novoProcesso);
}

void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS){
    Processo novoProcesso;
    init(&novoProcesso, nome_do_arquivo, IDS);
    FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec].idProcesso);
    trocaDeContexto(gerenciadorProcesso, &novoProcesso);
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec] = novoProcesso;
}

void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado){
	gerenciadorProcesso->estadoExecucao.processoExec = processoEscalonado->idProcesso;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].programCounter = gerenciadorProcesso->Cpu.PC_Atual;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].tempoUsadoCPU = gerenciadorProcesso->Cpu.FatiaQuantum;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].tamanhoMemoriaDoProcesso = gerenciadorProcesso->Cpu.tamanhoMemoriaSimulada;
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->Cpu), &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]));
    free(gerenciadorProcesso->Cpu.VetorDeProgramas);

    gerenciadorProcesso->estadoExecucao.processoExec = processoEscalonado->idProcesso;
    AlocarProcesso(&gerenciadorProcesso->Cpu, processoEscalonado);
    gerenciadorProcesso->Cpu.PC_Atual--;
}

void escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso,Processo *processo){
    //processo pai inicia com prioridade 0(mais alta)
    if(processo->prioridade==0){
        processo->prioridade = 1;
        trocaDeContexto(gerenciadorProcesso,processo);
    }else if(processo->prioridade == 1 && processo->tempoUsadoCPU > 1){
        processo->prioridade = 2;
        trocaDeContexto(gerenciadorProcesso,processo);
    }else if(processo->prioridade==2 && processo->tempoUsadoCPU > 3){
        processo->prioridade = 3;
        trocaDeContexto(gerenciadorProcesso,processo);
    }else if(processo->prioridade == 3 && processo->tempoUsadoCPU > 7){
        trocaDeContexto(gerenciadorProcesso,processo);
    }else{
        trocaDeContexto(gerenciadorProcesso,processo);
    }
}

/* Função que faz o escalonamento por Round Robin */
/* - função é executada a cada final de unidade de tempo. */
/* - indiceCpu é passado se ao terminar a unidade de tempo o processo precisa voltar para o estado pronto, ou seja, quando ele não vai para o estado bloqueado ou terminou de executar. Caso seja um desses casos, o indiceCpu deve ser passado como null. */
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu){
    int indice;
    /* Retira o primeiro da fila para executar. */
    indice = FDesenfileira(&(estP->processosP));

    if (indiceCpu >= 0)
        /* Coloca o que estava executando ao final da fila. */
        FEnfileira(&(estP->processosP), indiceCpu);

    /* Retorna o índice do que deve executar atualmente. */
    return indice;
}