#include "../headers/cpu.h"

void inicializaCPU(CPU *cpu){
    cpu->cpuOcupada = DESOCUPADA;
    cpu->FatiaQuantum = 5;
    cpu->PC_Atual = 0;
    cpu->VetorDeProgramas = NULL;
}

void alocarProcesso(CPU *cpu, Processo *processo){
    cpu->idprocesso = processo->idProcesso;
    cpu->PC_Atual = processo->programCounter;
    int k, i;
    
    // Liberando o vetor de programo caso não seja nulo
    if (cpu->VetorDeProgramas != NULL){
        for(k = 1; strcmp(cpu->VetorDeProgramas[k-1], "T") != 0; k++);
        for(i = 0; i < k; i++)
            free(cpu->VetorDeProgramas[i]);
        free(cpu->VetorDeProgramas);
    }

    // Alocando o Vetor de Programa da CPU
    for (k = 1; processo->vetorPrograma[k-1][0] != 'T'; k++);
    cpu->VetorDeProgramas = (char**) malloc (sizeof (char*) * k);
    for (i = 0; i < k; i++)
        cpu->VetorDeProgramas[i] = (char*) malloc (sizeof (char) * TAM_INST);
    
    for (i = 0; i < k; i++)
        strcpy(cpu->VetorDeProgramas[i], processo->vetorPrograma[i]);
}