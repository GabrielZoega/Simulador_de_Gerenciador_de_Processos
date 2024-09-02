#include "../headers/firstFit.h"

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
        printf("Tamanho da lacuna: %d\n", lacuna);
        printf("Posicao Inicial: %d\n", posicaoInicio);
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
        printf("Não há espaço para o processo!\n");
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