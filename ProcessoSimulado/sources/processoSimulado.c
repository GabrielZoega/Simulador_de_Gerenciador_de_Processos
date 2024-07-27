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
    char linhaDeInstrucao[40];
    char instrucao;
    int x = 0, n = 0;
    char nome_do_arquivo[30];

    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){

    }else{
        while (!feof(arquivo_de_processo)){
            fgets(linhaDeInstrucao, 40, arquivo_de_processo);
            sscanf(linhaDeInstrucao, "%c ", &instrucao);

            switch (instrucao){
            case 'N':
                sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
                instrucaoN(processo, n);
                break;
            case 'D':
                sscanf(linhaDeInstrucao, "%c %d", &instrucao, &x);
                instrucaoD(processo, x);
                break;
            case 'V':
                sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
                instrucaoV(processo, x, n);
                break;
            case 'A':
                sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
                instrucaoA(processo, x, n);
                break;
            case 'S':
                sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
                instrucaoS(processo, x, n);
                break;
            case 'B':
                sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
                instrucaoB(processo, n);
                break;
            case 'T':
                instrucaoT(processo);
                break;
            case 'F':
                sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
                instrucaoF(processo, n);
                break;
            case 'R':
                sscanf(linhaDeInstrucao, "%c %s", &instrucao, nome_do_arquivo);
                instrucaoR(processo, nome_do_arquivo);
                break;
            default:
                break;
            }
        }
    }   
    fclose(arquivo_de_processo);
}