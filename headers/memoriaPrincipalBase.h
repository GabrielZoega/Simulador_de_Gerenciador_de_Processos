#ifndef MEMORIAPRINCIPALBASE_H
#define MEMORIAPRINCIPALBASE_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct memoria{
	int *vetorMemoria;
	int tamanho;
	int ultimaPosicao;
}Memoria;

typedef struct segmento{
	int posicaoInicio;
	int tamanho;
	int idProcesso; //TODO fazer a parte de pegar o id do processo
}Segmento;

typedef struct vetorSegmentos{
	Segmento *segmentos;
	int numSegmentos;
}VetorSegmentos;

void criaMemoria(Memoria *memoria);
VetorSegmentos getSegmentosLivres(Memoria *memoria);

#endif