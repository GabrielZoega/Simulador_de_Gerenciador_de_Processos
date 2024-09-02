#ifndef WORSTFIT_H
#define WORSTFIT_H

#include "memoriaPrincipalBase.h"
#include "tabelaDeProcessos.h"
#include "../headers/disco.h"


Segmento worstFit(Disco * disco, Memoria* memoria, TabelaDeProcessos* tabela, int N, int *movimentosParaODisco, int *numeroNosPercorridos);

#endif