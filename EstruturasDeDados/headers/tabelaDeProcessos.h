#include <stdio.h>
#include <stdlib.h>

// Essa definição talvez seja movida para um arquivo .h separado pra o processo
typedef struct processo{
    int idProcesso;
    int idProcessoPai;
    int* programCounter;
    //dados* dados; teoricamente é um vetor de estruturas de dados (tá escrito assim na especificação), não sabemos extamanete oq é isso
    int prioridade;
    char estado;
    int inicioTempo;
    int tempoUsadoCPU;

};

// A tabela de Processos será um vetor do tipo processo
typedef struct tabelaDeProcessos {
    processo processo[50]; // Esse tamanho pode mudar dependendo dos testes mais tarde
};