#include "../headers/gerenciadorProcessos.h"

void gerenciarProcesso(int *fd){
    // Processo processoSimulado;
    // init(&processoSimulado);

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        LerPipe(fd[0], &comandoEntrada);

        printf("Entrou no filho: %c\n", comandoEntrada);
        
        if(comandoEntrada == 'M') break;
    }
}

void init(Processo *processoSimulado){  
    processoSimulado->idProcesso = 0;
    processoSimulado->idProcessoPai = NULL;
    processoSimulado->inicioTempo = 0;
    processoSimulado->estado = EM_EXECUCAO;
    processoSimulado->prioridade = 0;
    processoSimulado->programCounter = 0;
    processoSimulado->inicioTempo = 0;
    processoSimulado->tempoUsadoCPU = 0;
    processoSimulado->tempoBloqueado = 0;
    lerInstrucoes(processoSimulado, INIT);
}

void executaIntrucao(Processo *processoSimulado, char *linhaDeInstrucao){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;

    sscanf(linhaDeInstrucao, "%c ", &instrucao);

    switch (instrucao){
    case 'N':
        sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
        instrucaoN(processoSimulado, n);
        break;
    case 'D':
        sscanf(linhaDeInstrucao, "%c %d", &instrucao, &x);
        instrucaoD(processoSimulado, x);
        break;
    case 'V':
        sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
        instrucaoV(processoSimulado, x, n);
        break;
    case 'A':
        sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
        instrucaoA(processoSimulado, x, n);
        break;
    case 'S':
        sscanf(linhaDeInstrucao, "%c %d %d", &instrucao, &x, &n);
        instrucaoS(processoSimulado, x, n);
        break;
    case 'B':
        sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
        instrucaoB(processoSimulado, n);
        break;
    case 'T':
        instrucaoT(processoSimulado);
        break;
    case 'F':
        sscanf(linhaDeInstrucao, "%c %d", &instrucao, &n);
        instrucaoF(processoSimulado, n);
        break;
    case 'R':
        sscanf(linhaDeInstrucao, "%c %s", &instrucao, nome_do_arquivo);
        instrucaoR(processoSimulado, nome_do_arquivo);
        break;
    default:
        break;
    }
}