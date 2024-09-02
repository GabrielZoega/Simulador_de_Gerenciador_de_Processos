#include "../headers/worstFit.h"

Segmento worstFit(Disco * disco, Memoria* memoria, TabelaDeProcessos* tabela, int N, int *movimentosParaODisco, int *numeroNosPercorridos) {
    (*numeroNosPercorridos)++;
    VetorSegmentos Vsegmento = getSegmentosLivres(memoria);
    Segmento segFinal;
    segFinal.tamanho = 0;  

    // Percorre os segmentos livres para encontrar o maior.
    for (int i = 0; i < Vsegmento.numSegmentos; i++) {
        // Apenas considera os segmentos que podem acomodar o processo.
        if (Vsegmento.segmentos[i].tamanho >= N) {
            // Se o segmento atual for maior que o maior encontrado , atualiza segFinal.
            if (Vsegmento.segmentos[i].tamanho > segFinal.tamanho) {
                segFinal = Vsegmento.segmentos[i];
            }
        }
    }

    // Se um segmento adequado for encontrado,retornar ele 
    if (segFinal.tamanho >= N) {
        return segFinal;
    }

    // Se não houver segmento livre suficiente, tenta desalocar algum processo e encontrar espaço novamente.
    retiraProcessosDaMemoria(disco, memoria, tabela, N, movimentosParaODisco);
    segFinal = worstFit(disco, memoria, tabela, N, movimentosParaODisco, numeroNosPercorridos);
    return segFinal;
}

