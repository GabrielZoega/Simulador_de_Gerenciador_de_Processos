#ifndef BESTFIT_H
#define BESTFIT_H

#include "memoriaPrincipalBase.h"
#include "tabelaDeProcessos.h"
#include "../headers/disco.h"

Segmento bestFit(Disco *disco, Memoria* memoria, TabelaDeProcessos* tabela, int N, int *movimentosParaODisco, int *numeroNosPercorridos);
// Segmento bestFitDisco(Memoria* memoria, TabelaDeProcessos* tabela, int N);

#endif