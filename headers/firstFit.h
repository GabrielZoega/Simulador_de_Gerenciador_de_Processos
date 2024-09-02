#ifndef FIRSTFIT_H
#include "../headers/memoriaPrincipalBase.h"
#include "../headers/disco.h"
#include "../headers/tabelaDeProcessos.h"

int achaLacunaFF(Memoria *memoria, int *posicaoInicio, int *lacuna);
void firstFit(Memoria *memoria, int tamanhoProcesso, int *enderecoInicio, TabelaDeProcessos *tabelaDeProcessos, Disco *disco, int *movimentosParaODisco, int *numeroNosPercorridos);


#endif