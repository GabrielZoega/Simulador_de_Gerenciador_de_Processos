#include <stdio.h>
#include <stdlib.h>
#include "../../ProcessoSimulado/headers/processoSimulado.h"

// A tabela de Processos será um vetor do tipo processo
typedef struct tabelaDeProcessos {
    Processo tabelaProcessos[50];
}TabelaDeProcessos;