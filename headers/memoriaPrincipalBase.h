#ifndef MEMORIAPRINCIPALBASE_H
#define MEMORIAPRINCIPALBASE_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct memoria{
	int *vetorMemoria;				// Vetor de Inteiros representando a memória
	int tamanho;
	int ultimaPosicao;				// Última posição em que um processo foi alocado (usada no Next Fit)
}Memoria;

typedef struct segmento{
	int posicaoInicio;				// Endereço de inicio de um segmento de memória		
	int tamanho;					// Tamanho desse segmento
	int idProcesso;	
}Segmento;

typedef struct vetorSegmentos{
	Segmento *segmentos;			// Vetor contendo vários segmentos
	int numSegmentos;				// Quantidade de segmentos desse vetor
}VetorSegmentos;

void criaMemoria(Memoria *memoria);
VetorSegmentos getSegmentosLivres(Memoria *memoria);

#endif