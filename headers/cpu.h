#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processoSimulado.h"
#include "memoriaPrincipalBase.h"

#define OCUPADA 1
#define DESOCUPADA 0

typedef struct CPU{
    int PC_Atual; //valor atual de contador de programa,aponta para um endereço de memória
    char **VetorDeProgramas; //Vetor de Programas
    int inicioMemoriaProcessoAtual; // posição de inicio na memoria do processo atual
    int tamanhoMemoriaProcessoAtual; // o tamanho que o processo atual ocupa na memória
    int idprocesso; //id do processo em execução da cpu
    int FatiaQuantum; // deve guardar o número de unidades de tempo usadas
    int cpuOcupada;
    //int *MemoriaSimulada; //Conjunto de endereços inteiros // Memória Simulada tem que sumir
    //int tamanhoMemoriaSimulada; também irá sumir
}CPU;

// Declarações antigas, deixei aqui pra cado de alguma merda
// void inicializaCPU(CPU *cpu);
// void AlocarProcesso(CPU *cpu, Processo *novoprocesso);
// void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo);
// void alocarMemoriaCpu(CPU *cpu, Processo *processo);
// void copiarMemoriaDoProcesso(CPU *cpu, Processo *processo);
// void alocarVetorPrograma(CPU *cpu, Processo *processo);
// void copiarVetorPrograma(CPU *cpu, Processo *processo);

void inicializaCPU(CPU *cpu);
void AlocarProcesso(CPU *cpu, Processo *novoprocesso);
void alocarMemoriaDoProcesso(CPU *cpu, Processo *processo, Memoria *memoria);
void copiarMemoriaCpu(Memoria *memoria, Processo *processo);
void copiarMemoriaDoProcesso(CPU *cpu, Processo *processo);
void alocarVetorPrograma(CPU *cpu, Processo *processo);
void copiarVetorPrograma(CPU *cpu, Processo *processo);

#endif
