#include "../headers/nextFit.h"

int achaLacuna(Memoria *memoria, int *posicaoInicio, int *lacuna){
    *lacuna = 0;
    for(int c = *posicaoInicio; c < memoria->tamanho; c++){
        if (memoria->vetorMemoria[c] == INT_MIN ){
            (*lacuna)++;
            if (*lacuna == 1){
                *posicaoInicio = c;
            }
            if((memoria->vetorMemoria[c + 1] != INT_MIN) && ( ((c + 1) <= (memoria->tamanho-1)) || c == memoria->tamanho-1) ){
                return 1;
            }
        }
    }
    return 0;
}
void nextFit(Memoria *memoria, int tamanhoProcesso, int *ultimaPosicao, int *enderecoInicio, TabelaDeProcessos *tabelaDeProcessos, Disco *disco, int *movimentosParaODisco, int *numeroNosPercorridos){

    int posicaoInicio;
    int posicaoFinal;
    int lacuna;
    int controle = 1;

    while(controle == 1){
        (*numeroNosPercorridos)++;
        posicaoInicio = *ultimaPosicao;
        controle = achaLacuna(memoria, &posicaoInicio, &lacuna);
        // Verifica se a lacuna encontrada cabe o processo
        if (lacuna >= tamanhoProcesso){
            *(enderecoInicio) = posicaoInicio;
            break;
        }
        else{
            posicaoFinal++;
            posicaoInicio = posicaoFinal;
        }

        if(controle == 0){
            // Retira um processo da memória caso nenhuma lacuna tenha sido encontrada
            retiraProcessosDaMemoria(disco, memoria, tabelaDeProcessos, tamanhoProcesso, movimentosParaODisco);
            *ultimaPosicao = 0;
            controle = 1;
        }
    }


    for(int k = posicaoInicio; k < (posicaoInicio + tamanhoProcesso); k++){
        memoria->vetorMemoria[k] = -1;
        posicaoFinal = k;
    }
    if(posicaoFinal+1 == memoria->tamanho) posicaoFinal = -1;
    *ultimaPosicao = posicaoFinal+1;
    return;
}

