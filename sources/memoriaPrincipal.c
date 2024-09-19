#include "../headers/memoriaPrincipal.h"

void iniciaMemoria(MemoriaRAM *memoria, int tamanhoMemoria){
    // Alocando a memória e o vetor de segmentos
    memoria->segmentos = (SegmentoProcesso*) malloc (sizeof(SegmentoProcesso) * tamanhoMemoria);
    memoria->vetorMemoria = (int*) malloc (sizeof(int) * tamanhoMemoria);
    memoria->tamanhoMemoria = tamanhoMemoria;

    // Inicializando a memória com o menor inteiro possível
    for (int i = 0; i < tamanhoMemoria; i++){
        memoria->vetorMemoria[i] = INT_MIN;
    }
}


SegmentoProcesso retornaSegmento(MemoriaRAM memoria, int idProcesso){
    for(int i = 0; i < memoria.tamanhoMemoria; i++){
        if(memoria.segmentos[i].idProcessoMemoria == idProcesso)
            return memoria.segmentos[i];
    }
}