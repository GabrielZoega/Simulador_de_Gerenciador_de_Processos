#include "../Simulador_de_Gerenciador_de_Processos/ProcessoSimulado/headers/processoSimulado.h"

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

    int numIntrucoes = 0;

    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){
        printf("Nao foi possivel ler o arquivo!");
    }else{
        while (!feof(arquivo_de_processo)){
            fgets(linhaDeInstrucao, TAM_INST, arquivo_de_processo);
            numIntrucoes++;           
        }
    }   
    fclose(arquivo_de_processo);

    processo->vetorPrograma = (char**) malloc(sizeof(char)*numIntrucoes*TAM_INST);

    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){
        printf("Nao foi possivel ler o arquivo!");

    }else{
        for(int i = 0; i < numIntrucoes; i++){
            fgets(linhaDeInstrucao, TAM_INST, arquivo_de_processo);
            strcpy(processo->vetorPrograma[i], linhaDeInstrucao);
        }
    }   
    fclose(arquivo_de_processo);
}