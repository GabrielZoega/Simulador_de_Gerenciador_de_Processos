#include "../headers/fila.h"

void FFVazia(TFila* pFila) {
    pFila->pFrente = (Apontador)malloc(sizeof(TCelula));

    pFila->pTras = pFila->pFrente;

    pFila->pFrente->pProx = NULL;
} 

int FEhVazia(TFila* pFila) {
    return (pFila->pFrente == pFila->pTras);
}

int FEnfileira(TFila *pFila, int indice) {
    Apontador pNovo;
    pNovo = (Apontador)malloc(sizeof(TCelula));
    if (pNovo == NULL) return -1;

    pFila->pTras->pProx = pNovo;
    pFila->pTras = pNovo;
    pNovo->indice = indice;
    pNovo->pProx = NULL;
    return 0;
} 

int FDesenfileira(TFila* pFila) {
    Apontador pAux;
    int indice;
    if (FEhVazia(pFila)) return -1;

    pAux = pFila->pFrente;
    indice = pAux->indice;
    pFila->pFrente = pFila->pFrente->pProx;

    free(pAux);
    return indice;
}