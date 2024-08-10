#include "../headers/Pcontrole.h"

void Pcontrole(FILE *arq, int opcao, int *fd){
    //opcao = 1, ler do terminal
    //opcao = 2, ler de um arquivo

    char comandoSaida;

    if(opcao==1){
                
        // fecha a leitura do pipe
        close(fd[0]);
        
        printf(INICIO2 "\nComandos:" FINAL "\n", BOLD, UNDERLINE);
        while(1){             
            scanf("%c", &comandoSaida);
            getchar();

//            printf("Saiu do pai: %c\n", comandoSaida);

            // Escrevendo a string no pipe
            EscreverPipe(fd[1], &comandoSaida);
            if((comandoSaida == 'M') | ((comandoSaida != 'U') & (comandoSaida != 'I'))) break;
        }

    }else if(opcao == 2){
        char path[TAMANHO_NOME_ARQ];

        printf("\n" INICIO2 "Insira o caminho do arquivo a ser lido:" FINAL " ", BOLD, UNDERLINE);
        scanf("%s", path);
        
        // fecha a leitura do pipe
        close(fd[0]);
        
        if ((arq = fopen(path, "r")) == NULL){
        	printf("\n" INICIO3 "Não foi possível ler o arquivo!" FINAL "\n", VERMELHO, BOLD, PISCAR);
        
        }else{

            while(!feof(arq)){

                fscanf(arq, "%c\n", &comandoSaida);
                printf("Saiu do pai: %c\n", comandoSaida);

                // Escrevendo a string no pipe
                EscreverPipe(fd[1], &comandoSaida);
                if(comandoSaida == 'M') break;
            }
            
            fclose(arq);
        }
    }

    // return retorno;
}
