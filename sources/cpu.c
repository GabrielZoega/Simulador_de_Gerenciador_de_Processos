#include "../headers/cpu.h"

void inicializaCPU(CPU *cpu){
    cpu->PC_Atual = 0;
    cpu->VetorDeProgramas = NULL;
    cpu->FatiaQuantum = 0;
    cpu->cpuOcupada = DESOCUPADA;
}

void AlocarProcesso(CPU *cpu, Processo *novoprocesso){
	int i = 0;
    cpu->idprocesso = novoprocesso->idProcesso; //id do processo em execução
    cpu->PC_Atual = novoprocesso->programCounter; //PC atualizado
    cpu->FatiaQuantum = 0;

    if(cpu->VetorDeProgramas != NULL){
		int i;
		for(i = 1; strcmp(cpu->VetorDeProgramas[i-1], "T") != 0; i++);
		for (int j = 0; j < i; j++) free(cpu->VetorDeProgramas[j]);
		free(cpu->VetorDeProgramas);
		cpu->VetorDeProgramas = NULL;
	}

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
	processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * processo->tamanhoMemoriaDoProcesso); //esse tamanho foi colocado na troca de contexto antes da chamada da função.
	for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){ // aqui o for tem o tamanho do processo pois a memória tem um tamanho maior.
		processo->memoriaDoProcesso[i] = memoria->vetorMemoria[i+cpu->inicioMemoriaProcessoAtual]; // soma o endereço do inicio do processo que está na cpu.
	}
}

// Declaração Antiga
// //Coloca o que esta na cpu no processo
// void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo){
// 	if(cpu->MemoriaSimulada != NULL){
// 		processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * cpu->tamanhoMemoriaSimulada);
// 		processo->tamanhoMemoriaDoProcesso = cpu->tamanhoMemoriaSimulada;
// 		for(int i = 0; i < cpu->tamanhoMemoriaSimulada; i++){
// 			processo->memoriaDoProcesso[i] = cpu->MemoriaSimulada[i];
// 		}
// 	}
// }

// TODO: pensar se ainda vamos precisar dessa instrução (Talvez seja necessário caso a gente tire algum processo da memória principal e depois precise colocar lá de novo)
// Pega o que está no processo e coloca na CPU (caso precise, fazer isso usando o Next fit tbm?)
void copiarMemoriaCpu(Memoria *memoria, Processo *processo){
    printf("Tamanho Memoria Processo: %d\n", processo->tamanhoMemoriaDoProcesso);
    printf("Inicio Memoria Processo: %d\n", processo->inicioMemoria);
 	if(processo->memoriaDoProcesso != NULL){
 		for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
 			memoria->vetorMemoria[i+processo->inicioMemoria] = processo->memoriaDoProcesso[i];
 		}
 	}
}

// Declaração Antiga
// void alocarMemoriaCpu(CPU *cpu, Processo *processo){
// 	if(processo->memoriaDoProcesso != NULL){
// 		if(cpu->MemoriaSimulada != NULL){
// 			free(cpu->MemoriaSimulada);
// 			cpu->MemoriaSimulada = NULL;
// 		}
// 		cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * processo->tamanhoMemoriaDoProcesso);
// 		cpu->tamanhoMemoriaSimulada = processo->tamanhoMemoriaDoProcesso;
// 		for(int i = 0; i < cpu->tamanhoMemoriaSimulada; i++){
// 			cpu->MemoriaSimulada[i] = processo->memoriaDoProcesso[i];
// 		}
// 	}
// }

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
