#include "../headers/pipe.h"

void EscreverPipe(int fd, char *caractere){
    //escrever dados no pipe
    write(fd, caractere, sizeof(caractere));
}
void LerPipe(int fd, char *caractere){
    //ler dados do pipe,aramazena em retorno e retorna o valor lido,comunicação entre processos
    // char retorno;
    read(fd, caractere, sizeof(char));
    // return ca;
}