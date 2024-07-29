#include "../headers/Pcontrole.h"

char Pcontrole(FILE *ptr, int opcao, int LinhaLeitura){
    //opcao = 1, ler do terminal
    //opcao = 2, ler de um arquivo
    //O arquivo deverá ter o tamanho do Pipe
    char ConteudoArquivo[TAMANHOPIPE];
    char retorno;
    if(opcao==1){
        //terminal
        scanf("%c",&retorno);
    }else if(opcao == 2){
        //Primeira Implementação: Ler um caractere por vez do arquivo
        if(fgets(ConteudoArquivo,TAMANHOPIPE,ptr)!=NULL){
            retorno = ConteudoArquivo[LinhaLeitura];
        }
    }else{
        //Opção Inválida
        retorno = ' ';
    }
    
    return retorno;
}


void PImpressao() {
    /* Imprime estado atual do sistema */
}

void MFinaliza(){
    PImpressao();
    /* imprime tempo médio de resposta */
    exit(0);
}