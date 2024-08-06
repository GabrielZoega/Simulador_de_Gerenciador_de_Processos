#ifndef FILA_H
#define FILA_H

#include "stdlib.h"
#include "stdio.h"

typedef struct Celula* Apontador;

typedef struct Celula {
    int indice;
    struct Celula* pProx;
} TCelula;

typedef struct TFila {
    Apontador pFrente;
    Apontador pTras;
} TFila;


void FFVazia(TFila* pFila);
int FEhVazia(TFila* pFila);
int FEnfileira(TFila* pFila, int indice);
int FDesenfileira(TFila* pFila);
void ImprimeFila(TFila* fila);

#endif