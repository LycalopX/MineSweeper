// Vari�veis
#include "functions.h"

int main()
{

    // Execution time pt. 1
    struct timeval t0, t1;
    gettimeofday(&t0, 0);

    setlocale(LC_ALL, "Portuguese_Brazil");

    // Opção escolhida pelo usuário quando promptado, e variável loop
    // que encerra o programa

    int option, loop = 0;

    // Nome do arquivo onde serão salvas as estatísticas de jogo daquela dificuldade
    // Nome do jogador que: está jogando, ou tendo seus dados analisados pelo sistema
    // em dado momento

    char fileName[11], username[20];

    // Configurações das matrizes que serão definidas conforme a dificuldade
    // de jogo escolhida pelo usuário

    int x, uppermatrix, bombcount, counter = 0;

    // Estatásticas do jogador da partida! Extremamente importante quando analisando
    // os placares de jogadores diferentes usando findStats...

    int segundos, pontos, dia, jganhos, jperdidos;

    // Tela inicial do usuário
    printf("\n \033[0;36m");
    for (int i = 0; i < 69; i++) { printf("%c", 175); }
    printf("\x1b[0m\n");

    printf("   \033[1;34m___                                     _                 _       \n"
           "  / __\\__ _ _ __ ___  _ __   ___     /\\/\\ (_)_ __   __ _  __| | ___  \n"
           " / /  / _` | '_ ` _ \\| '_ \\ / _ \\   /    \\| | '_ \\ / _` |/ _` |/ _ \\ \n"
           "/ /__| (_| | | | | | | |_) | (_) | / /\\/\\ \\ | | | | (_| | (_| | (_) |\n"
           "\\____/\\__,_|_| |_| |_| .__/ \\___/  \\/    \\/_|_| |_|\\__,_|\\__,_|\\___/ \n"
           "                     |_|\033[1;34m                                           \n"
           "\n \033[0;36m_____________________________________________________________________\x1b[0m \n\nNome de usu%crio (sem espa%cos): ", 225, 231);

    // Usuário para coleta de dados anteriormente salvos
    scanf("%s", username);

    // Loop para quando se inicia o jogo, se pessoa quer jogar novamente
    while (loop == 0)
    {
        printf("\n\nGostaria de: \n\033[0;36m---------------------------------------------\x1b[0m\n1. \033[0;32mJogar \x1b[0m\n2. \033[0;34mConsultar placar de jogadores \x1b[0m\n3. \033[0;31mSair \x1b[0m \n\033[0;36m---------------------------------------------\n\n\x1b[0mOp%c%co: ", 231, 227);
        scanf("%d", &option);

        // Tela de escolher se vai jogar, se vai olhar a leaderboard, etc.
        SelectionScreen(option, fileName, &uppermatrix, &bombcount, username, &segundos, &pontos, &dia, &jganhos, &jperdidos);

        // Aqui nós temos que ter certeza de que o arquivo existe, e o jogador que acabou de começar o jogo
        // Isso é necessário para a alteração de seus dados, caso ele vença ou perca afrente.

        FileMaker(fileName, username);

        // Definindo a matriz
        struct block **Matrix = malloc(uppermatrix * sizeof(struct block *));

        // Gerando a matriz inteira com todas as propriedades como bombas, pontos,
        // entre outras criadas toda vez que um jogo novo é iniciado.

        AllocateMatrix(&uppermatrix, Matrix);

        // Gerador de seed
        srand(time(0));

        // Índice de gameover
        int gmover = 0;

        // Inicia o jogo
        play(&gmover, &uppermatrix, &counter, &bombcount, Matrix);

        counter = 0;

        // Execution time pt. 2
        gettimeofday(&t1, NULL);

        int day = (int)(t1.tv_sec);

        int time = (int)((t1.tv_sec - t0.tv_sec));

        int hours = findHours(time),
            minutes = findMinutes(time),
            seconds = findSeconds(time);

        // Se a pessoa perdeu, adicionar isso ao seu placar...
        if (gmover == 1)
        {
            updateUser(0, 0, 0, 0, 1, fileName, username, &segundos, &pontos, &dia, &jganhos, &jperdidos);
            printf("\n\n\n\n\nBOOOOOOMMMMMM \nGame Over!!! \n\n\n\n\n");
        }
        // Se a pessoa ganhou, atualizar, mas com variáveis diferentes (porque ele ganhou)
        else
        {
            updateUser(time, 10, day, 1, 0, fileName, username, &segundos, &pontos, &dia, &jganhos, &jperdidos);

            printf("\n\nParab%cns %s! \nTodas as Bombas foram desarmadas!"
                   "\n\nStats da partida: \nTempo: %.2i:%.2i:%.2i\nPontos totais: %i\n\n",
                   233, username, hours, minutes, seconds, pontos);
        }

        // Para saber se o jogador gostaria de continuar jogando ou encerrar
        // o jogo, foi criada uma função com o prompt

        ContinuarJogandoScreen(&loop);
    }
}