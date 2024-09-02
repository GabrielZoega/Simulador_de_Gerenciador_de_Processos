#include "../headers/tabelaDeProcessos.h"

VetorSegmentos getSegmentosOcupados(Memoria memoria, TabelaDeProcessos tabelaDeProcessos){
	VetorSegmentos vetorSegmentos;
	vetorSegmentos.segmentos = (Segmento*) malloc(sizeof(Segmento) * tabelaDeProcessos.quantidadeDeProcessos);
    vetorSegmentos.numSegmentos = 0;
	for (int i = 0; i < 50; i++){
        if(tabelaDeProcessos.processos[i].estaNaMemoria && tabelaDeProcessos.processos[i].idProcesso >= 0){
            vetorSegmentos.numSegmentos++;
            vetorSegmentos.segmentos[i].idProcesso = tabelaDeProcessos.processos[i].idProcesso;
            vetorSegmentos.segmentos[i].posicaoInicio = tabelaDeProcessos.processos[i].inicioMemoria;
            vetorSegmentos.segmentos[i].tamanho = tabelaDeProcessos.processos[i].tamanhoMemoriaDoProcesso;
        }
	}

	return vetorSegmentos;
}

void retiraProcessosDaMemoria(Disco *disco, Memoria *memoria, TabelaDeProcessos *tabelaDeProcessos, int tamanhoParaRetirar, int *movimentosParaODisco){
    VetorSegmentos segmentosOcupados;
    int idProcessoMaisVelho;
    
    while(1){
        segmentosOcupados = getSegmentosOcupados(*memoria, *tabelaDeProcessos);
        for (int i = 0; i < segmentosOcupados.numSegmentos; i++){
            if (i == 0) idProcessoMaisVelho = segmentosOcupados.segmentos[i].idProcesso;
            if (tabelaDeProcessos->processos[segmentosOcupados.segmentos[i].idProcesso].tempoUltimoAcessoAMemoria
            < tabelaDeProcessos->processos[idProcessoMaisVelho].tempoUltimoAcessoAMemoria){
                idProcessoMaisVelho = segmentosOcupados.segmentos[i].idProcesso;
            }
        }
        if(tabelaDeProcessos->processos[idProcessoMaisVelho].tamanhoMemoriaDoProcesso >= tamanhoParaRetirar){
            
            moveParaODisco(disco, memoria, &(tabelaDeProcessos->processos[idProcessoMaisVelho]), movimentosParaODisco);
            break;
        }else{
            moveParaODisco(disco, memoria, &(tabelaDeProcessos->processos[idProcessoMaisVelho]), movimentosParaODisco);
            tamanhoParaRetirar -= tabelaDeProcessos->processos[idProcessoMaisVelho].tamanhoMemoriaDoProcesso;
        }
    }
}