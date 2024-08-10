#ifndef PCONTROLE_H
#define PCONTROLE_H


#define TAMANHO_NOME_ARQ 60 //Tamanho do buffer

#include "pipe.h"
#include <string.h>
#include "terminal_format.h"

//o usuário do seu simulador irá escolher entre duas opções: 
//lê comandos repetidamente a partir da entrada padrão ou a partir de um arquivo

void Pcontrole(FILE *arq, int opcao, int *fd);

#endif
