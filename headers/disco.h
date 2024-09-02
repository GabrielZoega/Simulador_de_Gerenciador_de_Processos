#ifndef DISCO_H
#define DISCO_H

#include "memoriaPrincipalBase.h"
#include "processoSimulado.h"

#define TAM_DISCO 500

// Vetor de 500 posições representando o disco.
typedef struct disco{
	int vetorDisco[TAM_DISCO];
	int ultimaPosicao;
}Disco;

void iniciaDisco(Disco *disco);
Segmento retiraSegmentoDeProcesso(Disco *disco, Processo processo);
void moveParaAMemoria(Disco *disco, Memoria *memoria, Processo *processo);
void moveParaODisco(Disco *disco, Memoria *memoria, Processo *processo, int *movimentosParaODisco);
VetorSegmentos getSegmentosLivresDisco(Disco *disco);

#endif