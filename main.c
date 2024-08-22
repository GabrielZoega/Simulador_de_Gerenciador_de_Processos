#include "stdlib.h"
#include "stdio.h"

/*  Função que encontra um processo que possui um espaço que melhor se encaixa com o espaço requisitado.
    O processo encontrado é levado para o disco.
    Usada no caso de não ter espaço suficiente na memória.
    -> Retorna o processo que deve ser substituído.
*/
int bestFitParaDisco(char* VetorMemoria, int N, int tamanho ){
    int i;
    int espacoL = 0, espacoLReal = tamanho+1, processo = -1, processoReal = -1, simbolo;
    /* Percorre a memória */
    for(i = 0; i < tamanho; i++){
        /* Salva o número do processo. */
        simbolo = VetorMemoria[i] - '0';

        /* Confere se o processo lido atualmente é o mesmo que o anterior. */
        if (processo == simbolo){
            espacoL++;
        }
        
        else {
            /* Confere se o espaço encontrado atualmente é melhor que o melhor até então. */
            if ((espacoL >= N) && (abs(N - espacoL) < abs(N - espacoLReal))){
                espacoLReal = espacoL;
                processoReal = processo;
                if (espacoLReal == N){
                    printf("Espaço: %d\n", espacoLReal);
                    printf("Processo a ser retirado: %d\n", processoReal);
                    return processoReal;
                }
            }

            /* Reinicia a contagem, pois é um processo diferente. */
            espacoL = 1;
            processo = simbolo;
        }
    }

    /* Confere se o último espaço é melhor que o melhor até então. */
    if ((espacoL >= N) && (abs(N - espacoL) < abs(N - espacoLReal))){
            espacoLReal = espacoL;
            processoReal = processo;
    }

    /* Confere se o espaço encontrado é válido. */
   if ((espacoLReal >= N) && (processoReal != -1)){
        printf("Espaço: %d\n", espacoLReal);
        printf("Processo a ser retirado: %d\n", processoReal);
        return processoReal;
    }
    return -1;
}

/*  Função que encontra a sequência de espaços livres que melhor se encaixa com o espaço requisitado.
    -> Retorna a posição inicial para usar o espaço requisitado.
*/
int bestFit(char* VetorMemoria, int N, int tamanho){
    int i;
    int espacoL = 0, espacoLReal = tamanho+1, posicaoInicial = -1, posicaoInicialReal = -1;
    
    /* Percorre a memória */
    for(i = 0; i < tamanho; i++){

        /* Confere se o espaço atual é vazio. */
        if (VetorMemoria[i] == '_'){
            /* Confere se é o primeiro espaço vazio e marca a posição inicial. */
            if (espacoL == 0)
                posicaoInicial = i;

            espacoL++;
        }
        /* Caso não seja um espaço vazio e acabei de terminar uma sequência de espaços livres.*/
        else if (espacoL != 0){
            /* Confere se o espaço encontrado atualmente é melhor que o melhor até então. */
            if ((espacoL >= N) && (abs(N - espacoL) < abs(N - espacoLReal))){
                espacoLReal = espacoL;
                posicaoInicialReal = posicaoInicial;
                if (espacoLReal == N){
                    printf("Espaço: %d\n", espacoLReal);
                    printf("Posição Inicial: %d\n", posicaoInicialReal);
                    return posicaoInicialReal;
                }
            }
            espacoL = 0;    
        }
    }

    /* Confere se o último espaço é melhor que o melhor até então. */
    if ((espacoL >= N) && (abs(N - espacoL) < abs(N - espacoLReal))){
            espacoLReal = espacoL;
            posicaoInicialReal = posicaoInicial;
    }

    /* Confere se o espaço encontrado é válido. */
    if ((espacoLReal >= N) && (posicaoInicialReal != -1)){
        printf("Espaço: %d\n", espacoLReal);
        printf("Posição Inicial: %d\n", posicaoInicialReal);
        return posicaoInicialReal;
    }
    return -1;
}

int main(){
    char vetor[10] = {'_', '_', '1', '3', '_', '_', '1', '_', '_', '_'};    
    if (bestFit(vetor, 3, 10) == -1)
        bestFitParaDisco(vetor, 3, 10);
}
/*
- número médio de fragmentos externos;
- tempo médio de alocação considerando o número médio de nós percorridos na
alocação;
- número de vezes que um processo teve que ser levado para o "disco", para liberar
espaço na memória;
*/