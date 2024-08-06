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
    if (pNovo == NULL) return 0;

    pFila->pTras->pProx = pNovo;
    pFila->pTras = pNovo;
    pNovo->indice = indice;
    pNovo->pProx = NULL;
    return 1;
} 

int FDesenfileira(TFila* pFila) {
    Apontador pAux;
    int idProcesso;
    if (FEhVazia(pFila)) return 0;

    pAux = pFila->pFrente;
    pFila->pFrente = pFila->pFrente->pProx;
    
    idProcesso = pAux->indice;
    
    free(pAux);
    return idProcesso;
}

void ImprimeFila(TFila* fila) {
    if (fila->pFrente == NULL) {
        printf("A fila está vazia.\n");
        return;
    }

    Apontador atual = fila->pFrente;
    while (atual != NULL) {
        printf("%d ", atual->indice);
        atual = atual->pProx;
    }
    printf("\n");
}