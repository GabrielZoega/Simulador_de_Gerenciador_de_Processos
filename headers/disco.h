#ifndef DISCO_H
#define DISCO_H

#include "memoriaPrincipalBase.h"
#include "processoSimulado.h"

#define TAM_DISCO 500

typedef struct disco{
	int vetorDisco[TAM_DISCO];
	int ultimaPosicao;
}Disco;

void criaDisco(Disco *disco);
Segmento getSegmentoDeProcesso(Disco *disco, int idProcesso);

#endif