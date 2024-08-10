#include "../headers/gerenciadorProcessos.h"
#include "../headers/processoImpressao.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador){
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
    gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas++;
    gerenciadorProcesso->vetorCPUS.ultimaCpuUsada = 0;
    gerenciadorProcesso->vetorCPUS.processadores[0].cpuOcupada = OCUPADA;

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        LerPipe(fd[0], &comandoEntrada);

        if(comandoEntrada == 'U'){

            for (i = 0; i < gerenciadorProcesso->vetorCPUS.numeroDeProcessadores; i++){
                if(gerenciadorProcesso->vetorCPUS.processadores[i].cpuOcupada == DESOCUPADA) continue;
                executaInstrucao(gerenciadorProcesso, &IDS, escalonador, &filaDePrioridades, i);
                gerenciadorProcesso->vetorCPUS.processadores[i].PC_Atual++;
                if(escalonador == FILA_DE_PRIORIDADE){
                    confereFatiaQuantum(gerenciadorProcesso, i);
                }else if(escalonador == ROUND_ROBIN){
                    if((gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos > 1)){
                        decideEscalonador(gerenciadorProcesso, &filaDePrioridades, escalonador, i);
                    }
                }
            }
			desbloqueiaProcessos(gerenciadorProcesso, &filaDePrioridades);
            gerenciadorProcesso->Tempo++;
			if(gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos <= 0)
				printf("\n" INICIO3 "Não ha mais processos em execução, digite M para encerrar o programa" FINAL "\n", BOLD, VERMELHO, PISCAR);

        }else if(comandoEntrada == 'I'){
        	ApresentarTudo(gerenciadorProcesso);
        	printf(INICIO2 "\nComandos:" FINAL "\n", BOLD, UNDERLINE);
        }else if(comandoEntrada == 'M'){
        	ApresentarTudo(gerenciadorProcesso);
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
    processoSimulado->tempoUsadoCPU = 0;
    processoSimulado->tempoBloqueado = 0;
    processoSimulado->memoriaDoProcesso = NULL;
    lerInstrucoes(processoSimulado, path);
}

void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum++;
    
    if (gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas == NULL) return;
    sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c ", &instrucao);

    switch (instrucao){
    case 'N':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoN(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), n);
        break;
    case 'D':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &x);
        instrucaoD(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x);
        break;
    case 'V':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoV(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n);
        break;
    case 'A':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoA(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n);
        break;
    case 'S':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoS(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), x, n);
        break;
    case 'B':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoB(gerenciadorProcesso, n, escalonador, filasDePrioridade, cpuAtual);
        break;
    case 'T':
        instrucaoT(gerenciadorProcesso, escalonador, filasDePrioridade, cpuAtual);
        break;
    case 'F':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %d", &instrucao, &n);
        instrucaoF(gerenciadorProcesso, n, IDS, escalonador, filasDePrioridade, cpuAtual);
        break;
    case 'R':
        sscanf(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas[gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual], "%c %s", &instrucao, nome_do_arquivo);
        instrucaoR(gerenciadorProcesso, nome_do_arquivo, IDS, escalonador, cpuAtual);
        break;
    default:
        break;
    }
}

void instrucaoN(CPU *Cpu, int n){
    if(Cpu->MemoriaSimulada != NULL){
        Cpu->MemoriaSimulada = NULL;
        free (Cpu->MemoriaSimulada);
    }
    Cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * n);
    Cpu->tamanhoMemoriaSimulada = n;
}

void instrucaoD(CPU *Cpu, int x){
    Cpu->MemoriaSimulada[x] = 0;
}

void instrucaoV(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] = n;
}

void instrucaoA(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] += n;
}

void instrucaoS(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] -= n;
}

void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    processoAtual->estado = BLOQUEADO;
    processoAtual->tempoBloqueado = n;

    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual);
}

void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
	if(processoAtual->memoriaDoProcesso !=  NULL){
        processoAtual->memoriaDoProcesso = NULL;
		free(processoAtual->memoriaDoProcesso);
	}
    if (processoAtual->vetorPrograma != NULL){
        processoAtual->vetorPrograma = NULL;
	    free(processoAtual->vetorPrograma);
    }
    processoAtual->idProcesso = -1;
    gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual] = -1;
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].cpuOcupada = DESOCUPADA;

    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual);
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos --;

    if (gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1){
        gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas--; // ACHO que aqui deveria diminuir o número de CPUS sendo utilizadas, pois uma instrução acabou aqui.
        if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas != NULL){
            free(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas);
            gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].VetorDeProgramas = NULL;
        }
        gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual = 0;
    }

}

void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    Processo novoProcesso;

    alocarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso);
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso);
    novoProcesso.idProcesso = *IDS;
    (*IDS)++;
    novoProcesso.idProcessoPai = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso;
    novoProcesso.inicioTempo = gerenciadorProcesso->Tempo;
    novoProcesso.estado = PRONTO;
    novoProcesso.prioridade = processoAtual->prioridade;

    if(gerenciadorProcesso->vetorCPUS.numeroDeProcessadores > 1){
        if (escalonador == ROUND_ROBIN) novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+2;
        else novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+1;
    }
    else{
        if (escalonador == ROUND_ROBIN) novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual+1;
        else novoProcesso.programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual;
    }


    novoProcesso.tempoUsadoCPU = 0;
    novoProcesso.tempoBloqueado = 0;
    FEnfileira(&gerenciadorProcesso->estadoPronto.processosP, novoProcesso.idProcesso);

    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual += n + 1;
    gerenciadorProcesso->tabelaProcessos.processos[novoProcesso.idProcesso] = novoProcesso;
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos++;

    if (gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas != gerenciadorProcesso->vetorCPUS.numeroDeProcessadores){
        decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador, cpuAtual);
    }
}

void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador, int cpuAtual){
    Processo *processoAntigo = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]); 
    Processo novoProcesso;
    init(&novoProcesso, nome_do_arquivo, IDS);
    *IDS = *IDS - 1;
    novoProcesso.idProcesso = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].idprocesso;
    
    if(processoAntigo->vetorPrograma != NULL) {
        free(processoAntigo->vetorPrograma);
        processoAntigo->vetorPrograma = NULL;
    }
    if(processoAntigo->memoriaDoProcesso != NULL) {
        free(processoAntigo->memoriaDoProcesso);
        processoAntigo->memoriaDoProcesso = NULL;
    }

   
    copiarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), &novoProcesso);
    
    gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual = -1;
    if(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].MemoriaSimulada != NULL){
        free(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].MemoriaSimulada);
        gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].MemoriaSimulada = NULL;
    }
    novoProcesso.memoriaDoProcesso = NULL;
}

void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado, int escalonador, int cpuAtual){
	Processo *processoNaoEscalonado = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual]]);
    processoNaoEscalonado->programCounter = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].PC_Atual;
    processoNaoEscalonado->tempoUsadoCPU += gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].FatiaQuantum;
    processoNaoEscalonado->tamanhoMemoriaDoProcesso = gerenciadorProcesso->vetorCPUS.processadores[cpuAtual].tamanhoMemoriaSimulada;
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), processoNaoEscalonado);
    alocarVetorPrograma(&(gerenciadorProcesso->vetorCPUS.processadores[cpuAtual]), processoNaoEscalonado);

    if(processoNaoEscalonado->estado == BLOQUEADO){
		FEnfileira(&(gerenciadorProcesso->estadoBloqueado.processosB), processoNaoEscalonado->idProcesso);
    }else if(processoNaoEscalonado->estado == EM_EXECUCAO){
    	if((processoNaoEscalonado->idProcesso >= 0) && (gerenciadorProcesso->vetorCPUS.cpusSendoUtilizadas == gerenciadorProcesso->vetorCPUS.numeroDeProcessadores)){
            FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), processoNaoEscalonado->idProcesso);
        }else{
        	if(escalonador == ROUND_ROBIN)
        		processoEscalonado->programCounter--;
        }
    }

    //muda o processoEscalonado para o estado de execucao
    processoEscalonado->estado = EM_EXECUCAO;
	gerenciadorProcesso->estadoExecucao.processoExec[selecionaCPU(&(gerenciadorProcesso->vetorCPUS))] = processoEscalonado->idProcesso;
	alocarMemoriaCpu(&(gerenciadorProcesso->vetorCPUS.processadores[selecionaCPU(&(gerenciadorProcesso->vetorCPUS))]), processoEscalonado);
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

int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int cpuAtual){
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
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual);

    }else if(processoEscalonado->prioridade == 1 && processoEscalonado->tempoUsadoCPU > 1){
        processoEscalonado->prioridade = 2;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual);

    }else if(processoEscalonado->prioridade == 2 && processoEscalonado->tempoUsadoCPU > 3){
        processoEscalonado->prioridade = 3;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual);

    }else if(processoEscalonado->prioridade == 3 && processoEscalonado->tempoUsadoCPU > 7){
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual);

    }else{
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado, FILA_DE_PRIORIDADE, cpuAtual);
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

void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador, int cpuAtual){
	switch(escalonador){
	case FILA_DE_PRIORIDADE:
		escalonadorFilaPrioridade(gerenciadorProcesso, filasDePrioridade, cpuAtual);
		break;
	case ROUND_ROBIN:
		int idProcessoEscalonado = escalonamentoRoundRobin(&(gerenciadorProcesso->estadoPronto), gerenciadorProcesso->estadoExecucao.processoExec[cpuAtual], gerenciadorProcesso);
		if(idProcessoEscalonado >= 0)
			trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]), ROUND_ROBIN, cpuAtual);
		break;
	default:
		break;
	}
}
