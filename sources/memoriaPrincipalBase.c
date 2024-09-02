#include "../headers/memoriaPrincipalBase.h"

// Inicializa a memória principal
void criaMemoria(Memoria *memoria){
	memoria->ultimaPosicao = 0;
	memoria->vetorMemoria =  (int*) malloc(sizeof(int) * memoria->tamanho);
	for(int i = 0; i < memoria->tamanho; i++){
		memoria->vetorMemoria[i] =  INT_MIN;
	}
}

// Retorna um vetor de segmentos livres da memória.
VetorSegmentos getSegmentosLivres(Memoria *memoria){
	int numSegmentosLivres = 0;
	int ehUmNovoSegmento = 1;
	for (int i = 0; i < memoria->tamanho; i++){
		if (memoria->vetorMemoria[i] == INT_MIN && ehUmNovoSegmento) {
			numSegmentosLivres++;
			ehUmNovoSegmento = 0;

		}else if (memoria->vetorMemoria[i] != INT_MIN && !ehUmNovoSegmento){
			ehUmNovoSegmento = 1;
		}
	}

	VetorSegmentos vetorSegmentos;
	vetorSegmentos.segmentos = (Segmento*) malloc(sizeof(Segmento) * numSegmentosLivres);
	vetorSegmentos.numSegmentos = numSegmentosLivres;

	// guarda os tamanhos de cada segmento e suas respectivas posicoes
	numSegmentosLivres = 0;
	ehUmNovoSegmento = 1;
	for (int i = 0; i < memoria->tamanho; i++) {
		if (memoria->vetorMemoria[i] == INT_MIN && ehUmNovoSegmento) {
			vetorSegmentos.segmentos[numSegmentosLivres].posicaoInicio =  i;
			vetorSegmentos.segmentos[numSegmentosLivres].tamanho = 0;
            vetorSegmentos.segmentos[numSegmentosLivres].idProcesso = -1;
			numSegmentosLivres++;
			ehUmNovoSegmento = 0;

		}else if (memoria->vetorMemoria[i] != INT_MIN && !ehUmNovoSegmento){
			ehUmNovoSegmento = 1;
		}
		if (memoria->vetorMemoria[i] == INT_MIN){
			vetorSegmentos.segmentos[numSegmentosLivres-1].tamanho++;
		}
	}
	return vetorSegmentos;
}