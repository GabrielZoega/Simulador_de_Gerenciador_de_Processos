#include "headers/Pcontrole.h"
#include "headers/gerenciadorProcessos.h"
#include "headers/memoriaPrincipalBase.h"
#include "headers/disco.h"

int main(){
    GerenciadorProcesso gerenciadorProcesso;
    Memoria memoria;
    Disco disco;
    iniciaDisco(&disco);

    system("clear");
	printf("\nDigite o tamanho desejado para a memoria: ");
	scanf("%d", &(memoria.tamanho));
	criaMemoria(&memoria);

    int tecnicaAlocacao;

    system("clear");
    printf("\nEscolha a tecnica de alocacao/desalocacao de memoria:\n\n");
	printf("Digite '1' para usar first fit\n");
	printf("Digite '2' para usar next fit\n");
    printf("Digite '3' para usar best fit\n");
	printf("Digite '4' para usar worst fit\n");
	printf("Digite '0' para encerrar o programa \n");
	printf("Tecnica escolhida: ");
	scanf("%d", &tecnicaAlocacao);

    if (tecnicaAlocacao != 1 && tecnicaAlocacao != 2 && tecnicaAlocacao != 3 && tecnicaAlocacao != 4){
		printf("Programa encerrado.\n\n");
		return 0;
	}

    system("clear");
    printf("\nDigite o numero de processadores para a execucao: ");
    scanf("%d", &(gerenciadorProcesso.vetorCPUS.numeroDeProcessadores));
    CPU CPUS[gerenciadorProcesso.vetorCPUS.numeroDeProcessadores];
    gerenciadorProcesso.vetorCPUS.processadores = CPUS;
    int EXEC[gerenciadorProcesso.vetorCPUS.numeroDeProcessadores];
    gerenciadorProcesso.estadoExecucao.processoExec = EXEC;

    // Inicializando as CPUS e estados de execucao
    int i;
    for(i = 0; i < gerenciadorProcesso.vetorCPUS.numeroDeProcessadores; i++){
        inicializaCPU(&(gerenciadorProcesso.vetorCPUS.processadores[i]));
        EXEC[i] = -1;
        //if (gerenciadorProcesso.vetorCPUS.processadores[i].MemoriaSimulada == NULL) printf("NULL\n");
    }

    int fd[2]; // File descriptors pro Pipe
    int pid; // Variavel para armazenar o pid
    int pipeRetorno = pipe(fd);
    int opcao, escalonador;
    
    system("clear");
    printf("\nEscolha o escalonador para o gerenciador de processos:\n\n");
	printf("Digite '1' para usar Fila de Prioridade\n");
	printf("Digite '2' para usar Round Robin\n");
	printf("Digite '0' para encerrar o programa \n");
	printf("Escalonador escolhido: ");
	scanf("%d", &escalonador);

	system("clear");

	if (escalonador != FILA_DE_PRIORIDADE && escalonador != ROUND_ROBIN ){
		printf("Programa encerrado.\n\n");
		return 0;
	}

    printf("\nEscolha a forma de entrar com os comandos do processo controle:\n\n");
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
                gerenciarProcesso(fd, &gerenciadorProcesso, escalonador, &memoria, &disco, tecnicaAlocacao);
            }
                
        // leitura por arquivo
        }else if (opcao == 2){

            // Processo Pai (Processo Controle)
            if (pid > 0){

                FILE *arq = NULL;
                Pcontrole(arq, opcao, fd);
                
            // Processo Filho (Processo Gerenciador de Processos)
            }else{
                gerenciarProcesso(fd, &gerenciadorProcesso, escalonador, &memoria, &disco, tecnicaAlocacao);
            }
        }
    }else{
        perror("pipe") ;
        return -1 ;
    }

    return 0;
}