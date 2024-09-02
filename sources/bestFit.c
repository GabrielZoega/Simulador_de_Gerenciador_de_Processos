#include "../headers/bestFit.h"

/* Função que retorna o segmento livre por meio do algoritmo BestFit. */
Segmento bestFit(Disco *disco, Memoria* memoria, TabelaDeProcessos* tabela, int N, int *movimentosParaODisco, int *numeroNosPercorridos){
	(*numeroNosPercorridos)++;
	VetorSegmentos Vsegmento =  getSegmentosLivres(memoria);
	int i;
	Segmento segFinal;
	segFinal.tamanho = memoria->tamanho + 1;
	/* Percorre os segmentos livres */
	for(i = 0; i < Vsegmento.numSegmentos; i++){
		/* Será analisado os segmentos que tiverem tamanho mínimo de N */
		if (Vsegmento.segmentos[i].tamanho >= N){

			/* Se o segmento atual tiver o tamanho mais próximo de N que o mais próximo até o momento,
			então ele será o melhor */
			if (abs(Vsegmento.segmentos[i].tamanho - N) < abs(segFinal.tamanho - N)){
				segFinal = Vsegmento.segmentos[i];
			}
		}
	}

	/* Se o tamanho do segmento final for no máximo o tamanho da memória, então foi encontrado algum segmento. */
	if (segFinal.tamanho < (memoria->tamanho + 1)) return segFinal;

	/* Se não for encontrado um segmento livre de no mínimo tamanho N, tenta levar algum processo para o disco */
	// segFinal = bestFitDisco(memoria, tabela, N);
    retiraProcessosDaMemoria(disco, memoria, tabela, N, movimentosParaODisco);
    segFinal = bestFit(disco, memoria, tabela, N, movimentosParaODisco, numeroNosPercorridos);
	return segFinal;
}

