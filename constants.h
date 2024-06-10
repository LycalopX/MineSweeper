// variáveis globais do programa que ditam a ordem que cada coordenada impõe sobre a matriz...
char alphabet[34] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcd";

// Configurações das matrizes
int x, lowermatrix = 0, uppermatrix, bombcount;

// Contagem do número de células reveladas, para levar à tela de vitória
int counter = 0;

// Estrutura de cada célula
struct block
{
    int type;
    int revealed;
    int flag;
};
