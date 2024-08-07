#include "../headers/fila.h"
void FFVazia(TFila* pFila) {
    pFila->pFrente = (Apontador)malloc(sizeof(TCelula));
    if (pFila->pFrente == NULL) return;

    pFila->pFrente->pProx = NULL;
    pFila->pTras = pFila->pFrente;
} 

int FEhVazia(TFila* pFila) {
    return (pFila->pFrente == pFila->pTras);
}

int FEnfileira(TFila *pFila, int indice) {
    Apontador pNovo;
    pNovo = (Apontador)malloc(sizeof(TCelula));
    if (pNovo == NULL) return 0;

    pNovo->indice = indice;
    pNovo->pProx = NULL;

    pFila->pTras->pProx = pNovo;
    pFila->pTras = pNovo;

    return 1;
}

int FDesenfileira(TFila* pFila) {
    Apontador pAux;
    int idProcesso;
    if (FEhVazia(pFila)) return 0;

    pAux = pFila->pFrente->pProx;

    pFila->pFrente->pProx = pAux->pProx;

    if (pFila->pTras == pAux) {
        pFila->pTras = pFila->pFrente; // Atualiza pTras se estamos removendo o último elemento
    }

    idProcesso = pAux->indice;
    free(pAux);
    return idProcesso;
}