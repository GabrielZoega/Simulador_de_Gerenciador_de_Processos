#ifndef NEXTFIT_H
#define NEXTFIT_H
#include <stdio.h>
#include <limits.h>
#include "../headers/disco.h"
#include "../headers/tabelaDeProcessos.h"

int achaLacuna(Memoria *memoria, int *posicaoInicio, int *lacuna);
void nextFit(Memoria *memoria, int tamanhoProcesso, int *ultimaPosicao, int *enderecoInicio, TabelaDeProcessos *tabelaDeProcessos, Disco *disco, int *movimentosParaODisco, int *numeroNosPercorridos);

#endif