// Importando o arquivo de constantes
#include "constants.h"

/*
Checa se o começo do string a contém o string b. Bom para comparar as linhas de
dados dos jogadores, que começa com o seu nome

Exemplo: LycalopX 0 0 0 0 0
*/
int StartsWith(const char *a, const char *b)
{
    if (strncmp(a, b, strlen(b)) == 0)
    {
        return 1;
    }
    return 0;
}

/*
Retorna valores aleatórios no intervalo fornecido

Usado para criar as bombas no mapa do jogo
*/
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

/*
Interface de seleção do modo de jogo

Altera algumas variáveis que indicam a dificuldade do jogo para o arquivo principal
criar o tabuleiro (i.e. quantidade de bombas, tamanho da matriz, etc...)
*/
void selection(int *pointer1, int *pointer2, char fileName[11])
{
    // Retoma os ponteiros, para armazenar o tamanho da matriz
    // e a quantidade de bombas selecionado pelo usuário

    int option;

    // Assegurar que uma dificuldade seja escolhida
    int loop = 1;

    // Escolher modo de jogo
    do
    {
        // Selecionar modo de jogo
        printf("\n\nSeja bem-vindo a campo minado!\n"
               "\nEscolha modo de jogo: \n\033[0;36m---------------------------------------------\x1b[0m\n1. \033[0;32mF%ccil \n\x1b[0m2. \033[0;34mIntermedi%crio \n\x1b[0m3. \033[0;31mEspecialista (20 minutos ou mais de jogo)\n\x1b[0m4. \033[0;30mUltranightmare (imposs%cvel)\n\033[0;36m---------------------------------------------\x1b[0m\n\nModo: ",
               225, 225, 237);
        scanf("%i", &option);

        loop = 1;

        // Opções escolhidas pelo usuário
        switch (option)
        {
        case 1:
            *pointer1 = 9;
            *pointer2 = 10;
            strcpy(fileName, "stats1.txt");
            break;

        case 2:
            *pointer1 = 16;
            *pointer2 = 40;
            strcpy(fileName, "stats2.txt");
            break;

        case 3:
            *pointer1 = 30;
            *pointer2 = 99;
            strcpy(fileName, "stats3.txt");
            break;

        case 4:
            *pointer1 = 81;
            *pointer2 = 729;
            break;

        default:
            printf("\nValor invalido!\n");
            loop = 0;
        }
    } while (loop == 0);
}

/*
Imprimir a matriz atual do tabuleiro (útil para encontrar bugs de programação)

Usado toda a vez que o usuário faz um movimento
*/
void printOut(int uppermatrix, struct block **Matrix)
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
            printf("|%c%c%c|", 175, 175, 175);
        }
        printf("\n%c", alphabet[i]);

        for (int j = 0; j < uppermatrix; j++)
        {
            int type = Matrix[i][j].type;
            int revealed = Matrix[i][j].revealed;
            int flag = Matrix[i][j].flag;

            if (flag)
            {
                printf("| \033[1m\033[31m%c \x1b[0m|", 254);
                continue;
            }

            if (revealed == 0)
            {
                printf("| \x1b[1m%c\x1b[0m |", 164);
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

/*
Ler para cada movimento, se as casas ao lado também serão reveladas...

Importante, além de que depende do tabuleiro já ter sido criado para funcionar.

Sintaxe: i, j, uppermatrix, counter, Matrix
*/
void read(int i, int j, int uppermatrix, int *pointer2, struct block **Matrix)
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
        (*pointer2)++;

        return;
    }

    // Revela o objeto, para que as funções decorrentes dessa não repitam a mesma casa, e o jogo
    // inteiro se encontre me um loop infinito...

    else
    {
        Matrix[i][j].revealed = 1;
        (*pointer2)++;
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
                    read(i - 1, (j - 1), uppermatrix, pointer2, Matrix);
                }
                else
                {
                    Matrix[i - 1][j - 1].revealed = 1;
                    (*pointer2)++;
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
                    read(i + 1, (j - 1), uppermatrix, pointer2, Matrix);
                }
                else
                {
                    Matrix[i + 1][j - 1].revealed = 1;
                    (*pointer2)++;
                }
            }
        }

        // Se o bloco à esquerda não tiver sido revelado
        if (left.revealed == 0)
        {
            if (left.type == 0)
            {
                read(i, (j - 1), uppermatrix, pointer2, Matrix);
            }
            else
            {
                Matrix[i][j - 1].revealed = 1;
                (*pointer2)++;
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
                    read(i - 1, (j + 1), uppermatrix, pointer2, Matrix);
                }
                else
                {
                    Matrix[i - 1][j + 1].revealed = 1;
                    (*pointer2)++;
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
                    read(i + 1, (j + 1), uppermatrix, pointer2, Matrix);
                }
                else
                {
                    Matrix[i + 1][j + 1].revealed = 1;
                    (*pointer2)++;
                }
            }
        }

        if (right.revealed == 0)
        {
            if (right.type == 0)
            {
                read(i, j + 1, uppermatrix, pointer2, Matrix);
            }
            else
            {
                Matrix[i][j + 1].revealed = 1;
                (*pointer2)++;
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
                read(i - 1, j, uppermatrix, pointer2, Matrix);
            }
            else
            {
                Matrix[i - 1][j].revealed = 1;
                (*pointer2)++;
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
                read(i + 1, j, uppermatrix, pointer2, Matrix);
            }
            else
            {
                Matrix[i + 1][j].revealed = 1;
                (*pointer2)++;
            }
        }
    }

    return;
};

// Dar uma função à cada bloco, e já confirmar a soma de bombas em nos 8 blocos à sua volta
// Sintaxe: i, j, uppermatrix, Matrix
void setUp(int i, int j, int *pointer1, struct block **Matrix)
{
    int uppermatrix = *pointer1;

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

/*
Gera todas as bombas no campo, tendo certeza de não colocá-las em um raio de um bloco do jogador
(nos oito à sua volta)
*/
void GeradorDeCampoDeMinas(int c1, int c2, int i, int j, int *pointer1, int *pointer2, struct block **Matrix)
{
    int uppermatrix = *pointer1;
    int bombcount = *pointer2;

    // Mapeando bombas
    for (int n = 0; n < bombcount;)
    {

        c1 = printRandoms(0, uppermatrix - 1, bombcount);
        c2 = printRandoms(0, uppermatrix - 1, bombcount);

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

            setUp(i, j, pointer1, Matrix);
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

/*
ESTRUTURA USADA: || username time score date gamesWon gamesLost ||

Cria usuário do jogo no arquivo de estatísticas escolhido
*/
void createUser(FILE *file, char username[20])
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
int findUser(FILE *file, char username[20])
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

void findStats(char info[40], char fileName[11], char username[20],
               int *segundos, int *pontos, int *dia, int *jganhos, int *jperdidos)
{
    char temp_filename[4] = "temp";

    FILE *file = fopen(temp_filename, "w");

    fprintf(file, "%s", info);
    fclose(file);

    // Ler saporra
    FILE *readfile = fopen(temp_filename, "r");

    fscanf(readfile, "%s %i %i %i %i %i", username, segundos, pontos, dia, jganhos, jperdidos);
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

int findBiggestScore(char **Matrix, int height, char fileName[11], char username[20],
                     int *segundos, int *pontos, int *dia, int *jganhos, int *jperdidos)

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
        findStats(Matrix[i], fileName, username, segundos, pontos, dia, jganhos, jperdidos);
        remove("temp");

        if (*pontos > num && *pontos)
        {
            index = i;
            num = *pontos;
        }
    }

    return index;
}

int findSmallestTime(char **Matrix, int height, char fileName[11], char username[20],
                     int *segundos, int *pontos, int *dia, int *jganhos, int *jperdidos)

{
    int num = 0;
    int index = 0;

    for (int i = 0; i < height; i++)
    {
        if (strlen(Matrix[i]) < 5)
        {
            continue;
        }

        findStats(Matrix[i], fileName, username, segundos, pontos, dia, jganhos, jperdidos);
        remove("temp");

        if ((*segundos < num || num == 0) && *segundos != 0)
        {
            index = i;
            num = *segundos;
        }
    }

    return index;
}

void organizeByPoints(int type, char fileName[20], char username[20],
                      int *segundos, int *pontos, int *dia, int *jganhos, int *jperdidos)
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
        printf("\n N%co foi possível organizar a leaderboard!! :o", 227);
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
            index = findBiggestScore(strings, p, fileName, username, segundos, pontos, dia, jganhos, jperdidos);

            findStats(strings[index], fileName, username, segundos, pontos, dia, jganhos, jperdidos);
            remove("temp");

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

            printf("\n    %.2d. %s \nTempo: %is Pontua%c%co: %i\nDia: %.2i/%.2i/%i\nJogos ganhos: %i\nJogos perdidos: %i \n\n",
                   j + 1, username, *segundos, 231, 227, *pontos, findDays(*dia), findMonths(*dia), findYears(*dia) + 1969, *jganhos, *jperdidos);

            // Remover da lista que precisa ser checada
            strcpy(strings[index], "a");
        }
        else
        {
            // Vamos achar o menor tempo, e colocá-lo na posição...
            index = findSmallestTime(strings, p, fileName, username, segundos, pontos, dia, jganhos, jperdidos);

            // Achando os dados
            findStats(strings[index], fileName, username, segundos, pontos, dia, jganhos, jperdidos);
            remove("temp");

            // Caso seja a mesma pessoa, quer dizer que o resto tem pontuação zero...
            if (!strcmp(username, previousIndex))
            {
                break;
            }
            else
            {
                strcpy(previousIndex, username);
            }

            if (!*segundos)
            {
                // Remover da lista que precisa ser checada
                strcpy(strings[index], "a");
                j--;
                continue;
            }

            printf("\n    %.2d. %s \nTempo: %is Pontua%c%co: %i\nDia: %.2i/%.2i/%i\nJogos ganhos: %i\nJogos perdidos: %i \n\n",
                   j + 1, username, *segundos, 231, 227, *pontos, findDays(*dia), findMonths(*dia), findYears(*dia) + 1969, *jganhos, *jperdidos);

            // Remover da lista que precisa ser checada
            strcpy(strings[index], "a");
        }
    }

    printf("--------------------------");

    freeMatrix(strings, p);
}

// Muitas variáveis, pois há muita coisa a ser passada...

// Sintaxe: newTime, score, newDay, ganhos, perdas, fileName, username, segundos, pontos, dia, jganhos, jperdidos
void updateUser(
    int newTime, int score, int newDay, int ganhos, int perdas,
    char fileName[11], char username[20],
    int *pointer1, int *pointer2, int *pointer3, int *pointer4, int *pointer5)

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
            findStats(linha, fileName, username, pointer1, pointer2, pointer3, pointer4, pointer5);
            remove("temp");

            if (*pointer1 > newTime || *pointer1 == 0)
            {
                *pointer1 = newTime;
                *pointer3 = newDay;
            }
            *pointer2 = *pointer2 + score;
            *pointer4 = *pointer4 + ganhos;
            *pointer5 = *pointer5 + perdas;

            char charNumber[20];

            // precisamos escrever todos os dados novos!
            // Lembrando que elas são variáveis globais
            strcat(strings[i], username);
            strcat(strings[i], " ");

            // Usaremos o mesmo string (charNumber) para transformar de int para char...

            sprintf(charNumber, "%d", *pointer1);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", *pointer2);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", *pointer3);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", *pointer4);

            strcat(strings[i], charNumber);
            strcat(strings[i], " ");

            sprintf(charNumber, "%d", *pointer5);

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

void SelectionScreen(int option, char fileName[11], int *uppermatrix, int *bombcount,
                     char username[20], int *segundos, int *pontos, int *dia, int *jganhos, int *jperdidos)
{
    // Caso tenha sido selecionado: jogar ou ver placar, ele age com base nessas duas escolhas
    // Case 1 é o caso da pessoa ter escolhido jogar
    // Case 2 é o caso da pessoa ter escolhido placar
    // Case 3 é o caso da pessoa ter escolhido sair do jogo

    int loop3, loop2 = 0;

    // Repetir até valor coerente...
    do
    {
        loop3 = 1;

        switch (option)
        {
        case 1:
            // Leva à tela de seleção da dificuldade, para jogar
            selection(uppermatrix, bombcount, fileName);
            break;

        case 2:

            while (loop2 == 0)
            {

                // Leva à tela de seleção da dificuldade, para ver a leaderboard
                selection(uppermatrix, bombcount, fileName);

                // Imprime as opções de placar (por tempo ou pontuação)
                printf("\n\nModo de placar: \n---------------------------------------------\n1. \033[1;30mTop 10 Tempos\x1b[0m \n2. \033[0;30mTop 10 Pontua%c%ces \x1b[0m\n---------------------------------------------\n\nOp%c%co: ", 231, 245, 231, 227);
                scanf("%d", &option);

                // Arquivo em que estão armazenadas as estatísticas
                FILE *file = fopen(fileName, "r");

                // Ninguém jogou ainda...
                if (!file)
                {
                    printf("\nNão há pontuações registradas nesse modo de jogo.");
                }

                // Inicia protocolo de achar os top 10 melhores jogadores e imprimir um a um
                // suas estaísticas
                else
                {
                    organizeByPoints(option - 1, fileName, username, segundos, pontos, dia, jganhos, jperdidos);
                }

                // Depois que isso se encerrou, ele pergunta novamente

                printf("\n\nE agora? Gostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nOp%c%co: ", 231, 227);
                scanf("%d", &option);

                // Usa a mesma variável para o case

                switch (option)
                {
                case 1:
                    selection(uppermatrix, bombcount, fileName);
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

            // Sair do jogo
            printf("\n\nObrigado por jogar conosco!\n\n");
            return;

        default:
            // Mesma pergunta de novo, até que a pessoa digite 1-3
            printf("\nValor inválido! \n\n");
            loop3 = 0;
            printf("\n\nGostaria de: \n---------------------------------------------\n1. Jogar \n2. Consultar placar de jogadores \n3. Sair \n---------------------------------------------\n\nO%c%co: ", 231, 227);
            scanf("%d", &option);
            break;
        }
    } while (loop3 == 0);
}

void FileMaker(char fileName[11], char username[20])
{
    // Verificador da existência de usuário
    int info;

    // Arquivo
    FILE *file = fopen(fileName, "r");

    // Caso findUser seja 1, o jogador existe, se for 0, ele tem de ser criado
    info = findUser(file, username);

    // Procurando o usuário
    if (!info)
    {
        // Append o arquivo, para adicionar o nome de usuário novo
        FILE *fp = fopen(fileName, "a");

        // Criamos o usuário
        createUser(fp, username);

        // Arquivo atualizado
        file = fopen(fileName, "r");
    }
}

// Alocar todo o espaço e configurar as matrizes
void AllocateMatrix(int *pointer1, struct block **Matrix)
{
    int uppermatrix = *pointer1;

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

/*
Assim, foi definida a função play para inicializar todos os protocolos e as
checagens que formam o jogo, depois do usuário fornecer todas as
informações necessárias

Sintaxe: gmover, uppermatrix, counter, bombcount, Matrix
*/
void play(int *pointer, int *pointer2, int *pointer3, int *pointer4, struct block **Matrix)
{

    // Definindo tudo que precisaremos para o início do jogo
    char string[9] = "";
    int gmover = *pointer;
    int uppermatrix = *pointer2;
    int bombcount = *pointer4;

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

                printOut(uppermatrix, Matrix);

                printf("\nPosi%c%co a revelar: ", 231, 227);
                scanf("%s", string);

                continue;
            }
            if (StartsWith(string, "unflag"))
            {
                Matrix[i][j].flag = 0;

                printOut(uppermatrix, Matrix);

                printf("\nPosi%c%co a revelar: ", 231, 227);
                scanf("%s", string);
                continue;
            }

            if (i < 0 || j < 0 || i > uppermatrix || j > uppermatrix)
            {

                printf("\nValor inválido\n");

                printf("\nPosi%c%co a revelar: ", 231, 227);
                scanf("%s", string);

                continue;
            }

            if ((*pointer3) == 0)
            {
                int c1, c2;

                GeradorDeCampoDeMinas(c1, c2, i, j, pointer2, pointer4, Matrix);
            }

            // Checando onde ele pisou
            if (Matrix[i][j].type == 9)
            {
                (*pointer) = 1;
                break;
            }
            else
            {
                read(i, j, uppermatrix, pointer3, Matrix);
            }
        }

        // Printing out the Matrix
        printOut(uppermatrix, Matrix);

        if ((*pointer3) >= ((uppermatrix * uppermatrix) - bombcount))
        {
            break;
        }
        else if (!(*pointer3))
        {
            printf("\nExemplo: A0");
        }

        printf("\nPosi%c%co a revelar: ", 231, 227);
        scanf("%s", string);
    }
}

// Tela para sair do jogo ou continuar jogando
void ContinuarJogandoScreen(int *loop)
{
    int option = 0;

    printf("\n\nGostaria de continuar jogando ou sair? \n1. Continuar jogando \n2. Sair \n\nOpç%co: ", 227);

    while (option != 1 && option != 2)
    {
        scanf("%d", &option);

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