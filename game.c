
// Variáveis
#include "functions.h"

int main()
{

    // Execution time pt. 1
    struct timeval t0, t1;
    gettimeofday(&t0, 0);

    // Limpar tudo
    system("clear");

    // Opção escolhida pelo usuário quando promptado, e variável loop
    // que encerra o programa
    int option, loop = 0;

    // Tela inicial do usuário
    printf("\n \033[0;36m‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\x1b[0m\n"
           "   \033[1;34m___                                     _                 _       \n"
           "  / __\\__ _ _ __ ___  _ __   ___     /\\/\\ (_)_ __   __ _  __| | ___  \n"
           " / /  / _` | '_ ` _ \\| '_ \\ / _ \\   /    \\| | '_ \\ / _` |/ _` |/ _ \\ \n"
           "/ /__| (_| | | | | | | |_) | (_) | / /\\/\\ \\ | | | | (_| | (_| | (_) |\n"
           "\\____/\\__,_|_| |_| |_| .__/ \\___/  \\/    \\/_|_| |_|\\__,_|\\__,_|\\___/ \n"
           "                     |_|\033[1;34m                                           \n"
           "\n \033[0;36m_____________________________________________________________________\x1b[0m \n\nNome de usuário (sem espaços): ");

    scanf("%s", username);

    while (loop == 0)
    {
        printf("\n\nGostaria de: \n\033[0;36m---------------------------------------------\x1b[0m\n1. \033[0;32mJogar \x1b[0m\n2. \033[0;34mConsultar placar de jogadores \x1b[0m\n3. \033[0;31mSair \x1b[0m \n\033[0;36m---------------------------------------------\n\n\x1b[0mOpção: ");
        scanf("%d", &option);

        // Tela de escolher se vai jogar, se vai olhar a leaderboard, etc.
        SelectionScreen(option);

        // Aqui nós temos que ter certeza de que o arquivo existe, e o jogador que acabou de começar o jogo
        // Isso é necessário para a alteração de seus dados, caso ele vença ou perca afrente.
        FileMaker();

        // Definindo a matriz
        Matrix = malloc(uppermatrix * sizeof(struct block *));

        // Gerando a matriz inteira com todas as propriedades como bombas, pontos,
        // entre outras criadas toda vez que um jogo novo é iniciado.
        AllocateMatrix();

        // Gerador de seed
        srand(time(0));

        // Índice de gameover
        int gmover = 0;

        // Inicia o jogo
        play(&gmover);

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
            updateUser(0, 0, 0, 0, 1);
            printf("\n\n\n\n\nBOOOOOOMMMMMM \nGame Over!!! \n\n\n\n\n");
            return 0;
        }

        updateUser(time, 10, day, 1, 0);

        printf("\n\nParabéns %s! \nTodas as Bombas foram desarmadas!"
               "\n\nStats da partida: \nTempo: %.2i:%.2i:%.2i\nPontos totais: %i\n\n",
               username, hours, minutes, seconds, pontos);
        
        // Para saber se o jogador gostaria de continuar jogando ou encerrar
        // o jogo, foi criada uma função com o prompt

        ContinuarJogandoScreen(&loop);
    }
}