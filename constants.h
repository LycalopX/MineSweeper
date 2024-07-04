// variáveis globais do programa que ditam a ordem que cada coordenada impõe sobre a matriz...
char alphabet[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$=^&*()-_=+[]{}|:;?/>.<,~`";


// Estrutura de cada célula
struct block
{
    int type;
    int revealed;
    int flag;
};


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <locale.h>