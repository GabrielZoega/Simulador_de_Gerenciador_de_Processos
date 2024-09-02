#include "../headers/firstFit.h"

// Acha uma lacuna na memória
int achaLacunaFF(Memoria *memoria, int *posicaoInicio, int *lacuna){
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

void firstFit(Memoria *memoria, int tamanhoProcesso, int *enderecoInicio, TabelaDeProcessos *tabelaDeProcessos, Disco *disco, int *movimentosParaODisco, int *numeroNosPercorridos){
    // --------------------------------------------------------------------------------------------------------
    int posicaoInicio = 0;
    int posicaoFinal;
    int lacuna;
    int controle = 1;

    while(controle == 1){
        (*numeroNosPercorridos)++;
        controle = achaLacunaFF(memoria, &posicaoInicio, &lacuna);
        // Confere se a coluna encontrada cabe o processo
        if (lacuna >= tamanhoProcesso){
            *(enderecoInicio) = posicaoInicio;
            break;
        }
        else{
            posicaoFinal++;
            posicaoInicio = posicaoFinal;
        }
    }
    if(controle == 0){
        // Retira um processo da memória caso nenhuma lacuna tenha sido encontrada
        retiraProcessosDaMemoria(disco, memoria, tabelaDeProcessos, tamanhoProcesso, movimentosParaODisco);
        controle = 1;
        return;
    }

    for(int k = posicaoInicio; k < (posicaoInicio + tamanhoProcesso); k++){
        memoria->vetorMemoria[k] = -1; // -1 para dizer que ta alocado
    }
    return;
// --------------------------------------------------------------------------------------------------------
}