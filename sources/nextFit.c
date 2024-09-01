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
void nextFit(Memoria *memoria, int tamanhoProcesso, int *ultimaPosicao, int *enderecoInicio){

    int posicaoInicio = *ultimaPosicao;
    int posicaoFinal;
    int lacuna;
    int controle = 1;

    while(controle == 1){
        controle = achaLacuna(memoria, &posicaoInicio, &lacuna);
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
        printf("Não há espaço para o processo!\n"); // aqui provavelmente deveriamos colocar um processo no disco e tentar de novo (teria que colocar esse controle == 0 dentro do while).
        *ultimaPosicao = 0;
        return;
    }

    for(int k = posicaoInicio; k < (posicaoInicio + tamanhoProcesso); k++){
        memoria->vetorMemoria[k] = -1; // -1 será apenas uma forma de dizer que o processo está alocado
        posicaoFinal = k;
    }
    ("Posicao Final: %d\n", posicaoFinal+1);
    if(posicaoFinal+1 == memoria->tamanho) posicaoFinal = -1;
    *ultimaPosicao = posicaoFinal+1;
}