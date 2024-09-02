#ifndef WORSTFIT_H
#define WORSTFIT_H

#include "memoriaPrincipalBase.h"
#include "tabelaDeProcessos.h"
#include "../headers/disco.h"

// Não sei se precisa , mas fiz ela porque ela remove um processo específico da memória principal libera o espaço ocupado 
// e simula sua transferência para o disco e atualiza a tabela de processos.
//Se não precisar só remover e atualizar worst fit
// void moveProcessoParaDisco(Memoria* memoria, Segmento segmento, TabelaDeProcessos* tabela);

Segmento worstFit(Disco * disco, Memoria* memoria, TabelaDeProcessos* tabela, int N, int *movimentosParaODisco, int *numeroNosPercorridos) ;
// Segmento worstFitDisco(Memoria* memoria, TabelaDeProcessos* tabela, int N);

#endif