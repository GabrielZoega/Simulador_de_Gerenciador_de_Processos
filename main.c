#include "headers/Pcontrole.h"
#include "headers/gerenciadorProcessos.h"
#include "headers/processoImpressao.h"

int main(){
    GerenciadorProcesso gerenciadorProcesso;
    inicializaCPU(&(gerenciadorProcesso.Cpu));
    int fd[2]; // File descriptors pro Pipe
    int pid; // Variavel para armazenar o pid
    int pipeRetorno = pipe(fd);
    int opcao;
    
    printf(INICIO2 "*************************************** Simulador de Gerenciador de Processos ****************************************************" FINAL "\n\n", BOLD, FUNDO_VERMELHO);
    printf(INICIO2 "Escolha a forma de entrar com os comandos do processo controle:\n\n" FINAL, BOLD, UNDERLINE);
    printf(INICIO1 "Digite '1' para entrar pelo terminal \n" FINAL, BOLD);
    printf(INICIO1 "Digite '2' para entrar por um arquivo \n" FINAL, BOLD);
    printf(INICIO1 "Digite '0' para encerrar o programa \n" FINAL, BOLD);
    printf("\n" INICIO2 "Opcao escolhida:" FINAL " ", BOLD, UNDERLINE);
    scanf("%d", &opcao);
    getchar();

    if (opcao != 1 && opcao != 2){
        printf("\n" INICIO2 "Programa encerrado.\n\n" FINAL, BOLD, VERMELHO);
        Asteriscos(FUNDO_VERMELHO);
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
                
            }
            // Processo Filho (Processo Gerenciador de Processos)
            else{
                gerenciarProcesso(fd, &gerenciadorProcesso);                
            }
                
        // leitura por arquivo
        }else if (opcao == 2){

            // Processo Pai (Processo Controle)
            if (pid > 0){

                FILE *arq;
                Pcontrole(arq, opcao, fd);  
            }
            // Processo Filho (Processo Gerenciador de Processos)
            else{
                gerenciarProcesso(fd, &gerenciadorProcesso);
            }
        }
    }else{
        perror("pipe") ;
        return -1 ;
    }

    return 0;
}
