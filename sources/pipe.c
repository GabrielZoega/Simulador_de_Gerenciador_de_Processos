#include "../headers/pipe.h"

void EscreverPipe(int fd, char *caractere){
    //escrever dados no pipe
    write(fd, caractere, sizeof(char));
}
int LerPipe(int fd, char *caractere){
    //ler dados do pipe,aramazena em retorno e retorna o valor lido,comunicação entre processos
    // char retorno;
    return read(fd, caractere, sizeof(char));
}
