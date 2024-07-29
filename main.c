#include "headers/processoSimulado.h"
#include "headers/pipe.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER 256

int main(void)
{
    int fd[2]; // File descriptors pro Pipe
    int pid; // Variável para armazenar o pid
    int pipeRetorno = pipe(fd);

    int opcao;
    
    printf("Escolha a forma de entrar com os comandos do processo controle:\n\n");
    printf("Digite '1' para entrar pelo terminal \n");
    printf("Digite '2' para entrar por um arquivo \n");
    printf("Digite '0' para encerrar o programa \n");
    printf("Opcao escolhida: ");
    scanf("%d", &opcao);
    getchar();
    
    // Criando nosso Pipe
    if(pipeRetorno >= 0){
       
        // Criando o processo filho
        pid = fork();

        if (pid < 0){
            perror("fork");
            exit(1);
        }

        if (opcao == 1){
            while(1){                
                char comandoSaida;
                scanf("%c", &comandoSaida);
                // Processo Pai (Processo Controle)
                if (pid > 0){
                    // fecha a leitura do pipe
                    close(fd[0]);

                    // Escrevendo a string no pipe
                    EscreverPipe(fd[1], &comandoSaida);
                    // write(fd[1], str, sizeof(str) + 1);
                    exit(0);
                }
                
                // Processo Filho (Processo Gerenciador de Processos)
                else{
                    char comandoEntrada;

                    // fecha a entrada de escrita do pipe
                    close(fd[1]);

                    // Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida'
                    LerPipe(fd[0], &comandoEntrada);
                    // read(fd[0], &comando, sizeof(comando));
                    exit(0);
                }

                if(comandoSaida == 'M') break;
            }
        }else if (opcao == 2){

        }else{
            printf("Programa encerrado.\n\n");
            return 0;
        }

    }else{
        perror("pipe") ;
        return -1 ;
    }

    return 0;
}