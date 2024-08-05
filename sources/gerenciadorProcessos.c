#include "../headers/gerenciadorProcessos.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso){
    Processo processoSimulado;
    init(&processoSimulado, INIT);
    AlocarProcesso(&gerenciadorProcesso->Cpu, &processoSimulado);

    gerenciadorProcesso->tabelaProcessos.processos[0] = processoSimulado;

    char comandoEntrada;

    // fecha a entrada de escrita do pipe
    close(fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando isso em comandoEntrada
        LerPipe(fd[0], &comandoEntrada);

        printf("Entrou no filho: %c\n", comandoEntrada);
        
        if(comandoEntrada == 'U'){
            executaInstrucao(gerenciadorProcesso);
        }else if(comandoEntrada == 'I'){
            
        }else if(comandoEntrada == 'M'){
            break;
        }
    }
}

void init(Processo *processoSimulado, char *path){  
    processoSimulado->idProcesso = 0;
    processoSimulado->idProcessoPai = -1;
    processoSimulado->inicioTempo = 0;
    processoSimulado->estado = EM_EXECUCAO;
    processoSimulado->prioridade = 0;
    processoSimulado->programCounter = 0;
    processoSimulado->inicioTempo = 0;
    processoSimulado->tempoUsadoCPU = 0;
    processoSimulado->tempoBloqueado = 0;
    lerInstrucoes(processoSimulado, path);
}

void executaInstrucao(GerenciadorProcesso *gerenciadorProcesso){
    char nome_do_arquivo[30];
    char instrucao;
    int x = 0, n = 0;
    Processo processoSimulado;

    sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c ", &instrucao);

    switch (instrucao){
    case 'N':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoN(&(gerenciadorProcesso->Cpu), n);
        break;
    case 'D':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &x);
        instrucaoD(&(gerenciadorProcesso->Cpu), x);
        break;
    case 'V':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoV(&(gerenciadorProcesso->Cpu), x, n);
        break;
    case 'A':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoA(&(gerenciadorProcesso->Cpu), x, n);
        break;
    case 'S':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d %d", &instrucao, &x, &n);
        instrucaoS(&(gerenciadorProcesso->Cpu), x, n);
        break;
    case 'B':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoB(gerenciadorProcesso, n);
        break;
    case 'T':
        instrucaoT(gerenciadorProcesso);
        break;
    case 'F':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %d", &instrucao, &n);
        instrucaoF(gerenciadorProcesso, n);
        break;
    case 'R':
        sscanf(gerenciadorProcesso->Cpu.VetorDeProgramas[gerenciadorProcesso->Cpu.PC_Atual], "%c %s", &instrucao, nome_do_arquivo);
        instrucaoR(gerenciadorProcesso, nome_do_arquivo);
        break;
    default:
        break;
    }
}

void instrucaoN(CPU *Cpu, int n){
    Cpu->MemoriaSimulada = (int*) malloc(sizeof(int) * n);
    Cpu->tamanhoMemoriaSimulada = n;
}

void instrucaoD(CPU *Cpu, int x){
    Cpu->MemoriaSimulada[x] = 0;
    //printf("D %d\n", x);
}

void instrucaoV(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] = n;
    //printf("V %d %d\n", x, n);
}

void instrucaoA(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] += n;
    //printf("A %d %d\n", x, n);
}

void instrucaoS(CPU *Cpu, int x, int n){
    Cpu->MemoriaSimulada[x] -= n;
    //printf("S %d %d\n", x, n);
}

void instrucaoB(GerenciadorProcesso* gerenciadorProcesso, int n){
     gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].estado = BLOQUEADO;
     gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].tempoBloqueado = n;
    //printf("B %d\n", n);
}

void instrucaoT(GerenciadorProcesso* gerenciadorProcesso){
    //printf("T\n");
}

void instrucaoF(GerenciadorProcesso* gerenciadorProcesso, int n){
    //printf("F %d\n", n);
}

void instrucaoR(GerenciadorProcesso* gerenciadorProcesso, char *nome_do_arquivo){
    Processo novoProcesso;
    init(&novoProcesso, nome_do_arquivo);
    trocaDeContexto(gerenciadorProcesso, &novoProcesso);
    //printf("R %s\n", nome_do_arquivo);
}

void trocaDeContexto(GerenciadorProcesso *gerenciadorProcesso, Processo *processoEscalonado){
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].programCounter = gerenciadorProcesso->Cpu.PC_Atual;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].tempoUsadoCPU = gerenciadorProcesso->Cpu.FatiaQuantum;
    gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso].tamanhoMemoriaDoProcesso = gerenciadorProcesso->Cpu.tamanhoMemoriaSimulada;
    alocarMemoriaDoProcesso(&(gerenciadorProcesso->Cpu), &(gerenciadorProcesso->tabelaProcessos.processos[gerenciadorProcesso->Cpu.idprocesso]));
    free(gerenciadorProcesso->Cpu.VetorDeProgramas);

    AlocarProcesso(&gerenciadorProcesso->Cpu, processoEscalonado);
}