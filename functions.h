// Importando o arquivo de constantes
#include "constants.h"

// Checa o começo do string
int StartsWith(const char *a, const char *b)
{
    if (strncmp(a, b, strlen(b)) == 0)
    {
        return 1;
    }
    return 0;
}

// Retorna valores aleatórios no intervalo fornecido
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

// Seleção
void selection()
{

    int loop = 1;

    // Escolher modo de jogo
    do
    {
        printf("\n\nSeja bem-vindo a campo minado!\n"
               "\nEscolha modo de jogo: \n---------------------------------------------\n1. Fácil \n2. Intermediário \n3. Especialista (20 minutos ou mais de jogo)\n4. Ultranightmare (impossível)\n---------------------------------------------\n\nModo: ");
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

// Imprimir a tabela atual
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

// Ler para cada movimento se outras irão abrir junto
void read(int i, int j)
{

    int sum = 0;

    int conditionleft = (j - 1) >= 0;
    int conditionright = j + 1 < uppermatrix;
    int conditionup = (i - 1) >= 0;
    int conditiondown = i + 1 < uppermatrix;

    // Se já tiver sido revelado, parar imediatamente
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

    // Simplesmente revela o objeto
    else
    {
        Matrix[i][j].revealed = 1;
        counter++;
    }

    // Se o bloco a esquerda existir
    if (conditionleft)
    {
        struct block left = Matrix[i][j - 1];

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

// Conformar os pontos atribuídos a cada célula
void setUp(int i, int j)
{
    int conditionup = (i - 1) >= 0;
    int conditiondown = i + 1 < uppermatrix;
    int conditionright = j + 1 < uppermatrix;
    int conditionleft = (j - 1) >= 0;

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

// Mapeador de células da matriz
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

// Definir tempo do jogador
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

int findDays(int time) {
    int days = (time / (60 * 60 * 24));
    return days;
}

int findMonths(int time) {
    int months = (time / (60 * 60 * 24 * 30));
    return months;
}

int findYears(int time) {
    int years = (time / (60 * 60 * 24 * 30 * 12));
    return years;
}

// ESTRUTURA: {username}: [time, {score, /date, =gwon -glost
// Cria usuário do jogo
void createUser(char name[], FILE *file)
{
    // Extrair todos os jogadores
    char linha[40];

    // LER - Linha por linha
    for (int i = 1; i > 0; i++)
    {
        if (StartsWith(linha, name))
        {
            return;
        }

        if (fgets(linha, 1000, file) == NULL)
        {
            fputs("\n", file);
            fputs(name, file);
            fputs(" 0 0 0 0 0", file);

            fclose(file);
            return;
        }
    }
}

// Procura usuário do jogo
void findUser(char name[], FILE *file, char info[40])
{
    if (file == NULL)
    {
        strcpy(info, "NULL");
        return;
    }

    // Extrair todos os jogadores
    char linha[40];

    // LER - Linha por linha
    for (int i = 1; i > 0; i++)
    {
        if (StartsWith(linha, name))
        {
            strcpy(info, linha);
            return;
        }

        if (fgets(linha, 1000, file) == NULL)
        {
            strcpy(info, "NULL");
            return;
        }
    }
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

void printLeaderboard(FILE *file)
{

    printf("\n\n--------------------------\n");

    // Extrair todos os jogadores
    char linha[40];

    // Pular primeira linha
    fgets(linha, 40, file);

    // LER - Linha por linha
    for (int i = 1; fgets(linha, 40, file) != NULL; i++)
    {
        findStats(linha);

        if (!segundos) {
            continue;
        }

        printf("\n    %s: \nTempo: %is Pontuação: %i\nDia: %i\nJogos ganhos: %i\nJogos perdidos: %i \n\n",
               username, segundos, pontos, dia, jganhos, jperdidos);
    }

    printf("--------------------------");
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
    ;

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
}