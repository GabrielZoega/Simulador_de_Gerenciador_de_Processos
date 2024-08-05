#include "../headers/escalonador.h"

/* Função que faz o escalonamento por Round Robin */
/* - função é executada a cada final de unidade de tempo. */
/* - indiceCpu é passado se ao terminar a unidade de tempo o processo precisa voltar para o estado pronto, ou seja, quando ele não vai para o estado bloqueado ou terminou de executar. Caso seja um desses casos, o indiceCpu deve ser passado como null. */
int escalonamentoRoundRobin(EstadoPronto*estP, int indiceCpu){
    int indice;
    /* Retira o primeiro da fila para executar. */
    indice = FDesenfileira(estP);

    if (indiceCpu != NULL)
        /* Coloca o que estava executando ao final da fila. */
        FEnfileira(estP, indiceCpu);

    /* Retorna o índice do que deve executar atualmente. */
    return indice;
}
