#include "../headers/tabelaDeProcessos.h"

void iniciaTabela(TabelaDeProcessos *tabelaDeProcessos){
    for (int i = 0; i < 50; i++){
        tabelaDeProcessos->processos[i].idProcesso = -1;
        tabelaDeProcessos->processos[i].estaNaMemoria = 0;
    }
    tabelaDeProcessos->quantidadeDeProcessos = 1;
}