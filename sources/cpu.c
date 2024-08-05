#include "../headers/cpu.h"

void inicializaCPU(CPU *cpu){
    cpu->PC_Atual = 0;
    cpu->MemoriaSimulada = NULL;
    cpu->VetorDeProgramas = NULL;
    cpu->FatiaQuantum = 0;
}

void AlocarProcesso(CPU *cpu, Processo *novoprocesso){
    int i;
    cpu->idprocesso = novoprocesso->idProcesso; //id do processo em execução
    cpu->PC_Atual  = novoprocesso->programCounter; //PC atualizado
    cpu->FatiaQuantum = 0;
    for(i = 1; novoprocesso->vetorPrograma[i-1][0] != 'T'; i++); //calcula numero de instrucoes em i

    cpu->VetorDeProgramas = (char**) malloc (sizeof(char*) * i);
    for (int j = 0; j < i; j++)
        cpu->VetorDeProgramas[j] = (char*) malloc (sizeof (char) * TAM_INST);
    
    i = 0;
    while(1){
        strcpy(cpu->VetorDeProgramas[i], novoprocesso->vetorPrograma[i]);
        if(novoprocesso->vetorPrograma[i][0] == 'T') break;
        i++;
    }
}

void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo){
    processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * cpu->tamanhoMemoriaSimulada);
    processo->tamanhoMemoriaDoProcesso = cpu->tamanhoMemoriaSimulada;
    for(int i = 0; i < cpu->tamanhoMemoriaSimulada; i++){
        processo->memoriaDoProcesso[i] = cpu->MemoriaSimulada[i];
    }
}

void copiarMemoriaDoProcesso(CPU *cpu, Processo *processo){
    cpu->tamanhoMemoriaSimulada = processo->tamanhoMemoriaDoProcesso;
    for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
        cpu->MemoriaSimulada[i] = processo->memoriaDoProcesso[i];
    }
}