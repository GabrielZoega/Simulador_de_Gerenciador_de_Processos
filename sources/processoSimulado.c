#include "../headers/processoSimulado.h"


void lerInstrucoes(Processo *processo, char *pathProcesso){
    FILE *arquivo_de_processo;
    char linhaDeInstrucao[TAM_INST];

    int numInstrucoes = 0;

    // recupera a quantidade de instrucoes do arquivo
    if ((arquivo_de_processo = fopen(pathProcesso, "r")) == NULL){
        printf("\n" INICIO3 "Não foi possível ler o arquivo!" FINAL "\n", VERMELHO, BOLD, PISCAR);
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
        printf("\n" INICIO3 "Não foi possível ler o arquivo!" FINAL "\n", VERMELHO, BOLD, PISCAR);

    }else{
        for(int i = 0; i < numInstrucoes; i++){
            fgets(linhaDeInstrucao, TAM_INST, arquivo_de_processo);
            strcpy(processo->vetorPrograma[i], linhaDeInstrucao);
        }
    }   
    fclose(arquivo_de_processo);
}
