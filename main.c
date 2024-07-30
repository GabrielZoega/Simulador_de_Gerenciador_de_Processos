#include "headers/Pcontrole.h"
#include "headers/gerenciadorProcessos.h"
#include "headers/processoSimulado.h"
#include "headers/pipe.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    int fd[2]; // File descriptors pro Pipe
    int pid; // Variavel para armazenar o pid
    int status;
    int pipeRetorno = pipe(fd);
    int opcao;
    
    printf("Escolha a forma de entrar com os comandos do processo controle:\n\n");
    printf("Digite '1' para entrar pelo terminal \n");
    printf("Digite '2' para entrar por um arquivo \n");
    printf("Digite '0' para encerrar o programa \n");
    printf("Opcao escolhida: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao != 1 && opcao != 2){
        printf("Programa encerrado.\n\n");
        return 0;
    }

    // Criando nosso Pipe
    if(pipeRetorno >= 0){
       
        // Criando o processo filho
        pid = fork();

        if (pid < 0){
            perror("fork");
            exit(1);
        }

        // leitura pelo terminal
        if (opcao == 1){
            
            // Processo Pai (Processo Controle)
            if (pid > 0){
                Pcontrole(NULL, opcao, fd);
                
            // Processo Filho (Processo Gerenciador de Processos)
            }else{
                gerenciarProcesso(fd);                
            }
                
        // leitura por arquivo
        }else if (opcao == 2){

            // Processo Pai (Processo Controle)
            if (pid > 0){

                FILE *arq;
                Pcontrole(arq, opcao, fd);
                
            // Processo Filho (Processo Gerenciador de Processos)
            }else{
                gerenciarProcesso(fd);
            }
        }
    }else{
        perror("pipe") ;
        return -1 ;
    }

    return 0;
}