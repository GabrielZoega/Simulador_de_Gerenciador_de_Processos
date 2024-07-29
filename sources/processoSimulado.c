#include "../headers/processoSimulado.h"

void instrucaoN(Processo *processo, int n){
    processo->memoriaDoProcesso = (int*) malloc(sizeof(int) * n);
    //printf("N %d\n", n);
}

void instrucaoD(Processo *processo, int x){
    processo->memoriaDoProcesso[x] = 0;
    //printf("D %d\n", x);
}

void instrucaoV(Processo *processo, int x, int n){
    processo->memoriaDoProcesso[x] = n;
    //printf("V %d %d\n", x, n);
}

void instrucaoA(Processo *processo, int x, int n){
    processo->memoriaDoProcesso[x] += n;
    //printf("A %d %d\n", x, n);
}

void instrucaoS(Processo *processo, int x, int n){
    processo->memoriaDoProcesso[x] -= n;
    //printf("S %d %d\n", x, n);
}

void instrucaoB(Processo *processo, int n){
    processo->estado = BLOQUEADO;
    processo->tempoBloqueado = n;
    //printf("B %d\n", n);
}

void instrucaoT(Processo *processo){
    //printf("T\n");    
}

void instrucaoF(Processo *processo, int n){
    //printf("F %d\n", n);
}

void instrucaoR(Processo *processo, char *nome_do_arquivo){
    //printf("R %s\n", nome_do_arquivo);
}

void lerInstrucoes(Processo *processo, char *pathProcesso){
    FILE *arquivo_de_processo;
    char linhaDeInstrucao[TAM_INST];

    int numInstrucoes = 0;

    // recupera a quantidade de instrucoes do arquivo
    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){
        printf("Nao foi possivel ler o arquivo!");
    }else{
        while (!feof(arquivo_de_processo)){
            fgets(linhaDeInstrucao, TAM_INST, arquivo_de_processo);
            numInstrucoes++;           
        }
    }   
    fclose(arquivo_de_processo);

    // aloca a quantidade necessaria de memoria para o vetor de instrucoes
    processo->vetorPrograma = (char**) malloc (sizeof(char*) * numInstrucoes);

    for (int i = 0; i < numInstrucoes; i++)
        processo->vetorPrograma[i] = (char*) malloc (sizeof (char) * TAM_INST);

    // guarda o conteudo de cada linha de instrucao no vetor
    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){
        printf("Nao foi possivel ler o arquivo!");

    }else{
        for(int i = 0; i < numInstrucoes; i++){
            fgets(linhaDeInstrucao, TAM_INST, arquivo_de_processo);
            strcpy(processo->vetorPrograma[i], linhaDeInstrucao);
        }
    }   
    fclose(arquivo_de_processo);
}