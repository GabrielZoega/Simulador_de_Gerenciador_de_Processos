#include <stdio.h>
#include <stdlib.h>

typedef struct CPU{
    int *PC_Atual; //valor atual de contador de programa,aponta para um endereço de memória
    //Programas **VetorDeProgramas; //Vetor de Programas
    int **MemoriaSimulada; //??
    int *program_counter; //PC,apontna para um endereço de memória
    int FatiaQuantum; // deve guardar o número de unidades de tempo usadas

}CPU;

void inicializaCPU();