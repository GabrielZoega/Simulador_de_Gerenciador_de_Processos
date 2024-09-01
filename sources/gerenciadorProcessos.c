#include "../headers/gerenciadorProcessos.h"
#include "../headers/processoImpressao.h"
#include "../headers/nextFit.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador, Memoria *memoria, int tecnicaAlocacao){
    //inicializa a tabela de processos
    int i;
    for (i = 0; i < 50; i++){
        gerenciadorProcesso->tabelaProcessos.processos[i].idProcesso = -1;
    }
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos = 1;
    gerenciadorProcesso->Tempo = 0;

    //Inicializa as filas
    //Filas de prioridade
    FilasDePrioridade filaDePrioridades;
	FFVazia(&(filaDePrioridades.prioridade0));
	FFVazia(&(filaDePrioridades.prioridade1));
	FFVazia(&(filaDePrioridades.prioridade2));
    FFVazia(&(filaDePrioridades.prioridade3));
    //Filas de estados
    FFVazia(&(gerenciadorProcesso->estadoBloqueado.processosB));
    FFVazia(&(gerenciadorProcesso->estadoPronto.processosP));
    gerenciadorProcesso->estadoExecucao.processoExec[0] =  0;
    
    //cria o processo pai simulado
    Processo *processoPaiSimulado = &(gerenciadorProcesso->tabelaProcessos.processos[0]);
    int IDS = 0;
    init(processoPaiSimulado, INIT, &IDS);
    AlocarProcesso(&gerenciadorProcesso->vetorCPUS.processadores[0], processoPaiSimulado);
    gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas = 0;
    gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas++;
    gerenciadorProcesso->vetorCPUS.ultimaCpuUsada = 0;
    gerenciadorProcesso->vetorCPUS.processadores[0].cpuOcupada = OCUPADA;

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        if(LerPipe(fd[0], &comandoEntrada) == -1){
            printf("broken pipe\n");
            break;
        }

        if(comandoEntrada == 'U'){

            for (i = 0; i < gerenciadorProcesso->vetorCPUS.numeroDeProcessadores; i++){
                if(gerenciadorProcesso->vetorCPUS.processadores[i].cpuOcupada == DESOCUPADA) continue;
                executaInstrucao(gerenciadorProcesso, &IDS, escalonador, &filaDePrioridades, i, memoria);
                gerenciadorProcesso->vetorCPUS.processadores[i].PC_Atual++;
                if(escalonador == FILA_DE_PRIORIDADE){
                    confereFatiaQuantum(gerenciadorProcesso, i);
                }else if(escalonador == ROUND_ROBIN){
                    if((gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos > 1)){
                        decideEscalonador(gerenciadorProcesso, &filaDePrioridades, escalonador, i, memoria);
                    }
                }
            }
			desbloqueiaProcessos(gerenciadorProcesso, &filaDePrioridades);
            gerenciadorProcesso->Tempo++;
			if(gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos <= 0)
				printf("\n" INICIO3 "Não ha mais processos em execução, digite M para encerrar o programa" FINAL "\n", BOLD, VERMELHO, PISCAR);

        }else if(comandoEntrada == 'I'){
        	ApresentarTudo(gerenciadorProcesso, memoria);
        	printf(INICIO2 "\nComandos:" FINAL "\n", BOLD, UNDERLINE);
        }else if(comandoEntrada == 'M'){
        	ApresentarTudo(gerenciadorProcesso, memoria);
			Asteriscos(FUNDO_VERMELHO);
            break;
        }
        else{
        	printf("\n" INICIO3 "Um comando inválido foi digitado!" FINAL "\n", BOLD, VERMELHO, PISCAR);
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
    processoSimulado->tempoUsadoCPU = 100;
    processoSimulado->tempoBloqueado = 0;
    processoSimulado->memoriaDoProcesso = NULL;
    lerInstrucoes(processoSimulado, path);
}

void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum++;
    
    if (gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas == NULL) return;
    sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c ", &instrucao);
    printf("Instrucao: %c\n", instrucao);
    switch (instrucao){
    case 'N':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoN(gerenciadorProcesso, n, cpuAtual, memoria);
        gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;
        break;
    case 'D':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &x);
        instrucaoD(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, memoria);
        gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;
        break;
    case 'V':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoV(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n, memoria);
        gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;
        break;
    case 'A':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoA(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n, memoria);
        gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;        
        break;
    case 'S':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoS(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n, memoria);
        gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;
        break;
    case 'B':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoB(gerenciadorProcesso, n, escalonador, filasDePrioridade, cpuAtual, memoria);
        break;
    case 'T':
        instrucaoT(gerenciadorProcesso, escalonador, filasDePrioridade, cpuAtual, memoria);
        break;
    case 'F':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoF(gerenciadorProcesso, n, IDS, escalonador, filasDePrioridade, cpuAtual, memoria);
        break;
    case 'R':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %s", &instrucao, nome_do_arquivo);
        instrucaoR(gerenciadorProcesso, nome_do_arquivo, IDS, escalonador, cpuAtual, memoria);
        break;
    default:
        break;
    }
}

void instrucaoN(GerenciadorProcesso *gerenciadorProcesso, int n, int cpuAtual, Memoria *memoria){
    int enderecoInicio = -1;
    //printf("ultimaPosicao: %d\n", memoria->ultimaPosicao);
    nextFit(memoria, n, &memoria->ultimaPosicao, &enderecoInicio);
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].inicioMemoria = enderecoInicio;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tamanhoMemoriaDoProcesso = n;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].inicioMemoriaProcessoAtual = enderecoInicio;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaProcessoAtual = n;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso].tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;

    // if(Cpu->MemoriaSimulada != NULL){
    //     free (Cpu->MemoriaSimulada);
    //     Cpu->MemoriaSimulada = NULL;
    // }
    // Cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * n);
    // Cpu->tamanhoMemoriaSimulada = n;
}

void instrucaoD(CPU *cpu, int x, Memoria *memoria){
    x += cpu->inicioMemoriaProcessoAtual;
    memoria->vetorMemoria[x] = 0;
}

void instrucaoV(CPU *cpu, int x, int n, Memoria *memoria){
    x += cpu->inicioMemoriaProcessoAtual;
    memoria->vetorMemoria[x] = n;
}

void instrucaoA(CPU *cpu, int x, int n, Memoria *memoria){
    x += cpu->inicioMemoriaProcessoAtual;
    memoria->vetorMemoria[x] += n;
}

void instrucaoS(CPU *cpu, int x, int n, Memoria *memoria){
    x += cpu->inicioMemoriaProcessoAtual;
    memoria->vetorMemoria[x] -= n;
}

void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    processoAtual->estado = BLOQUEADO;
    processoAtual->tempoBloqueado = n;

    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual, memoria);
}

void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria){ 
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
	if(processoAtual->memoriaDoProcesso !=  NULL){
		free(processoAtual->memoriaDoProcesso);
        processoAtual->memoriaDoProcesso = NULL;
	}
    if (processoAtual->vetorPrograma != NULL){
    	int i;
    	for(i = 1; strcmp(processoAtual->vetorPrograma[i-1], "T") != 0; i++);
    	for (int j = 0; j < i; j++) free(processoAtual->vetorPrograma[j]);
	    free(processoAtual->vetorPrograma);
        processoAtual->vetorPrograma = NULL;
    }
    processoAtual->idProcesso = -1;
    gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual] = -1;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].cpuOcupada = DESOCUPADA;

    for (int i = 0; i < gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaProcessoAtual; i++){
        memoria->vetorMemoria[i + gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].inicioMemoriaProcessoAtual] = INT_MIN;
    }
    
    
    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual, memoria);
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos --;
    printf("--- Quantidade de Processos Depois do T: %d ---\n", gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos);

    if (gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1){
        gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas--; // Diminuir o número de CPUS sendo utilizadas, pois uma instrução acabou aqui.
        if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas != NULL){
            free(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas);
            gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas = NULL;
        }
        gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual = 0;
    }

}

void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    Processo novoProcesso;
    novoProcesso.vetorPrograma = NULL;

    alocarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso);
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso, memoria);
    novoProcesso.idProcesso = *IDS;
    (*IDS)++;
    novoProcesso.tempoUltimoAcessoAMemoria = gerenciadorProcesso->Tempo;
    novoProcesso.idProcessoPai = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso;
    novoProcesso.inicioTempo = gerenciadorProcesso->Tempo;
    novoProcesso.estado = PRONTO;
    novoProcesso.prioridade = processoAtual->prioridade;
    //novoProcesso.inicioMemoria = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].inicioMemoriaProcessoAtual;

    if(gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1){
        if (escalonador == ROUND_ROBIN) novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+2;
        else novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+1;
    }
    else{
        if (escalonador == ROUND_ROBIN) novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+1;
        else novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual;
    }

    int enderecoInicio = -1;
    n = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaProcessoAtual;
    nextFit(memoria, n, &memoria->ultimaPosicao, &enderecoInicio);
    
    novoProcesso.inicioMemoria = enderecoInicio;
    novoProcesso.tamanhoMemoriaDoProcesso = n;

    novoProcesso.tempoUsadoCPU = 0;
    novoProcesso.tempoBloqueado = 0;
    FEnfileira(&gerenciadorProcesso->estadoPronto.processosP, novoProcesso.idProcesso);

    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual += n;
    gerenciadorProcesso->tabelaProcessos.processos[novoProcesso.idProcesso] = novoProcesso;
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos++;
    printf("--- Quantidade de Processos Depois do F: %d ---\n", gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos);

    printf("Endereco inicio: %d\n", gerenciadorProcesso->tabelaProcessos.processos[novoProcesso.idProcesso].inicioMemoria);
    if (gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1){
        decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual, memoria);
    }
}

void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual, Memoria *memoria){
    Processo *processoAntigo = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]); 
    Processo novoProcesso;
    init(&novoProcesso, nome_do_arquivo, IDS);
    *IDS = *IDS - 1;
    novoProcesso.idProcesso = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso;
    
    if(processoAntigo->vetorPrograma != NULL) {
    	int i;
		for(i = 1; strcmp(processoAntigo->vetorPrograma[i-1], "T") != 0; i++);
		for (int j = 0; j < i; j++) free(processoAntigo->vetorPrograma[j]);
		free(processoAntigo->vetorPrograma);
		processoAntigo->vetorPrograma = NULL;
    }
    if(processoAntigo->memoriaDoProcesso != NULL) {
        free(processoAntigo->memoriaDoProcesso);
        processoAntigo->memoriaDoProcesso = NULL;
    }

   
    copiarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso);
    
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual = -1;
    // TODO: pensar em como isso aqui vai funcionar, desalocar a memória desse processo? não será mais com o free, usar INT_MIN? Precisaria do tamanho que o processo ocupa na memória.
    for (int i = 0; i < gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaProcessoAtual; i++){
       memoria->vetorMemoria[i + gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].inicioMemoriaProcessoAtual] = INT_MIN; // acho que isso aqui resolve, desalocando a memória.
    }
    novoProcesso.memoriaDoProcesso = NULL;
}

void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual, Memoria *memoria){
    printf("Troca de contexto\n");
    printf("IDprocesso: %d\n", processoEscalonado->idProcesso);
    printf("Endereco inicio: %d\n", processoEscalonado->inicioMemoria);

    Processo *processoNaoEscalonado = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    
    if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual][0] != 'T'){
        processoNaoEscalonado->programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual;
        printf("Tempo Usado CPU: %d\n", processoNaoEscalonado->tempoUsadoCPU);
        alocarMemoriaDoProcesso(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), processoNaoEscalonado, memoria);
        alocarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), processoNaoEscalonado);
        processoNaoEscalonado->tamanhoMemoriaDoProcesso = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaProcessoAtual; // acho que isso resolve, o processo não escalonado é o que está na CPU no momento.
        processoNaoEscalonado->inicioMemoria = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].inicioMemoriaProcessoAtual;
    }

    if(processoNaoEscalonado->estado == BLOQUEADO && (gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual][0] != 'T')){
		FEnfileira(&(gerenciadorProcesso->estadoBloqueado.processosB), processoNaoEscalonado->idProcesso);
    }else if(processoNaoEscalonado->estado == EM_EXECUCAO && (gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual][0] != 'T')){
    	if((processoNaoEscalonado->idProcesso >= 0) && (gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas == gerenciadorProcesso->vetorCPUS.numeroDeProcessadores)){
            FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), processoNaoEscalonado->idProcesso);
            processoNaoEscalonado->estado = PRONTO;
        }else{
        	if(escalonador == ROUND_ROBIN)
        		processoEscalonado->programCounter--;
                processoNaoEscalonado->estado = PRONTO;
        }
    }

    //muda o processoEscalonado para o estado de execucao
    printf("numero de processadores: %d\n", gerenciadorProcesso->vetorCPUS.numeroDeProcessadores);
    processoEscalonado->estado = EM_EXECUCAO;
    gerenciadorProcesso->vetorCPUS.processadores[selecionaCPU(&(gerenciadorProcesso->vetorCPUS))].inicioMemoriaProcessoAtual = processoEscalonado->inicioMemoria;
	gerenciadorProcesso->estadoExecucao.processoExec[selecionaCPU(&(gerenciadorProcesso->vetorCPUS))] = processoEscalonado->idProcesso;
	copiarMemoriaCpu(memoria, processoEscalonado);
    AlocarProcesso(&gerenciadorProcesso->vetorCPUS.processadores[selecionaCPU(&(gerenciadorProcesso->vetorCPUS))], processoEscalonado);
    gerenciadorProcesso->vetorCPUS.ultimaCpuUsada = selecionaCPU(&(gerenciadorProcesso->vetorCPUS));
    if (gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1) gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas++; // ACHO que seria aqui o momento para atualizar o número de CPUS
}

void desbloqueiaProcessos(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade){
	TFila *filaBloqueados = &(gerenciadorProcesso->estadoBloqueado.processosB);
	TFila *filaProntos = &(gerenciadorProcesso->estadoPronto.processosP);
	int idProcesso1, idProcesso;
	if(!FEhVazia(filaBloqueados)){
		idProcesso1 = FDesenfileira(filaBloqueados);
		if(gerenciadorProcesso->tabelaProcessos.processos[idProcesso].tempoBloqueado <= 0){
			FEnfileira(filaProntos, idProcesso);
			enfileiraFilaDePrioridade(gerenciadorProcesso, filasDePrioridade, idProcesso1);
		}else {
			gerenciadorProcesso->tabelaProcessos.processos[idProcesso1].tempoBloqueado--;
			FEnfileira(filaBloqueados, idProcesso);
		}

		while(filaBloqueados->pFrente->indice != idProcesso1){
			idProcesso = FDesenfileira(filaBloqueados);
			if(gerenciadorProcesso->tabelaProcessos.processos[idProcesso].tempoBloqueado <= 0){
				FEnfileira(filaProntos, idProcesso);
				enfileiraFilaDePrioridade(gerenciadorProcesso, filasDePrioridade, idProcesso);
			}else {
				gerenciadorProcesso->tabelaProcessos.processos[idProcesso].tempoBloqueado--;
				FEnfileira(filaBloqueados, idProcesso);
			}
		}
	}
}

void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso, int cpuAtual){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
	if(processoAtual->prioridade == 0){
		if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum >= 1){
			processoAtual->prioridade = 1;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 0;
		}
	}else if(processoAtual->prioridade == 1){
		if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum >= 2){
			processoAtual->prioridade = 2;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 0;
		}
	}else if(processoAtual->prioridade == 2){
		if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum >= 4){
			processoAtual->prioridade = 3;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 1;
		}
	}else if(processoAtual->prioridade == 3){
		if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum >= 8){
			processoAtual->prioridade = 3;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 2;
		}
	}
}

int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual, Memoria *memoria){
    //processo pai inicia com prioridade 0(mais alta)
	int idProcessoNaoEscalonado = gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual];

	Processo *processoEscalonado;
    int idProcessoEscalonado;
    if(!FEhVazia(&(filasDePrioridade->prioridade0))){
        idProcessoEscalonado =  FDesenfileira(&(filasDePrioridade->prioridade0));
        processoEscalonado =  &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]);
    
    }else if(!FEhVazia(&(filasDePrioridade->prioridade1))){
        idProcessoEscalonado =  FDesenfileira(&(filasDePrioridade->prioridade1));
        processoEscalonado =  &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]);
    
    }else if(!FEhVazia(&(filasDePrioridade->prioridade2))){
        idProcessoEscalonado =  FDesenfileira(&(filasDePrioridade->prioridade2));
        processoEscalonado =  &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]);
    
    }else if(!FEhVazia(&(filasDePrioridade->prioridade3))){
        idProcessoEscalonado =  FDesenfileira(&(filasDePrioridade->prioridade3));
        processoEscalonado =  &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]);
    
    }else if(!FEhVazia(&(gerenciadorProcesso->estadoPronto.processosP))){
        idProcessoEscalonado =  FDesenfileira(&(gerenciadorProcesso->estadoPronto.processosP));
        processoEscalonado =  &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]);
    
    }else return -1;

    if((strcmp(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "T") != 0) && gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas == gerenciadorProcesso->vetorCPUS.numeroDeProcessadores){
        enfileiraFilaDePrioridade(gerenciadorProcesso, filasDePrioridade, idProcessoNaoEscalonado);
    } 

    if(processoEscalonado->prioridade == 0){
        processoEscalonado->prioridade = 1;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual, memoria);

    }else if(processoEscalonado->prioridade == 1 && processoEscalonado->tempoUsadoCPU > 1){
        processoEscalonado->prioridade = 2;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual, memoria);

    }else if(processoEscalonado->prioridade == 2 && processoEscalonado->tempoUsadoCPU > 3){
        processoEscalonado->prioridade = 3;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual, memoria);

    }else if(processoEscalonado->prioridade == 3 && processoEscalonado->tempoUsadoCPU > 7){
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual, memoria);

    }else{
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual, memoria);
    }
	return 0;
}

void enfileiraFilaDePrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int idProcesso){
	Processo *processoEnfileirado = &(gerenciadorProcesso->tabelaProcessos.processos[idProcesso]);
	if(processoEnfileirado->prioridade == 0){
		FEnfileira(&(filasDePrioridade->prioridade0), idProcesso);
	}else if(processoEnfileirado->prioridade == 1){
		FEnfileira(&(filasDePrioridade->prioridade1), idProcesso);
	}else if(processoEnfileirado->prioridade == 2){
		FEnfileira(&(filasDePrioridade->prioridade2), idProcesso);
	}else if(processoEnfileirado->prioridade == 3){
		FEnfileira(&(filasDePrioridade->prioridade3), idProcesso);
	}
}

/* Função que faz o escalonamento por Round Robin */
/* - função é executada a cada final de unidade de tempo. */
/* - indiceCpu é passado se ao terminar a unidade de tempo o processo
 * precisa voltar para o estado pronto, ou seja, quando ele não vai para
 * o estado bloqueado ou terminou de executar. Caso seja um desses casos,
 * o indiceCpu deve ser passado como null. */
int escalonamentoRoundRobin(EstadoPronto *estP, int indiceCpu, GerenciadorProcesso *gerenciadorProcesso){
    int indice;
    /* Retira o primeiro da fila para executar. */
    if(!FEhVazia(&(estP->processosP))){
    	indice = FDesenfileira(&(estP->processosP));

    }else indice = -1;

    return indice;
}

void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual, Memoria *memoria){
	switch(escalonador){
	case FILA_DE_PRIORIDADE:
		escalonadorFilaPrioridade(gerenciadorProcesso, filasDePrioridade, cpuAtual, memoria);
		break;
	case ROUND_ROBIN:
		int idProcessoEscalonado = escalonamentoRoundRobin(&(gerenciadorProcesso->estadoPronto), gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual], gerenciadorProcesso);
		if(idProcessoEscalonado >= 0)
			trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]), ROUND_ROBIN, cpuAtual, memoria);
		break;
	default:
		break;
	}
}

VetorSegmentos getSegmentosOcupados(Memoria memoria, TabelaDeProcessos tabelaDeProcessos){
	VetorSegmentos vetorSegmentos;
	vetorSegmentos.segmentos = (Segmento*) malloc(sizeof(Segmento) * tabelaDeProcessos.quantidadeDeProcessos);
	vetorSegmentos.numSegmentos = tabelaDeProcessos.quantidadeDeProcessos;

	for (int i = 0; i < tabelaDeProcessos.quantidadeDeProcessos; i++) {
		vetorSegmentos.segmentos[i].idProcesso = tabelaDeProcessos.processos[i].idProcesso;
		vetorSegmentos.segmentos[i].posicaoInicio = tabelaDeProcessos.processos[i].inicioMemoria;
		vetorSegmentos.segmentos[i].tamanho = tabelaDeProcessos.processos[i].tamanhoMemoriaDoProcesso;
	}
	return vetorSegmentos;
}
