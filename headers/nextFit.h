#ifndef NEXTFIT_H
#define NEXTFIT_H
#include <stdio.h>
#include <limits.h>
#include "../headers/memoriaPrincipalBase.h"

int achaLacuna(Memoria *memoria, int *posicaoInicio, int *lacuna);
void nextFit(Memoria *memoria, int tamanhoProcesso, int *ultimaPosicao, int *enderecoInicio);

#endif