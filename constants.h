// variáveis globais do programa que ditam a ordem que cada coordenada impõe sobre a matriz...
char alphabet[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$=^&*()-_=+[]{}|:;?/>.<,~`";
char fileName[11], username[20];

// Configurações das matrizes
int x, lowermatrix = 0, uppermatrix, bombcount, counter = 0;


// Estrutura de cada célula
struct block
{
    int type;
    int revealed;
    int flag;
} **Matrix ;


// Para as estatísticas do jogador
int segundos, pontos, dia, jganhos, jperdidos;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>