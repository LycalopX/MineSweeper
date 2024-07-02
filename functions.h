// Importando o arquivo de constantes
#include "constants.h"

// Checa se o começo do string a contém o string b. Bom para comparar as linhas de
// dados dos jogadores, que começa com o seu nome

// Exemplo: LycalopX 0 0 0 0 0
int StartsWith(const char *a, const char *b)
{
    if (strncmp(a, b, strlen(b)) == 0)
    {
        return 1;
    }
    return 0;
}

// Retorna valores aleatórios no intervalo fornecido

// Usado para criar as bombas no mapa do jogo
int printRandoms(int lower, int upper, int count)
{

    int i;
    for (i = 0; i < count; i++)
    {
        int num = (rand() %
                   (upper - lower + 1)) +
                  lower;
        return num;
    }
    return 0;
}

// Interface de seleção do modo de jogo

// Altera algumas variáveis que indicam a dificuldade do jogo para o arquivo principal
// criar o tabuleiro (i.e. quantidade de bombas, tamanho da matriz, etc...)
void selection()
{

    int loop = 1;

    // Escolher modo de jogo
    do
    {
        printf("\n\nSeja bem-vindo a campo minado!\n"
               "\nEscolha modo de jogo: \n\033[0;36m---------------------------------------------\x1b[0m\n1. \033[0;32mFácil 💣 \n\x1b[0m2. \033[0;34mIntermediário 🪖 \n\x1b[0m3. \033[0;31mEspecialista 🗡️ (20 minutos ou mais de jogo)\n\x1b[0m4. \033[0;30mUltranightmare 🎖️ (impossível)\n\033[0;36m---------------------------------------------\x1b[0m\n\nModo: ");
        scanf("%i", &x);

        loop = 1;

        switch (x)
        {
        case 1:
            uppermatrix = 9;
            bombcount = 10;
            strcpy(fileName, "stats1.txt");
            break;

        case 2:
            uppermatrix = 16;
            bombcount = 40;
            strcpy(fileName, "stats2.txt");
            break;

        case 3:
            uppermatrix = 30;
            bombcount = 99;
            strcpy(fileName, "stats3.txt");
            break;

        case 4:
            uppermatrix = 81;
            bombcount = 729;
            break;

        default:
            printf("\nValor invalido!\n");
            loop = 0;
        }
    } while (loop == 0);
}

// Imprimir a matriz atual do tabuleiro (útil para encontrar bugs de programação)

// Usado toda a vez que o usuário faz um movimento
void printOut()
{

    // Números
    printf("\n ");
    for (int x = 0; x < uppermatrix; x++)
    {
        if (x > 9)
        {
            printf("%3i  ", x);
            continue;
        }
        printf("%3i  ", x);
    }

    printf("\n ");

    // Player Matrix
    for (int i = 0; i < uppermatrix; i++)
    {

        for (int p = 0; p < uppermatrix; p++)
        {
            printf("|‾‾‾|");
        }
        printf("\n%c", alphabet[i]);

        for (int j = 0; j < uppermatrix; j++)
        {
            int type = Matrix[i][j].type;
            int revealed = Matrix[i][j].revealed;
            int flag = Matrix[i][j].flag;

            if (flag)
            {
                printf("| \033[1m\033[31m⚑ \x1b[0m|");
                continue;
            }

            if (revealed == 0)
            {
                printf("| ▪︎ |");
                continue;
            }

            if (type != 0)
            {
                printf("| \x1b[%im%i \x1b[0m|", type + 30, type);
            }
            else
            {
                printf("|   |");
            }
        }
        printf("\n ");
        for (int p = 0; p < uppermatrix; p++)
        {
            printf("|___|");
        }
        printf("\n ");
    }
}

// Ler para cada movimento, se as casas ao lado também serão reveladas...

// Importante, além de que depende do tabuleiro já ter sido criado para funcionar.
void read(int i, int j)
{

    // Se existe uma coordenada das matriz em uma das direções
    int conditionleft = (j - 1) >= 0;
    int conditionright = j + 1 < uppermatrix;
    int conditionup = (i - 1) >= 0;
    int conditiondown = i + 1 < uppermatrix;

    // Se já tiver sido revelado esse bloco, parar imediatamente
    if (Matrix[i][j].revealed == 1)
    {
        return;
    }

    // Se objeto for entre 1 e 8 pontos, revelar esse, e parar imediatamente
    else if (Matrix[i][j].type != 0 && Matrix[i][j].type != 9)
    {
        Matrix[i][j].revealed = 1;
        counter++;

        return;
    }

    // Revela o objeto, para que as funções decorrentes dessa não repitam a mesma casa, e o jogo
    // inteiro se encontre me um loop infinito...

    else
    {
        Matrix[i][j].revealed = 1;
        counter++;
    }

    // Essencialmente, a checagem de casas reveladas surgiu da necessidade de garantir que
    // o AI não precisasse revelar a mesma casa mais de uma vez, além de evitar loops

    // Por isso, toda a vez que o bloco é checado, ele tem sua propriedade de revealed
    // modificada para 1

    // Se o bloco a esquerda existir
    if (conditionleft)
    {
        struct block left = Matrix[i][j - 1];

        // Se o bloco à esquerda e para cima existir
        if (conditionup)
        {
            struct block upleft = Matrix[i - 1][j - 1];

            if (upleft.revealed == 0)
            {
                if (upleft.type == 0)
                {
                    read(i - 1, (j - 1));
                }
                else
                {
                    Matrix[i - 1][j - 1].revealed = 1;
                    counter++;
                }
            }
        }

        // Se o bloco à esquerda e para cima baixo
        if (conditiondown)
        {

            struct block downleft = Matrix[i + 1][j - 1];
            if (downleft.revealed == 0)
            {
                if (downleft.type == 0)
                {
                    read(i + 1, (j - 1));
                }
                else
                {
                    Matrix[i + 1][j - 1].revealed = 1;
                    counter++;
                }
            }
        }

        // Se o bloco à esquerda não tiver sido revelado
        if (left.revealed == 0)
        {
            if (left.type == 0)
            {
                read(i, (j - 1));
            }
            else
            {
                Matrix[i][j - 1].revealed = 1;
                counter++;
            }
        }
    }

    // Se o bloco a direita existir
    if (conditionright)
    {
        struct block right = Matrix[i][j + 1];

        if (conditionup)
        {
            struct block upright = Matrix[i - 1][j + 1];

            if (upright.revealed == 0)
            {
                if (upright.type == 0)
                {
                    read(i - 1, (j + 1));
                }
                else
                {
                    Matrix[i - 1][j + 1].revealed = 1;
                    counter++;
                }
            }
        }

        if (conditiondown)
        {
            struct block downright = Matrix[i + 1][j + 1];

            if (downright.revealed == 0)
            {
                if (downright.type == 0)
                {
                    read(i + 1, (j + 1));
                }
                else
                {
                    Matrix[i + 1][j + 1].revealed = 1;
                    counter++;
                }
            }
        }

        if (right.revealed == 0)
        {
            if (right.type == 0)
            {
                read(i, j + 1);
            }
            else
            {
                Matrix[i][j + 1].revealed = 1;
                counter++;
            }
        }
    }

    // Se o bloco para cima existir
    if (conditionup)
    {
        struct block up = Matrix[i - 1][j];

        if (up.revealed == 0)
        {
            if (up.type == 0)
            {
                read(i - 1, j);
            }
            else
            {
                Matrix[i - 1][j].revealed = 1;
                counter++;
            }
        }
    }

    // Se o bloco para baixo existir
    if (conditiondown)
    {
        struct block down = Matrix[i + 1][j];

        if (down.revealed == 0)
        {
            if (down.type == 0)
            {
                read(i + 1, j);
            }
            else
            {
                Matrix[i + 1][j].revealed = 1;
                counter++;
            }
        }
    }

    return;
};

// Dar uma função à cada bloco, e já confirmar a soma de bombas em nos 8 blocos à sua volta
void setUp(int i, int j)
{
    // Condições para blocos existirem
    int conditionup = (i - 1) >= 0;
    int conditiondown = i + 1 < uppermatrix;
    int conditionright = j + 1 < uppermatrix;
    int conditionleft = (j - 1) >= 0;

    // Soma de bombas à sua volta
    int sum = 0;

    if (conditionright)
    {
        struct block right = Matrix[i][j + 1];

        if (right.type == 9)
        {
            sum++;
        }

        if (conditionup)
        {
            struct block upright = Matrix[i - 1][j + 1];
            if (upright.type == 9)
            {
                sum++;
            }
        }

        if (conditiondown)
        {
            struct block downright = Matrix[i + 1][j + 1];
            if (downright.type == 9)
            {
                sum++;
            }
        }
    }

    if (conditionleft)
    {
        struct block left = Matrix[i][j - 1];
        if (left.type == 9)
        {
            sum++;
        }

        if (conditionup)
        {
            struct block upleft = Matrix[i - 1][j - 1];
            if (upleft.type == 9)
            {
                sum++;
            }
        }

        if (conditiondown)
        {
            struct block downleft = Matrix[i + 1][j - 1];
            if (downleft.type == 9)
            {
                sum++;
            }
        }
    }

    if (conditionup)
    {
        struct block up = Matrix[i - 1][j];
        if (up.type == 9)
        {
            sum++;
        }
    }

    if (conditiondown)
    {
        struct block down = Matrix[i + 1][j];
        if (down.type == 9)
        {
            sum++;
        }
    }

    Matrix[i][j].type = sum;

    return;
};

// Gera todas as bombas no campo, tendo certeza de não colocá-las em um raio de um bloco do jogador
// (nos oito à sua volta)
void GeradorDeCampoDeMinas(int c1, int c2, int i, int j)
{

    // Mapeando bombas
    for (int n = 0; n < bombcount;)
    {

        c1 = printRandoms(lowermatrix, uppermatrix - 1, bombcount);
        c2 = printRandoms(lowermatrix, uppermatrix - 1, bombcount);

        // Tendo certeza de que não estamos colocando uma bomba duplicata, assim como não criando uma bomba
        // no lugar onde já foi revelado (i,j)
        if (Matrix[c1][c2].type == 9 || (abs(i - c1) == 1 && abs(j - c2) == 1) || (abs(i - c1) == 1 && abs(j - c2) == 0) || (abs(i - c1) == 0 && abs(j - c2) == 1) || (c1 == i && c2 == j))
        {
            continue;
        }
        else
        {
            Matrix[c1][c2].type = 9;
        }

        n++;
    }

    // Preparando os blocos não bomba
    for (int i = 0; i < uppermatrix; i++)
    {
        for (int j = 0; j < uppermatrix; j++)
        {
            if (Matrix[i][j].type == 9)
            {
                continue;
            }

            setUp(i, j);
        }
    }
}

// Quando informado tempo em milisegundos, ele converte para o formato desejado
int findSeconds(int time)
{
    int seconds = (time) % 60;
    return seconds;
}

int findMinutes(int time)
{
    int minutes = (time / (60)) % 3600;
    return minutes;
}

int findHours(int time)
{
    int hours = (time / (60 * 60));
    return hours;
}

int findDays(int time)
{
    int days = (time / (60 * 60 * 24) - 8) % (24);
    return days;
}

int findMonths(int time)
{
    int months = (time / (60 * 60 * 24 * 30) + 4) % (12);
    return months;
}

int findYears(int time)
{
    int years = (time / (60 * 60 * 24 * 30 * 12));
    return years;
}

// ESTRUTURA USADA: || username time score date gamesWon gamesLost ||

// Cria usuário do jogo no arquivo de estatísticas escolhido
void createUser(FILE *file)
{
    // Extrair todos os jogadores
    char linha[40];

    // LER - Linha por linha
    for (int i = 1; i > 0; i++)
    {
        if (StartsWith(linha, username))
        {
            return;
        }

        if (fgets(linha, 1000, file) == NULL)
        {
            fputs("\n", file);
            fputs(username, file);
            fputs(" 0 0 0 0 0", file);

            fclose(file);
            return;
        }
    }
}

// Procura usuário do jogo
int findUser(FILE *file)
{
    if (file == NULL)
    {
        return 0;
    }

    // Extrair todos os jogadores
    char linha[40];

    // LER - Linha por linha
    for (int i = 1; i > 0; i++)
    {
        if (StartsWith(linha, username))
        {
            return 1;
        }

        if (fgets(linha, 1000, file) == NULL)
        {
            return 0;
        }
    }

    return 0;
}

void findStats(char info[40])
{

    // "LycalopX 0 0 0 0 0"
    char temp_filename[1024];

    // LER - Valores
    strcpy(temp_filename, "temp_____");
    strcat(temp_filename, fileName);

    FILE *file = fopen(temp_filename, "w");

    fprintf(file, "%s", info);
    fclose(file);

    // Ler saporra
    FILE *readfile = fopen(temp_filename, "r");

    fscanf(readfile, "%s %i %i %i %i %i", username, &segundos, &pontos, &dia, &jganhos, &jperdidos);
}

// Liberar espaço da matriz
void freeMatrix(char **Matrix, int height)
{

    for (int i = 0; i < height; i++)
    {
        Matrix[i] = NULL;
    }
    Matrix = NULL;

    return;
}

int findBiggestScore(char **Matrix, int height)
{
    int num = 0;
    int index = 0;

    for (int i = 0; i < height; i++)
    {
        if (strlen(Matrix[i]) < 5)
        {
            continue;
        }

        // Quando o string está vazio, ele muda o valor de segundos para 0
        findStats(Matrix[i]);

        if (pontos > num)
        {
            index = i;
            num = pontos;
        }
    }

    return index;
}

int findSmallestTime(char **Matrix, int height)
{
    int num = 0;
    int index = 0;

    for (int i = 0; i < height; i++)
    {
        if (strlen(Matrix[i]) < 5)
        {
            continue;
        }

        findStats(Matrix[i]);

        if ((segundos < num || num == 0) && segundos != 0)
        {
            index = i;
            num = segundos;
        }
    }

    return index;
}

void organizeByPoints(int type)
{

    int i = 0, p = 0, index = 0;

    // Checa se o usuário é o mesmo da última iteração
    char previousIndex[20];

    // Arquivo
    FILE *file = fopen(fileName, "r");

    // Extrair todos os jogadores
    char linha[40];

    char **strings = NULL;

    if (file == NULL)
    {
        printf("\n Não foi possível organizar a leaderboard!! :o");
    }

    strings = malloc(sizeof(char *));

    if (strings == NULL)
    {
        printf("Memory allocation failed\n");
    }

    // Essa função serve o propósito de criar uma nova matriz com todos os dados organizados
    // de todos os primeiros 10 usuários, dependendo da categoria usada

    // Alocação dinâmica é necessária!
    for (i = 0; fgets(linha, sizeof(linha), file) != NULL; i++)
    {
        p = i + 1;

        // Alocar memória para cada string que usamos
        strings[i] = (char *)malloc((41) * sizeof(char));

        // Para criar a matriz...
        strcpy(strings[i], linha);
    }

    // Não precisamos mais do arquivo aberto
    fclose(file);

    printf("\n\n--------------------------\n");

    // Agora vamos comparar todos
    for (int j = 0; j < (p - 1); j++)
    {
        if (type)
        {
            // Vamos achar o maior, e colocá-lo na posição...
            index = findBiggestScore(strings, p);

            findStats(strings[index]);

            // Caso seja a mesma pessoa, quer dizer que o resto tem pontuação zero...
            if (!strcmp(username, previousIndex))
            {
                break;
            }
            else
            {
                strcpy(previousIndex, username);
            }

            if (!pontos)
            {
                // Remover da lista que precisa ser checada
                strcpy(strings[index], "a");
                j--;
                continue;
            }

            printf("\n    %.2d. %s \nTempo: %is Pontuação: %i\nDia: %.2i/%.2i/%i\nJogos ganhos: %i\nJogos perdidos: %i \n\n",
                   j + 1, username, segundos, pontos, findDays(dia), findMonths(dia), findYears(dia) + 1969, jganhos, jperdidos);

            // Remover da lista que precisa ser checada
            strcpy(strings[index], "a");
        }
        else
        {
            // Vamos achar o menor tempo, e colocá-lo na posição...
            index = findSmallestTime(strings, p);

            // Achando os dados
            findStats(strings[index]);

            // Caso seja a mesma pessoa, quer dizer que o resto tem pontuação zero...
            if (!strcmp(username, previousIndex))
            {
                break;
            }
            else
            {
                strcpy(previousIndex, username);
            }

            if (!segundos)
            {
                // Remover da lista que precisa ser checada
                strcpy(strings[index], "a");
                j--;
                continue;
            }

            printf("\n    %.2d. %s \nTempo: %is Pontuação: %i\nDia: %.2i/%.2i/%i\nJogos ganhos: %i\nJogos perdidos: %i \n\n",
                   j + 1, username, segundos, pontos, findDays(dia), findMonths(dia), findYears(dia) + 1969, jganhos, jperdidos);

            // Remover da lista que precisa ser checada
            strcpy(strings[index], "a");
        }
    }

    printf("--------------------------");

    freeMatrix(strings, p);
}

void updateUser(int newTime, int score, int newDay, int ganhos, int perdas)
{

    int p, i;

    // Arquivo
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("\nNão foi possível atualizar os seus novos pontos!! :o");
        return;
    }

    // Extrair todos os jogadores
    char linha[40];

    char **strings = NULL;

    strings = malloc(sizeof(char *));

    if (strings == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    // Essa função serve o propósito de criar um novo arquivo que contém as novas
    // informações, sem alterar as outras, e isso é feito transportando todos os
    // dados para uma array, e os sobrescrevendo no arquivo

    // Alocação dinâmica é necessária!
    for (i = 0; fgets(linha, sizeof(linha), file) != NULL; i++)
    {
        // variáveis
        p = i + 1;

        // Realocar para caber a nova linha do arquivo
        strings = realloc(strings, p * (sizeof(char *)));

        // Alocar memória para cada string que usamos
        strings[i] = (char *)malloc((41) * sizeof(char));

        // Agora precisamos escrever na "nova linha" os novos dados de jogador!
        if (StartsWith(linha, username))
        {
            findStats(linha);

            if (segundos > newTime || segundos == 0)
            {
                segundos = newTime;
                dia = newDay;
            }
            pontos = pontos + score;
            jganhos = jganhos + ganhos;
            jperdidos = jperdidos + perdas;

            char charNumber[20];

            // precisamos escrever todos os dados novos!
            // Lembrando que elas são variáveis globais
            strcat(strings[i], username);
            strcat(strings[i], " ");

            // Usaremos o mesmo string (charNumber) para transformar de int para char...

            sprintf(charNumber, "%d", segundos);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", pontos);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", dia);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", jganhos);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", jperdidos);

            strcat(strings[i], charNumber);
            strcat(strings[i], "\n");

            continue;
        };

        // Se os dados não forem alterados, só o incluir o string nessa casa i.
        strcpy(strings[i], linha);
    }

    fclose(file);

    // Arquivo
    FILE *writefile = fopen(fileName, "w");

    for (i = 0; i < p; i++)
    {
        fputs(strings[i], writefile);
    };

    fclose(writefile);

    freeMatrix(strings, p);
}

void SelectionScreen(int option)
{
    int loop3, loop2 = 0;

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

                printf("\n\nModo de placar: \n---------------------------------------------\n1. \033[1;30mTop 10 Tempos ⏳\x1b[0m \n2. \033[0;30mTop 10 Pontuações 🏅 \x1b[0m\n---------------------------------------------\n\nOpção: ");
                scanf("%d", &option);

                // Arquivo
                FILE *file = fopen(fileName, "r");

                // Ninguém jogou ainda...
                if (!file)
                {
                    printf("\nNão há pontuações registradas nesse modo de jogo.");
                }
                else
                {
                    organizeByPoints(option - 1);
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
                    return;
                }
            }

            break;
        case 3:
            printf("\n\nObrigado por jogar conosco!\n\n");
            return;

        default:
            printf("\nValor inválido! \n\n");
            loop3 = 0;
            printf("\n\nGostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nOpção: ");
            scanf("%d", &option);
            break;
        }
    } while (loop3 == 0);
}

void FileMaker()
{
    // Verificador da existência de usuário
    int info;

    // Arquivo
    FILE *file = fopen(fileName, "r");

    // Caso findUser seja 1, o jogador existe, se for 0, ele tem de ser criado
    info = findUser(file);

    // Procurando o usuário
    if (!info)
    {
        // Append o arquivo, para adicionar o nome de usuário novo
        FILE *fp = fopen(fileName, "a");

        // Criamos o usuário
        createUser(fp);

        // Arquivo atualizado
        file = fopen(fileName, "r");

        // Abrindo o usuário
        info = findUser(file);
    }
}

void AllocateMatrix()
{

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
}

// Passamos como ponteiro o índice de gameover do jogo...

// Ele é importante, pois informa se, depois de acabar a função, isso ocorreu
// devido ao jogador ganhar ou perder o jogo, sendo gmover = 1, se ele perdeu

// Assim, foi definida a função play para inicializar todos os protocolos e as
// checagens que formam o jogo, depois do usuário fornecer todas as
// informações necessárias
void play(int *pointer)
{

    // Definindo tudo que precisaremos para o início do jogo
    char string[9] = "";
    int gmover = *pointer;

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
}

void ContinuarJogandoScreen(int *loop)
{
    int option = 0;

    printf("\n\nGostaria de continuar jogando ou sair? \n1. Continuar jogando \n2. Sair \n\nOpção: ");

    scanf("%d", &option);

    while (option != 1 && option != 2)
    {
        switch (option)
        {
        case 1:
            // Nothing happens :/
            break;
        case 2:
            printf("\n\nObrigado por jogar!");
            *loop = 1;
            break;
        default:
            printf("Valor inválido bro");
            break;
        }
    }
}