#include <stdio.h>
#include <stdlib.h>
#include "processoSimulado.h"

// A tabela de Processos será um vetor do tipo processo
typedef struct tabelaDeProcessos {
    processo tabelaProcesso[50]; // Esse tamanho pode mudar dependendo dos testes mais tarde
};