#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processoSimulado.h"
#include "memoriaPrincipal.h"

#define OCUPADA 1
#define DESOCUPADA 0

typedef struct CPU{
    int PC_Atual;                           // valor atual de contador de programa, aponta para um endereço de memória
    char **VetorDeProgramas;                // Vetor de Programas contendo as instruçõees
    int idprocesso;                         // id do processo em execução da cpu
    int FatiaQuantumAtual;                  // deve guardar a Fatia Quantum do Processo Atual
    int TempoUsadoProcesso;                 // Tempo de CPU que o processo teve até o tempo atual
    int cpuOcupada;                         // Flag para dizer se a CPU está ocupada
}CPU;

void inicializaCPU(CPU *cpu);
void alocarProcesso(CPU *cpu, Processo *processo);

#endif
