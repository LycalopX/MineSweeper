
// Variáveis
#include "functions.h"

int main()
{

    // Stats do usuário
    int score, option, loop;

    printf("\n \033[0;36m‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\x1b[0m\n"
           "   \033[1;30m___                                     _                 _       \n"
           "  / __\\__ _ _ __ ___  _ __   ___     /\\/\\ (_)_ __   __ _  __| | ___  \n"
           " / /  / _` | '_ ` _ \\| '_ \\ / _ \\   /    \\| | '_ \\ / _` |/ _` |/ _ \\ \n"
           "/ /__| (_| | | | | | | |_) | (_) | / /\\/\\ \\ | | | | (_| | (_| | (_) |\n"
           "\\____/\\__,_|_| |_| |_| .__/ \\___/  \\/    \\/_|_| |_|\\__,_|\\__,_|\\___/ \n"
           "                     |_|\033[1;30m                                             \n"
           "\n \033[0;36m_____________________________________________________________________\x1b[0m \n\nNome de usuário (sem espaços): ");

    scanf("%s", username);

    printf("\n\nGostaria de: \n\033[0;36m---------------------------------------------\x1b[0m\n1. \033[0;32mJogar \x1b[0m\n2. \033[0;34mConsultar placar de jogadores \x1b[0m\n3. \033[0;31mSair \x1b[0m \n\033[0;36m---------------------------------------------\n\n\x1b[0mOpção: ");
    scanf("%d", &option);

    // Tela de escolher se vai jogar, se vai olhar a leaderboard, etc.
    SelectionScreen(option);

    // Aqui nós temos que ter certeza de que o arquivo existe, e o jogador que acabou de começar o jogo
    // Isso é necessário para a alteração de seus dados, caso ele vença ou perca afrente.
    FileMaker();

    // Definindo a matriz
    Matrix = malloc(uppermatrix * sizeof(struct block *));

    AllocateMatrix();

    // Gerador de seed
    srand(time(0));

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

                printOut();

                printf("\nPosição a revelar: ");
                scanf("%s", string);

                continue;
            }
            if (StartsWith(string, "unflag"))
            {
                Matrix[i][j].flag = 0;

                printOut();

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

                GeradorDeCampoDeMinas(c1, c2, i, j);
            }

            // Checando onde ele pisou
            if (Matrix[i][j].type == 9)
            {
                gmover = 1;
                continue;
            }
            else
            {
                read(i, j);
            }
        }

        // Printing out the Matrix
        printOut();

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

    // Execution time pt. 2
    gettimeofday(&tv2, NULL);

    int day = (int)tv2.tv_sec;

    int time = (int)(tv2.tv_usec - tv1.tv_usec) / 1000;

    int hours = findHours(time),
        minutes = findMinutes(time),
        seconds = findSeconds(time);


    // Se a pessoa perdeu, adicionar isso ao seu placar...
    if (gmover == 1)
    {
        updateUser(0, 0, 0, 0, 1);
        printf("\n\n\n\n\nBOOOOOOMMMMMM \nGame Over!!! \n\n\n\n\n");
        return 0;
    }

    updateUser(time, 10, day, 1, 0);

    printf("\n\nParabéns %s! \nTodas as Bombas foram desarmadas!"
           "\n\nStats da partida: \nTempo: %.2i:%.2i:%.2i\nPontos totais: %i\n\n",
           username, hours, minutes, seconds, pontos);

    return 0;
}