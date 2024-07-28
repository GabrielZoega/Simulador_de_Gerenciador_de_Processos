#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Biblioteca para o uso do pipe()
#include <sys/types.h> // Biblioteca para o uso do fork()
#define TAMANHOPIPE 50 //Tamanho do buffer
 
//Implementação do Pipe segundo: https://acervolima.com/pipe-chamada-de-sistema/
//fd = 0 será o fd (descritor de arquivo) para leitura
//fd = 1 será para escrita
//pipe será um buffer que o processo filho & pai compartilham
void EscreverPipe(int fd,char caractere);
char LerPipe(int fd);