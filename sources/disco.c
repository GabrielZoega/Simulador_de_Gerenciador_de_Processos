#include "../headers/disco.h"

void iniciaDisco(Disco *disco){
	disco->ultimaPosicao = 0;
	for (int i = 0; i < TAM_DISCO; ++i) {
		disco->vetorDisco[i] = INT_MIN;
	}
}

Segmento retiraSegmentoDeProcesso(Disco *disco, Processo processo){
	Segmento segmento;
	segmento.idProcesso = processo.idProcesso;
	segmento.posicaoInicio = processo.inicioDisco;
	segmento.tamanho = processo.tamanhoMemoriaDoProcesso;
	return segmento;
}

void copiaParaODisco(Disco *disco, Memoria *memoria, Processo processo){
	for(int i = 0; i < processo.tamanhoMemoriaDoProcesso; i++){

	}
}

VetorSegmentos getSegmentosLivres(Disco *disco){
	int numSegmentosLivres = 0;
	int ehUmNovoSegmento = 1;
	for (int i = 0; i < TAM_DISCO; i++){
		if (disco->vetorDisco[i] == INT_MIN && ehUmNovoSegmento) {
			numSegmentosLivres++;
			ehUmNovoSegmento = 0;

		}else if (disco->vetorDisco[i] != INT_MIN && !ehUmNovoSegmento){
			ehUmNovoSegmento = 1;
		}
	}

	VetorSegmentos vetorSegmentos;
	vetorSegmentos.segmentos = (Segmento*) malloc(sizeof(Segmento) * numSegmentosLivres);
	vetorSegmentos.numSegmentos = numSegmentosLivres;

// guarda os tamanhos de cada segmento e suas respectivas posicoes

	numSegmentosLivres = 0;
	ehUmNovoSegmento = 1;
	for (int i = 0; i < TAM_DISCO; i++) {
		if (disco->vetorDisco[i] == INT_MIN && ehUmNovoSegmento) {
			vetorSegmentos.segmentos[numSegmentosLivres].posicaoInicio =  i;
			vetorSegmentos.segmentos[numSegmentosLivres].tamanho = 0;
            vetorSegmentos.segmentos[numSegmentosLivres].idProcesso = -1;
			numSegmentosLivres++;
			ehUmNovoSegmento = 0;

		}else if (disco->vetorDisco[i] != INT_MIN && !ehUmNovoSegmento){
			ehUmNovoSegmento = 1;
		}
		if (disco->vetorDisco[i] == INT_MIN){
			vetorSegmentos.segmentos[numSegmentosLivres-1].tamanho++;
		}
	}
	return vetorSegmentos;
}