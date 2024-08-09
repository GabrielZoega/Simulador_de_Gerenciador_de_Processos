#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processoSimulado.h"

#define OCUPADA 1
#define DESOCUPADA 0

typedef struct CPU{
    int PC_Atual; //valor atual de contador de programa,aponta para um endereço de memória
    char **VetorDeProgramas; //Vetor de Programas
    int *MemoriaSimulada; //Conjunto de endereços inteiros
    int idprocesso; //id do processo em execução da cpu
    int FatiaQuantum; // deve guardar o número de unidades de tempo usadas
    int tamanhoMemoriaSimulada;
    int cpuOcupada;
}CPU;

void inicializaCPU(CPU *cpu);
void AlocarProcesso(CPU *cpu, Processo *novoprocesso);
void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo);
void alocarMemoriaCpu(CPU *cpu, Processo *processo);
void copiarMemoriaDoProcesso(CPU *cpu, Processo *processo);
void alocarVetorPrograma(CPU *cpu, Processo *processo);
void copiarVetorPrograma(CPU *cpu, Processo *processo);

#endif
