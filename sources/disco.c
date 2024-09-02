#include "../headers/disco.h"

void iniciaDisco(Disco *disco){
	disco->ultimaPosicao = 0;
	for (int i = 0; i < TAM_DISCO; ++i) {
		disco->vetorDisco[i] = INT_MIN;
	}
}

// Retira algumas informações de um segmento do processo.
Segmento retiraSegmentoDeProcesso(Disco *disco, Processo processo){
	Segmento segmento;
	segmento.idProcesso = processo.idProcesso;
	segmento.posicaoInicio = processo.inicioDisco;
	segmento.tamanho = processo.tamanhoMemoriaDoProcesso;
	return segmento;
}

// Move um processo do Disco para a memória
void moveParaAMemoria(Disco *disco, Memoria *memoria, Processo *processo){
	int i;

	// Desalocando o espaço na memória para receber as variáveis do disco. (não sei se realmente precisa disso)
	for(i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
		memoria->vetorMemoria[i+processo->inicioMemoria] = INT_MIN;
	}

	// Copiando o conteúdo do disco para a memória.
	for(i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
		memoria->vetorMemoria[i+processo->inicioMemoria] = disco->vetorDisco[i+processo->inicioDisco];
	}

	// Desalocando o espaço no disco
	for(i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
		disco->vetorDisco[i+processo->inicioDisco] = INT_MIN;
	}
}

// Move um processo da memória para o disco
void moveParaODisco(Disco *disco, Memoria *memoria, Processo *processo, int *movimentosParaODisco){
	VetorSegmentos segmentosLivres = getSegmentosLivresDisco(disco);
	int segmentoEscolhido;
	for (int i = 0; i < segmentosLivres.numSegmentos; i++){
		if (segmentosLivres.segmentos[i].tamanho >= processo->tamanhoMemoriaDoProcesso){
			segmentoEscolhido = segmentosLivres.segmentos[i].posicaoInicio;
			processo->inicioDisco = segmentosLivres.segmentos[i].posicaoInicio;
			break;
		}
	}
	for(int i = 0; i < processo->tamanhoMemoriaDoProcesso; i++){
		disco->vetorDisco[i + segmentoEscolhido] = memoria->vetorMemoria[i + processo->inicioMemoria];
		memoria->vetorMemoria[i + processo->inicioMemoria] = INT_MIN;
	}
	processo->estaNaMemoria = 0;
	(*movimentosParaODisco)++;
}

// Seleciona um vetor de segmentos livros de um disco
VetorSegmentos getSegmentosLivresDisco(Disco *disco){
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
