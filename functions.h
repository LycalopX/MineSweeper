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
void selection() {

    int loop = 1;

    // Escolher modo de jogo
    do
    {
        printf("\n\nSeja bem-vindo a campo minado!\n\nEscolha modo de jogo: \n---------------------------------------------\n1. Fácil \n2. Intermediário \n3. Especialista (20 minutos ou mais de jogo)\n---------------------------------------------\n\nModo: ");
        scanf("%i", &x);

        loop = 1;

        switch (x)
        {
        case 1:
            uppermatrix = 9;
            bombcount = 10;
            break;

        case 2:
            uppermatrix = 16;
            bombcount = 40;
            break;

        case 3:
            uppermatrix = 30;
            bombcount = 99;
            break;

        default:
            printf("\nValor invalido!\n");
            loop = 0;
        }
    } while (loop == 0);

}

// Imprimir a tabela atual
void printOut(struct block Matrix[uppermatrix][uppermatrix])
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

    // Player Matrix
    for (int i = 0; i < uppermatrix; i++)
    {

        printf("\n ");
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
                printf("| ■ |");
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
        printf("\n");
    }
}

// Ler para cada movimento se outras irão abrir junto
struct block read(struct block Matrix[uppermatrix][uppermatrix], int i, int j)
{

    int sum = 0;

    struct block right = Matrix[i][j + 1];
    int conditionright = j + 1 < uppermatrix;

    struct block left = Matrix[i][j - 1];
    int conditionleft = (j - 1) >= 0;

    struct block up = Matrix[i - 1][j];
    int conditionup = (i - 1) >= 0;

    struct block down = Matrix[i + 1][j];
    int conditiondown = i + 1 < uppermatrix;

    // Se já tiver sido revelado, parar imediatamente
    if (Matrix[i][j].revealed == 1)
    {
        return Matrix[i][j];
    }

    // Se objeto for entre 1 e 8 pontos, revelar esse, e parar imediatamente
    else if (Matrix[i][j].type != 0 && Matrix[i][j].type != 9)
    {
        Matrix[i][j].revealed = 1;
        counter++;
        return Matrix[i][j];
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

        if (left.revealed == 0)
        {
            if (left.type == 0)
            {
                Matrix[i][j - 1] = read(Matrix, i, (j - 1));
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
        if (right.revealed == 0)
        {
            if (right.type == 0)
            {
                Matrix[i][j + 1] = read(Matrix, i, j + 1);
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
        if (up.revealed == 0)
        {
            if (up.type == 0)
            {
                Matrix[i - 1][j] = read(Matrix, i - 1, j);
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

        if (down.revealed == 0)
        {
            if (down.type == 0)
            {
                Matrix[i + 1][j] = read(Matrix, i + 1, j);
            }
            else
            {
                Matrix[i + 1][j].revealed = 1;
                counter++;
            }
        }
    }

    return Matrix[i][j];
};

// Conformar os pontos atribuídos a cada célula
struct block setUp(struct block Matrix[uppermatrix][uppermatrix], int i, int j)
{

    int sum = 0;

    struct block right = Matrix[i][j + 1];
    int conditionright = j + 1 < uppermatrix;

    if (conditionright && right.type == 9)
    {
        sum++;
    }

    struct block left = Matrix[i][j - 1];
    int conditionleft = (j - 1) >= 0;

    if (conditionleft && left.type == 9)
    {
        sum++;
    }

    struct block up = Matrix[i - 1][j];
    int conditionup = (i - 1) >= 0;

    if (conditionup && up.type == 9)
    {
        sum++;
    }

    struct block down = Matrix[i + 1][j];
    int conditiondown = i + 1 < uppermatrix;

    if (conditiondown && down.type == 9)
    {
        sum++;
    }

    struct block upright = Matrix[i - 1][j + 1];

    if (conditionup && conditionright && upright.type == 9)
    {
        sum++;
    }

    struct block upleft = Matrix[i - 1][j - 1];

    if (conditionleft && conditionup && upleft.type == 9)
    {
        sum++;
    }

    struct block downright = Matrix[i + 1][j + 1];

    if (conditiondown && conditionright && downright.type == 9)
    {
        sum++;
    }

    struct block downleft = Matrix[i + 1][j - 1];

    if (conditiondown && conditionleft && downleft.type == 9)
    {
        sum++;
    }

    Matrix[i][j].type = sum;

    return Matrix[i][j];
};


// Mapeador de células da matriz
void GeradorDeCampoDeMinas(int c1, int c2, struct block Matrix[uppermatrix][uppermatrix], int i, int j)
{

    // Mapeando bombas
    for (int n = 0; n < bombcount;)
    {

        c1 = printRandoms(lowermatrix, uppermatrix - 1, bombcount);
        c2 = printRandoms(lowermatrix, uppermatrix - 1, bombcount);

        // Tendo certeza de que não estamos colocando uma bomba duplicata, assim como não criando uma bomba
        // no lugar onde já foi revelado (i,j)
        if (Matrix[c1][c2].type == 9 && (i == c1 || j == c2))
        {
            continue;
        }
        else
        {
            Matrix[c1][c2].type = 9;
            Matrix[c1][c2].revealed = 0;
            Matrix[c1][c2].flag = 0;
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

            Matrix[i][j] = setUp(Matrix, i, j);
        }
    }
}


// Definir tempo do jogador
int findSeconds(int time)
{
    int seconds = (time) % 60;
    printf("%i segundos\n", seconds);
    return seconds;
}

int findMinutes(int time)
{
    int minutes = (time / (60)) % 3600;
    printf("%i minutos\n", minutes);
    return minutes;
}

int findHours(int time)
{
    int hours = (time / (60 * 60));
    printf("%i horas\n", hours);
    return hours;
}
