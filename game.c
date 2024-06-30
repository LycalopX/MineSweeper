
// Variáveis
#include "functions.h"

int main()
{
    // Nome de usuário
    char info[20];

    // Stats do usuário
    int score, place, option, loop, loop2 = 0, loop3 = 0;

    printf("\n ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n"
           "   ___                                     _                 _       \n"
           "  / __\\__ _ _ __ ___  _ __   ___     /\\/\\ (_)_ __   __ _  __| | ___  \n"
           " / /  / _` | '_ ` _ \\| '_ \\ / _ \\   /    \\| | '_ \\ / _` |/ _` |/ _ \\ \n"
           "/ /__| (_| | | | | | | |_) | (_) | / /\\/\\ \\ | | | | (_| | (_| | (_) |\n"
           "\\____/\\__,_|_| |_| |_| .__/ \\___/  \\/    \\/_|_| |_|\\__,_|\\__,_|\\___/ \n"
           "                     |_|                                              \n"
           "\n ________________________________________________________________________ \n\nNome de usuário (sem espaços): ");

    scanf("%s", username);

    printf("\n\nGostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nOpção: ");
    scanf("%d", &option);

    // Repetir até valor coerente...
    do
    {
        loop3 = 1;

        switch (option)
        {
        case 1:
            selection();
            break;

        case 2:

            while (loop2 == 0)
            {
                selection();

                // Arquivo
                FILE *file = fopen(fileName, "r");

                // Ninguém jogou ainda...
                if (!file)
                {
                    printf("\nNão há pontuações registradas nesse modo de jogo.");
                }
                else
                {
                    printLeaderboard(file);
                }

                printf("\n\nE agora? Gostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nOpção: ");
                scanf("%d", &option);

                switch (option)
                {
                case 1:
                    selection();
                    loop2 = 1;
                case 2:
                    break;
                case 3:
                    printf("\n\nObrigado por jogar conosco!\n\n");
                    return 0;
                }
            }

            break;
        case 3:
            printf("\n\nObrigado por jogar conosco!\n\n");
            return 0;

        default:
            printf("\nValor inválido! \n\n");
            loop3 = 0;
            printf("\n\nGostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nOpção: ");
            scanf("%d", &option);
            break;
        }
    } while (loop3 == 0);

    // Arquivo
    FILE *file = fopen(fileName, "r");

    // Abrindo o usuário
    findUser(username, file, info);

    // Procurando o usuário
    if (!strcmp("NULL", info))
    {
        // Criamos o arquivo
        FILE *fp = fopen(fileName, "a");

        // Criamos o usuário
        createUser(username, fp);

        // Arquivo atualizado
        file = fopen(fileName, "r");

        // Abrindo o usuário
        findUser(username, file, info);
    }

    // Definindo a matriz
    Matrix = malloc(uppermatrix * sizeof(struct block *));

    // Alocando as linhas...
    for (int i = 0; i < uppermatrix; i++)
    {
        Matrix[i] = malloc(uppermatrix * sizeof(struct block));

        for (int j = 0; j < uppermatrix; j++)
        {
            Matrix[i][j].revealed = 0;
            Matrix[i][j].flag = 0;
            Matrix[i][j].type = 0;
        }
    }

    // Gerador de seed
    srand(time(0));


    // Definindo tudo que precisaremos para o início do jogo
    int gmover = 0;
    char string[9] = "";

    // Execution time pt. 1
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    updateUser(username, file);

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

                GeradorDeCampoDeMinas(c1, c2, Matrix, i, j);
            }

            // Checando onde ele pisou
            if (Matrix[i][j].type == 9)
            {
                gmover = 1;
                continue;
            }
            else
            {
                read(Matrix, i, j);
            }
        }

        // Printing out the Matrix
        printOut(Matrix);

        if (counter >= ((uppermatrix * uppermatrix) - bombcount))
        {
            break;
        }
        else if (!counter)
        {
            printf("\nExemplo: A0");
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
    int time = (double)(tv2.tv_usec - tv1.tv_usec) / 1000000,

        hours = findHours(time),
        minutes = findMinutes(time),
        seconds = findSeconds(time);

    printf("\n\nParabéns %s! \nTodas as Bombas foram desarmadas!"
           "\n\nStats da partida: \nTempo: %.2i:%.2i:%.2i\nPosição atual no placar: %i° lugar\nPontos totais: %i\n\n",
           username, hours, minutes, seconds, place, score);

    // Escrever stats do jogo
}