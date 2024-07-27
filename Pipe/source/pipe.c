#include "../Simulador_de_Gerenciador_de_Processos/Pipe/headers/pipe.h"

void EscreverPipe(int fd,char caractere){
    //escrever dados no pipe
    write(fd,&caractere,sizeof(caractere));
}
char LerPipe(int fd){
    //ler dados do pipe,aramazena em retorno e retorna o valor lido,comunicação entre processos
    char retorno;
    read(fd,&retorno,sizeof(char));
    return retorno;
}