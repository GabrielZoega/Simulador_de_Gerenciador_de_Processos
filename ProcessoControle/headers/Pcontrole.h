#include "../../Pipe/headers/pipe.h"

//o usuário do seu simulador irá escolher entre duas opções: 
//lê comandos repetidamente a partir da entrada padrão ou a partir de um arquivo

//lerá/Receberá um caractere por vez
char Pcontrole(FILE *ptr, int opcao, int LinhaLeitura);

/* Função para o comando I */
void PImpressao();

/* Função para o comando M */
void MFinaliza();