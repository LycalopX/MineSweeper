#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

// Variáveis
#include "functions.h"

int main()
{
    char username[20];
    int score, place, option, loop;

    printf("\n ‾‾‾‾‾‾‾‾‾‾‾‾\n CAMPO MINADO\n ____________ \n\nNome de usuário: ");
    scanf("%s", username);

    printf("\n\nGostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n---------------------------------------------\n\nOpção: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        selection();
        break;

    case 2:
        printf("Vai tomar no cu");
        return 0;

    default:
        printf("Valor inválido!");
        break;
    }

    // Definindo a matriz
    struct block Matrix[uppermatrix][uppermatrix];

    // Gerador de seed
    srand(time(0));

    // Colocando tudo como não revelado ainda
    for (int i = 0; i < uppermatrix; i++)
    {
        for (int j = 0; j < uppermatrix; j++)
        {
            Matrix[i][j].revealed = 0;
            Matrix[i][j].flag = 0;
        }
    }

    // Definindo tudo que precisaremos para o início do jogo
    int gmover = 0;
    char string[9] = "";

    // Execution time pt. 1
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    // p =/ 0, game over :d
    while (gmover == 0)
    {

        // Quando o usuário forneceu um input
        if (string[0])
        {

            int j = 0, fc = 0;

            // Checando se vc nao simplesmente quebra tudo kkkkkkkkkk
            int length = (int)strlen(string);

            if (StartsWith(string, "flag"))
            {
                fc = 4;
            }
            if (StartsWith(string, "unflag"))
            {
                fc = 6;
            }

            for (int i = length - 1; i > fc; i--)
            {
                j += (((int)(string[i] - '0')) * pow(10, length - 1 - i));
            }

            // Descobrindo o que ele acabou de fornecer...
            char *a = alphabet;
            char *e;

            e = strchr(a, string[fc]);
            int i = (int)(e - a);

            if (StartsWith(string, "flag"))
            {
                Matrix[i][j].flag = 1;

                printOut(Matrix);

                printf("\nPosição a revelar: ");
                scanf("%s", string);

                continue;
            }
            if (StartsWith(string, "unflag"))
            {
                Matrix[i][j].flag = 0;

                printOut(Matrix);

                printf("\nPosição a revelar: ");
                scanf("%s", string);
                continue;
            }

            if (i < 0 || j < 0 || i > uppermatrix || j > uppermatrix)
            {

                printf("\nValor inválido\n");

                printf("\nPosição a revelar: ");
                scanf("%s", string);

                continue;
            }

            if (counter == 0)
            {
                int c1, c2;

                Matrix[i][j].revealed = 1;
                counter++;
                GeradorDeCampoDeMinas(c1, c2, Matrix);
            }

            // Checando onde ele pisou
            if (Matrix[i][j].type == 9)
            {
                gmover = 1;
                continue;
            }
            else
            {
                Matrix[i][j] = read(Matrix, i, j);
            }
        }

        // Printing out the Matrix
        printOut(Matrix);

        if (counter >= ((uppermatrix * uppermatrix) - bombcount))
        {
            break;
        }

        printf("\nPosição a revelar: ");
        scanf("%s", string);
    }

    if (gmover == 1)
    {

        printf("\n\n\n\n\nBOOOOOOMMMMMM \nGame Over!!! \n\n\n\n\n");
        return 0;
    }

    // Execution time pt. 2
    gettimeofday(&tv2, NULL);
    int time = (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec), 

    hours = findHours(time), 
    minutes = findMinutes(time), 
    seconds = findSeconds(time);



    printf("\n\nParabéns %s! \nTodas as Bombas foram desarmadas!"
           "\n\nStats da partida: \nTempo: %.2i:%.2i:%.2i\nPosição atual no placar: %i° lugar\nPontos totais: %i\n\n",
           username, hours, minutes, seconds, place, score);
}