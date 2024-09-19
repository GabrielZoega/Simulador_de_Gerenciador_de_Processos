#include "../headers/gerenciadorProcessos.h"

void gerenciarProcesso(int *fd, GerenciadorProcesso *gerenciadorProcesso, int escalonador, MemoriaRAM memoria){
    
    // Inicializa o tempo do sistema e a Tabela de Processos
    iniciaTabela(&(gerenciadorProcesso->tabelaDeProcessos));
    gerenciadorProcesso->tempo = 0;

    // Inicializa as filas de prioridade do gerenciador
    FilasDePrioridade filasDePrioridade;
    FFVazia(&(filasDePrioridade.prioridade0));
    FFVazia(&(filasDePrioridade.prioridade1));
    FFVazia(&(filasDePrioridade.prioridade2));
    FFVazia(&(filasDePrioridade.prioridade3));

    // Inicializa as Filas de Estados
    FFVazia(&(gerenciadorProcesso->estadoBloqueado));
    FFVazia(&(gerenciadorProcesso->estadoPronto));
    gerenciadorProcesso->estadoExecucao.processoExec[0] = 0;


    // Cria o processo Pai simulado
    Processo *processoPaiSimulado = &(gerenciadorProcesso->tabelaDeProcessos.processos[0]);
    int ids = 0;

    // Inicializa os campos do processo Pai
    init(processoPaiSimulado, INIT, &ids, gerenciadorProcesso->tempo);
    alocarProcesso(&(gerenciadorProcesso->processadores.CPUs[0]), processoPaiSimulado);
    gerenciadorProcesso->processadores.cpusSendoUtilizadas = 1;
    gerenciadorProcesso->processadores.ultimaCpuUsada = 0;
    gerenciadorProcesso->processadores.CPUs[0].cpuOcupada = OCUPADA;


    char comandoEntrada;

    // Fecha a entrada de escrita do pipe
    close (fd[1]);

    while(1){
        // lendo o que foi escrito no pipe, e armazenando em comandoEntrada
        if(LerPipe(fd[0], &comandoEntrada) == -1){
            comandoEntrada = 'M';
            break;
        }

        if (comandoEntrada == 'U'){
            // Itera as CPUs e executa uma instrução a cada U lido
            int i;
            char instrucao;
            for (i = 0; i < gerenciadorProcesso->processadores.numCpus; i++){
                if (gerenciadorProcesso->processadores.CPUs[i].cpuOcupada == OCUPADA) continue;

                // Executa e retorna a instrução que foi executada
                instrucao = executaInstrucao(gerenciadorProcesso, &ids, escalonador, &filasDePrioridade, i, memoria);

                // Confere o tipo de escalonador e decide se é necessário escalonar ou não
                if(escalonador == FILA_DE_PRIORIDADE){
                    conferePrioridade(gerenciadorProcesso, i);
                    if(gerenciadorProcesso->processadores.CPUs[i].FatiaQuantumAtual == gerenciadorProcesso->processadores.CPUs[i].TempoUsadoProcesso
                    && (instrucao == 'T' || (instrucao == 'F' && gerenciadorProcesso->processadores.numCpus > 1) )){
                        escalonadorFilaPrioridade(gerenciadorProcesso, &filasDePrioridade, escalonador, i, memoria);
                    }
                }
                else if (escalonador == ROUND_ROBIN){
                    if (gerenciadorProcesso->tabelaDeProcessos.quantidadeDeProcessos > 1)
                        trocaDeContexto(gerenciadorProcesso, &filasDePrioridade, escalonador, i, memoria);
                }
            }
            // Incrementa o tempo do sistema e confere se algum processo deve ser desbloqueado
            gerenciadorProcesso->tempo++;
            desbloqueiaProcessos(gerenciadorProcesso, &filasDePrioridade);
        }
        else if(comandoEntrada == 'I'){
            // Apresenta todos os componentes do sistema
            ApresentarTudo(gerenciadorProcesso, memoria);
            printf(INICIO2 "\nComandos:" FINAL "\n", BOLD, UNDERLINE);
        }
        else if(comandoEntrada == 'M'){
            // Apresenta todos os componentes do sistema e encerra o programa
            ApresentarTudo(gerenciadorProcesso, memoria);
            Asteriscos(FUNDO_VERMELHO);
            break;
        }
        else{
            // Encerra o programa em caso de uma entrada inválida
            printf("\n" INICIO3 "Um comando inválido foi digitado!" FINAL "\n", BOLD, VERMELHO, PISCAR);
			printf("\n" INICIO2 "Programa Encerrado!" FINAL "\n", BOLD, VERMELHO);
			Asteriscos(FUNDO_VERMELHO);
            break;
        }
    }
    
    // Verifica se ainda existem processos a serem executados
    if(gerenciadorProcesso->tabelaDeProcessos.quantidadeDeProcessos <= 0)
        printf("\n" INICIO3 "Não ha mais processos em execução, digite M para encerrar o programa" FINAL "\n", BOLD, VERMELHO, PISCAR);
}

// Inicia um processo
void init(Processo *processoSimulado, char *path, int *ids, int tempo){  
    processoSimulado->idProcesso = *ids;
    (*ids)++;
    processoSimulado->idProcessoPai = -1;
    processoSimulado->inicioTempo = tempo;
    processoSimulado->estado = EM_EXECUCAO;
    processoSimulado->prioridade = 0;
    processoSimulado->programCounter = 0;
    processoSimulado->tempoUsadoCPU = 0;
    processoSimulado->tempoBloqueado = -1;
    processoSimulado->memoriaDoProcesso = NULL;
    lerInstrucoes(processoSimulado, path);
}


char executaInstrucao(GerenciadorProcesso *gerenciadorProcesso, int *ids, int escalonador, FilasDePrioridade *filasDePrioridade, int cpuAtual, MemoriaRAM memoria){


}