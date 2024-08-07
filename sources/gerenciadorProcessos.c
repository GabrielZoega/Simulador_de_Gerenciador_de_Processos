#include "../headers/gerenciadorProcessos.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador){
    //inicializa a tabela de processos
    int i;
    for (i = 0; i < 50; i++){
        gerenciadorProcesso->tabelaProcessos.processos[i].idProcesso = -1;
    }
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos = 1;
	
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
    gerenciadorProcesso->estadoExecucao.processoExec =  0;
    
    //cria o processo pai simulado
    Processo *processoPaiSimulado = &(gerenciadorProcesso->tabelaProcessos.processos[0]);
    int IDS = 0;
    init(processoPaiSimulado, INIT, &IDS);
    AlocarProcesso(&gerenciadorProcesso->Cpu, processoPaiSimulado);

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        LerPipe(fd[0], &comandoEntrada);

//        printf("Entrou no filho: %c\n", comandoEntrada);
        
        if(comandoEntrada == 'U'){
        	printf("Processo Cpu: %d\n", gerenciadorProcesso->Cpu.idprocesso);
        	printf("Processo execucao: %d\n", gerenciadorProcesso->estadoExecucao.processoExec);
            executaInstrucao(gerenciadorProcesso, &IDS, escalonador, &filaDePrioridades);
            gerenciadorProcesso->Cpu.PC_Atual++;
            gerenciadorProcesso->Tempo++;
            desbloqueiaProcessos(gerenciadorProcesso, &filaDePrioridades);
            if(escalonador == FILA_DE_PRIORIDADE){
            	confereFatiaQuantum(gerenciadorProcesso);
            }
        }else if(comandoEntrada == 'I'){
            
        }else if(comandoEntrada == 'M'){
            break;
        }
        else{
            printf("Um comando invalido foi digitado!\n");
            printf("Programa Encerrado!\n");
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

void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *IDS, int escalonador, FilasDePrioridade *filasDePrioridade){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;
    gerenciadorProcesso->Cpu.FatiaQuantum++;
    
    sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c ", &instrucao);

    switch (instrucao){
    case 'N':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoN(&(gerenciadorProcesso->Cpu), n);
        printf("ENTROU N\n");
        break;
    case 'D':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &x);
        instrucaoD(&(gerenciadorProcesso->Cpu), x);
        printf("ENTROU D\n");
        break;
    case 'V':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoV(&(gerenciadorProcesso->Cpu), x, n);
        printf("ENTROU V\n");
        break;
    case 'A':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoA(&(gerenciadorProcesso->Cpu), x, n);
        printf("ENTROU A\n");
        break;
    case 'S':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoS(&(gerenciadorProcesso->Cpu), x, n);
        printf("ENTROU S\n");
        break;
    case 'B':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoB(gerenciadorProcesso, n, escalonador, filasDePrioridade);
        printf("ENTROU B\n");
        break;
    case 'T':
        instrucaoT(gerenciadorProcesso, escalonador, filasDePrioridade);

        printf("ENTROU T\n");
        break;
    case 'F':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        printf("ENTROU F\n");
        instrucaoF(gerenciadorProcesso, n, IDS, escalonador);
        break;
    case 'R':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %s", &instrucao, nome_do_arquivo);
        printf("Nome do Arquivo: %s\n", nome_do_arquivo);
        printf("ENTROU R\n");
        instrucaoR(gerenciadorProcesso, nome_do_arquivo, IDS, escalonador);
        break;
    default:
        break;
    }
}

void instrucaoN(CPU *Cpu, int n){
    if(Cpu->MemoriaSimulada != NULL) free (Cpu->MemoriaSimulada);
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

//TODO implementar o escalonador
void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n, int escalonador, FilasDePrioridade *filasDePrioridade){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]);
    processoAtual->estado = BLOQUEADO;
    processoAtual->tempoBloqueado = n;

    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador);
    // trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[FDesenfileira(&(gerenciadorProcesso->estadoPronto.processosP))]));
}

//TODO conferir essa URGENTE
void instrucaoT(GerenciadorProcesso* gerenciadorProcesso, int escalonador, FilasDePrioridade *filasDePrioridade){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]);
	if(processoAtual->memoriaDoProcesso !=  NULL){
		free(processoAtual->memoriaDoProcesso);
	}

	free(processoAtual->vetorPrograma);
    processoAtual->idProcesso = -1;
    decideEscalonador(gerenciadorProcesso, filasDePrioridade, escalonador);
	//trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[FDesenfileira(&(gerenciadorProcesso->estadoPronto.processosP))]));
}

//TODO implementar o escalonador
void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n, int *IDS, int escalonador){
    Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]);
    Processo novoProcesso;

    alocarVetorPrograma(&(gerenciadorProcesso->Cpu), &novoProcesso);
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->Cpu), &novoProcesso);
    novoProcesso.idProcesso = *IDS;
    (*IDS)++;
    novoProcesso.idProcessoPai = gerenciadorProcesso->Cpu.idprocesso;
    novoProcesso.inicioTempo = gerenciadorProcesso->Tempo;
    novoProcesso.estado = PRONTO;
    FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), novoProcesso.idProcesso);
    novoProcesso.prioridade = processoAtual->prioridade;
    novoProcesso.programCounter = gerenciadorProcesso->Cpu.PC_Atual+1;
    novoProcesso.tempoUsadoCPU = 0;
    novoProcesso.tempoBloqueado = 0;

    gerenciadorProcesso->Cpu.PC_Atual += n;
    
}

void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo, int *IDS, int escalonador){
    Processo *processoAntigo = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]); 
    Processo novoProcesso;
    init(&novoProcesso, nome_do_arquivo, IDS);
    novoProcesso.idProcesso = gerenciadorProcesso->Cpu.idprocesso;
    free(processoAntigo->vetorPrograma);
    processoAntigo->vetorPrograma = NULL;
    copiarVetorPrograma(&(gerenciadorProcesso->Cpu), &novoProcesso);

    gerenciadorProcesso->Cpu.PC_Atual = -1;
    free(gerenciadorProcesso->Cpu.MemoriaSimulada);
    gerenciadorProcesso->Cpu.MemoriaSimulada = NULL;
    gerenciadorProcesso->Cpu.tamanhoMemoriaSimulada = novoProcesso.tamanhoMemoriaDoProcesso;

//    decideEscalonador
    // trocaDeContexto(gerenciadorProcesso, &novoProcesso);
    // gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec] = novoProcesso;
}

void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado){

	//atualiza os dados do processo em execucao na tabela de processos e passa para a fila de estado pronto ou bloqueado
	Processo *processoNaoEscalonado = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]);
    gerenciadorProcesso->tabelaProcessos.quantidadeDeProcessos ++;
    processoNaoEscalonado->programCounter = gerenciadorProcesso->Cpu.PC_Atual;
    processoNaoEscalonado->tempoUsadoCPU += gerenciadorProcesso->Cpu.FatiaQuantum;
    processoNaoEscalonado->tamanhoMemoriaDoProcesso = gerenciadorProcesso->Cpu.tamanhoMemoriaSimulada;
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->Cpu), processoNaoEscalonado);

    if(processoNaoEscalonado->estado == BLOQUEADO){
		FEnfileira(&(gerenciadorProcesso->estadoBloqueado.processosB), processoNaoEscalonado->idProcesso);
    }else if(processoNaoEscalonado->estado == PRONTO){
		FEnfileira(&(gerenciadorProcesso->estadoPronto.processosP), processoNaoEscalonado->idProcesso);
    }
    free(gerenciadorProcesso->Cpu.VetorDeProgramas);
    free(gerenciadorProcesso->Cpu.MemoriaSimulada);

    //muda o processoEscalonado para o estado de execucao
    processoEscalonado->estado = EM_EXECUCAO;
	gerenciadorProcesso->estadoExecucao.processoExec = processoEscalonado->idProcesso;
    AlocarProcesso(&gerenciadorProcesso->Cpu, processoEscalonado);
    // gerenciadorProcesso->Cpu.PC_Atual--;
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

void confereFatiaQuantum(GerenciadorProcesso *gerenciadorProcesso){
	Processo *processoAtual = &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->estadoExecucao.processoExec]);
	if(processoAtual->prioridade == 0){
		if(gerenciadorProcesso->Cpu.FatiaQuantum >= 1){
			processoAtual->prioridade = 1;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 0;
		}
	}else if(processoAtual->prioridade == 1){
		if(gerenciadorProcesso->Cpu.FatiaQuantum >= 2){
			processoAtual->prioridade = 2;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 0;
		}
	}else if(processoAtual->prioridade == 2){
		if(gerenciadorProcesso->Cpu.FatiaQuantum >= 4){
			processoAtual->prioridade = 3;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 1;
		}
	}else if(processoAtual->prioridade == 3){
		if(gerenciadorProcesso->Cpu.FatiaQuantum >= 8){
			processoAtual->prioridade = 3;
		}else if(processoAtual->estado == BLOQUEADO){
			processoAtual->prioridade = 2;
		}
	}
}

int escalonadorFilaPrioridade(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade){
    //processo pai inicia com prioridade 0(mais alta)
	int idProcessoNaoEscalonado = gerenciadorProcesso->estadoExecucao.processoExec;
	enfileiraFilaDePrioridade(gerenciadorProcesso, filasDePrioridade, idProcessoNaoEscalonado);

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

    if(processoEscalonado->prioridade == 0){
        processoEscalonado->prioridade = 1;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado);

    }else if(processoEscalonado->prioridade == 1 && processoEscalonado->tempoUsadoCPU > 1){
        processoEscalonado->prioridade = 2;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado);

    }else if(processoEscalonado->prioridade == 2 && processoEscalonado->tempoUsadoCPU > 3){
        processoEscalonado->prioridade = 3;
        trocaDeContexto(gerenciadorProcesso, processoEscalonado);

    }else if(processoEscalonado->prioridade == 3 && processoEscalonado->tempoUsadoCPU > 7){
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado);

    }else{
    	trocaDeContexto(gerenciadorProcesso, processoEscalonado);
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

void decideEscalonador(GerenciadorProcesso *gerenciadorProcesso, FilasDePrioridade *filasDePrioridade, int escalonador){
	switch(escalonador){
	case FILA_DE_PRIORIDADE:
		escalonadorFilaPrioridade(gerenciadorProcesso, filasDePrioridade);
		break;
	case ROUND_ROBIN:
		int idProcessoEscalonado = escalonamentoRoundRobin(&(gerenciadorProcesso->estadoPronto), gerenciadorProcesso->estadoExecucao.processoExec);
		trocaDeContexto(gerenciadorProcesso, &(gerenciadorProcesso->tabelaProcessos.processos[idProcessoEscalonado]));
		break;
	default:
		break;
	}
}
