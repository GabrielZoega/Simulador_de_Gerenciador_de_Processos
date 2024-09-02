#include "../headers/cpu.h"

void inicializaCPU(CPU *cpu){
    cpu->PC_Atual = 0;
    cpu->VetorDeProgramas = NULL;
    cpu->FatiaQuantum = 0;
    cpu->cpuOcupada = DESOCUPADA;
}

// Aloca o Vetor Programa e inicializa algumas variáveis
void AlocarProcesso(CPU *cpu, Processo *novoprocesso){
	int i = 0;
    cpu->idprocesso = novoprocesso->idProcesso; //id do processo em execução
    cpu->PC_Atual = novoprocesso->programCounter; //PC atualizado
    cpu->FatiaQuantum = 0;

    // Verifica de o vetor de programa da CPU é nulo. Caso não seja, libera ele.
    if(cpu->VetorDeProgramas != NULL){
		int i;
		for(i = 1; strcmp(cpu->VetorDeProgramas[i-1], "T") != 0; i++);
		for (int j = 0; j < i; j++) free(cpu->VetorDeProgramas[j]);
		free(cpu->VetorDeProgramas);
		cpu->VetorDeProgramas = NULL;
	}

    // Alocando o vetor de programa da CPU
    for(i = 1; novoprocesso->vetorPrograma[i-1][0] != 'T'; i++);
    cpu->VetorDeProgramas = (char**) malloc (sizeof(char*) * i);
    for (int j = 0; j < i; j++)
        cpu->VetorDeProgramas[j] = (char*) malloc (sizeof (char) * TAM_INST);
    
    int c;
    for (c = 0; c < i; c++){
        strcpy(cpu->VetorDeProgramas[c], novoprocesso->vetorPrograma[c]);
    }
}


//Coloca o que esta na cpu no processo
void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo, Memoria *memoria){
    processo->tamanhoMemoriaDoProcesso = cpu->tamanhoMemoriaProcessoAtual;
    processo->memoriaDoProcesso = NULL;
	processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * processo->tamanhoMemoriaDoProcesso);
	for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
		processo->memoriaDoProcesso[i] = memoria->vetorMemoria[i+cpu->inicioMemoriaProcessoAtual]; // soma o endereço do inicio do processo que está na cpu.
	}
}

// Copia o contéudo da memória principal para o processo
void copiarMemoriaCpu(Memoria *memoria, Processo *processo){
    printf("Tamanho Memoria Processo: %d\n", processo->tamanhoMemoriaDoProcesso);
    printf("Inicio Memoria Processo: %d\n", processo->inicioMemoria);
 	if(processo->memoriaDoProcesso != NULL){
 		for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
 			memoria->vetorMemoria[i+processo->inicioMemoria] = processo->memoriaDoProcesso[i];
 		}
 	}
}


void alocarVetorPrograma(CPU *cpu, Processo *processo){

    if(processo->vetorPrograma != NULL){
    	int i;
    	for(i = 1; strcmp(processo->vetorPrograma[i-1], "T") != 0; i++);
    	for (int j = 0; j < i; j++) free(processo->vetorPrograma[j]);
	    free(processo->vetorPrograma);
        processo->vetorPrograma = NULL;
    }

    int i = 1;
    for(i = 1; strcmp(cpu->VetorDeProgramas[i-1], "T") != 0; i++); //calcula numero de instrucoes em i

    processo->vetorPrograma = (char**) malloc (sizeof(char*) * i);
    for (int j = 0; j < i; j++)
        processo->vetorPrograma[j] = (char*) malloc (sizeof (char) * TAM_INST);

    i = 0;
    while(1){
        strcpy(processo->vetorPrograma[i], cpu->VetorDeProgramas[i]);
        if(strcmp(processo->vetorPrograma[i], "T") == 0) break;
        i++;
    }
}

void copiarVetorPrograma(CPU *cpu, Processo *processo){
    int i = 1;

    if(cpu->VetorDeProgramas != NULL){
        int i;
    	for(i = 1; strcmp(cpu->VetorDeProgramas[i-1], "T") != 0; i++);
    	for (int j = 0; j < i; j++) free(cpu->VetorDeProgramas[j]);
	    free(cpu->VetorDeProgramas);
        cpu->VetorDeProgramas = NULL;
    }
    
    for(i = 1; strcmp(processo->vetorPrograma[i-1], "T") != 0; i++); //calcula numero de instrucoes em i

    cpu->VetorDeProgramas = (char**) malloc (sizeof(char*) * i);
    for (int j = 0; j < i; j++)
        cpu->VetorDeProgramas[j] = (char*) malloc (sizeof (char) * TAM_INST);

    i = 0;
    while(1){
        strcpy(cpu->VetorDeProgramas[i], processo->vetorPrograma[i]);
        if(strcmp(cpu->VetorDeProgramas[i], "T") == 0) break;
        i++;
    }
}
