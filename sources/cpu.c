#include "../headers/cpu.h"

void inicializaCPU(CPU *cpu){
    cpu->PC_Atual = 0;
    cpu->MemoriaSimulada = NULL;
    cpu->VetorDeProgramas = NULL;
    cpu->FatiaQuantum = 0;
}

void AlocarProcesso(CPU *cpu, Processo *novoprocesso){
	int i = 0;
    cpu->idprocesso = novoprocesso->idProcesso; //id do processo em execução
    cpu->PC_Atual = novoprocesso->programCounter; //PC atualizado
    cpu->FatiaQuantum = 0;
    
    // if (cpu->VetorDeProgramas != NULL){
    //     free(cpu->VetorDeProgramas);
    //     cpu->VetorDeProgramas = NULL;
    // }

    //if (novoprocesso->vetorPrograma == NULL) printf("--- ERRRRRRRRRO ---\n");
    for(i = 1; novoprocesso->vetorPrograma[i-1][0] != 'T'; i++); //printf("na CPU: %s", novoprocesso->vetorPrograma[i-1]); //calcula numero de instrucoes em i
    //printf("--- ENTROU ALOCAR PROCESSO ---\n");
   
    cpu->VetorDeProgramas = (char**) malloc (sizeof(char*) * i);
    for (int j = 0; j < i; j++)
        cpu->VetorDeProgramas[j] = (char*) malloc (sizeof (char) * TAM_INST);
    
    int c;
    for (c = 0; c < i; c++){
        strcpy(cpu->VetorDeProgramas[c], novoprocesso->vetorPrograma[c]);
    }
}


//Coloca o que esta na cpu no processo
void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo){
	if(cpu->MemoriaSimulada != NULL){
		processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * cpu->tamanhoMemoriaSimulada);
		processo->tamanhoMemoriaDoProcesso = cpu->tamanhoMemoriaSimulada;
		for(int i = 0; i < cpu->tamanhoMemoriaSimulada; i++){
			processo->memoriaDoProcesso[i] = cpu->MemoriaSimulada[i];
		}
	}
}

void alocarMemoriaCpu(CPU *cpu, Processo *processo){
	if(processo->memoriaDoProcesso != NULL){
		if(cpu->MemoriaSimulada != NULL){
			free(cpu->MemoriaSimulada);
			cpu->MemoriaSimulada = NULL;
		}
		cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * processo->tamanhoMemoriaDoProcesso);
		cpu->tamanhoMemoriaSimulada = processo->tamanhoMemoriaDoProcesso;
		for(int i = 0; i < cpu->tamanhoMemoriaSimulada; i++){
			cpu->MemoriaSimulada[i] = processo->memoriaDoProcesso[i];
		}
        //printf("--- ENTROU ALOCAR MEMORIA CPU ---\n");
	}
}


void copiarMemoriaDoProcesso(CPU *cpu, Processo *processo){
    cpu->tamanhoMemoriaSimulada = processo->tamanhoMemoriaDoProcesso;
    for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
        cpu->MemoriaSimulada[i] = processo->memoriaDoProcesso[i];
    }
}

//TODO conferir se precisa liberar a memoria da cpu antes de copiar as instrucoes
void alocarVetorPrograma(CPU *cpu, Processo *processo){
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
