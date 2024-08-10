#ifndef TERMINALFORMAT_H
#define TERMINALFORMAT_H
/************************** Constantes para formatação de saída no terminal ***********************************/

/*  COR  */
#define BRANCO 37
#define VERDE_AGUA 36
#define ROXO 35
#define AZUL 34
#define AMARELO 33
#define VERDE 32
#define VERMELHO 31
#define PRETO 30

/*  COR DE FUNDO  */
#define FUNDO_BRANCO 47
#define FUNDO_VERDE_AGUA 46
#define FUNDO_ROXO 45
#define FUNDO_AZUL 44
#define FUNDO_AMARELO 43
#define FUNDO_VERDE 42
#define FUNDO_VERMELHO 41
#define FUNDO_PRETO 40

/*  ESTILIZAÇÃO DE TEXTO  */
#define BOLD 1
#define FRACO 2
#define ITALICO 3
#define UNDERLINE 4
#define PISCAR 5
#define INVERTIDO 7
#define OCULTO 8
#define CORTADO 9


/* Final e Início do formato */
#define FINAL "\033[m"
#define INICIO1 "\033[%dm"
#define INICIO2 "\033[%d;%dm"
#define INICIO3 "\033[%d;%d;%dm"
#define INICIO4 "\033[%d;%d;%d;%dm"
#define INICIO5 "\033[%d;%d;%d;%d;%dm"

/**************************************************************************************************************/

#endif
