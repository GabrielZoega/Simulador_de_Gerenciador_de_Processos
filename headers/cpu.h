#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include "processoSimulado.h"

typedef struct CPU{
    int PC_Atual; //valor atual de contador de programa,aponta para um endereço de memória
    Processo **VetorDeProgramas; //Vetor de Programas
    int *MemoriaSimulada; //Conjunto de endereços inteiros
    int idprocesso; //id do processo em execução da cpu
    int FatiaQuantum; // deve guardar o número de unidades de tempo usadas

}CPU;

CPU* inicializaCPU();

void AlocarProcesso(CPU *cpu, Processo *novoprocesso);

#endif