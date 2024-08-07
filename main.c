#include "headers/Pcontrole.h"
#include "headers/gerenciadorProcessos.h"


int main(){
    GerenciadorProcesso gerenciadorProcesso;
    inicializaCPU(&(gerenciadorProcesso.Cpu));
    int fd[2]; // File descriptors pro Pipe
    int pid; // Variavel para armazenar o pid
    int pipeRetorno = pipe(fd);
    int opcao, escalonador;
    
    printf("\nEscolha o escalonador para o gerenciador de processos:\n\n");
	printf("Digite '1' para usar Fila de Prioridade\n");
	printf("Digite '2' para usar Round Robin\n");
	printf("Digite '0' para encerrar o programa \n");
	printf("Escalonador escolhido: ");
	scanf("%d", &escalonador);

	printf("\e[1;1H\e[2J");

	if (escalonador != FILA_DE_PRIORIDADE && escalonador != ROUND_ROBIN ){
		printf("Programa encerrado.\n\n");
		return 0;
	}

    printf("\n\nEscolha a forma de entrar com os comandos do processo controle:\n\n");
    printf("Digite '1' para entrar pelo terminal \n");
    printf("Digite '2' para entrar por um arquivo \n");
    printf("Digite '0' para encerrar o programa \n");
    printf("Opcao escolhida: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao != 1 && opcao != 2 ){
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
                gerenciarProcesso(fd, &gerenciadorProcesso, escalonador);
            }
                
        // leitura por arquivo
        }else if (opcao == 2){

            // Processo Pai (Processo Controle)
            if (pid > 0){

                FILE *arq = NULL;
                Pcontrole(arq, opcao, fd);
                
            // Processo Filho (Processo Gerenciador de Processos)
            }else{
                gerenciarProcesso(fd, &gerenciadorProcesso, escalonador);
            }
        }
    }else{
        perror("pipe") ;
        return -1 ;
    }

    return 0;
}
