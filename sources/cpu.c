#include "../headers/cpu.h"

CPU* inicializaCPU(){
    //alocações de memória para a struct CPU
    CPU* cpu = (CPU*) malloc(sizeof(CPU));
    cpu->PC_Atual = 0;
    cpu->MemoriaSimulada = (int*) malloc(sizeof(int));
    // cpu->MemoriaSimulada = (int**) malloc(sizeof(CPU));
    cpu->FatiaQuantum = 0;
    return cpu;
}

void AlocarProcesso(CPU *cpu, Processo *novoprocesso){
    cpu->idprocesso = novoprocesso->idProcesso; //id do processo em execução
    cpu->PC_Atual  = novoprocesso->programCounter; //PC atualizado
    cpu->MemoriaSimulada = novoprocesso->memoriaDoProcesso; //Memória utilizada atualizada
    cpu->FatiaQuantum = 0;
    
}