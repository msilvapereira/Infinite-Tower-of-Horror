#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINHA 10
#define MAX_COLUNA 40

typedef struct
{
    int ox;
    int oy;
    int jogadorX;
    int jogadorY;
    int monstroX;
    int monstroY;
    int chaveX;
    int chaveY;
    int vitoria;
    int chaveDefinida;
    int dificuldade;
    int chaveObtida;
    int parede[5];
} tNivel;

void defineNivel(tNivel *nivel)
{
    nivel->vitoria = 0;
    nivel->dificuldade = 1;
    nivel->chaveObtida = 0;
    nivel->chaveDefinida = 0;
    nivel->ox = MAX_COLUNA - 2;
    nivel->oy = MAX_LINHA - 2;
    nivel->jogadorX = 1;
    nivel->jogadorY = 1;
    nivel->monstroX = (int)(MAX_COLUNA * 0.4);
    nivel->monstroY = (int)(MAX_LINHA * 0.8);
    nivel->chaveX = 1;
    nivel->chaveY = 1;
    nivel->parede[0] = 20;
    nivel->parede[1] = 39;
    nivel->parede[2] = 0;
    nivel->parede[3] = 9;
    nivel->parede[4] = 4;
}

<<<<<<< Updated upstream
void geraChave(tNivel *nivel)
=======
int menu()
{
    int opcao;

    system("cls");
    printf("\n[ 1 ] - Jogar");
    printf("\n[ 2 ] - Como jogar");
    printf("\n[ 3 ] - Sair\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        jogar();
        break;
    case 2:
        instrucoes();
        break;
    case 3:
        return 0;
    default:
        printf("\nOpcao invalida");
        system("PAUSE");
    }

    return 1;
}

void instrucoes()
{
    system("cls");
    printf("\nPara jogar voce deve selecionar a opcao Jogar no menu, e após isso ira comecar o jogo onde...");
    printf("\nVoce enquanto jogador deve fugir do monstro, pegar a chave e passar pela saida para alcancar o proximo nivel.");
    printf("\nSeus controles para movimentacao consistem nas telcas 8, 4, 5, 6 onde respectivamente o movimenta para cima, esquerda,  baixo e direita\n");
    system("PAUSE");
    system("cls");
}

// Funcao que ira receber o nome do jogador
void configurar()
>>>>>>> Stashed changes
{
    while (nivel->chaveX == nivel->parede[0] || nivel->chaveX == nivel->parede[1] || nivel->chaveX == nivel->parede[2] || nivel->chaveY == nivel->parede[2] || nivel->chaveY == nivel->parede[3])
    {
        nivel->chaveX = (int)(rand() % MAX_COLUNA);
        nivel->chaveY = (int)(rand() % MAX_LINHA);
    }
    nivel->chaveDefinida = 1;
}

void geraNivel(tNivel *nivel)
{
    int x, y;
    int caracteres[7] = {186, 177, 241, 207, 219, 189, 196};
    defineNivel(nivel);
    geraChave(nivel);
    for (y = 0; y < MAX_LINHA; y++)
    {
        for (x = 0; x < MAX_COLUNA; x++)
        {

            if (x == nivel->parede[0] && y != nivel->parede[2] && y != nivel->parede[3] && y != nivel->parede[4])
            {
                printf("%c", caracteres[0]);
            }
            else if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
            {
                printf("%c", caracteres[1]);
            }
            else if (x == nivel->jogadorX && y == nivel->jogadorY)
            {
                printf("%c", caracteres[2]);
            }
            else if (x == nivel->monstroX && y == nivel->monstroY)
            {
                printf("%c", caracteres[3]);
            }
            else if (x == nivel->ox && y == nivel->oy)
            {
                printf("%c", caracteres[4]);
            }
            else if (x == nivel->chaveX && y == nivel->chaveY)
            {
                printf("%c", caracteres[5]);
            }
            else
            {
                printf("%c", caracteres[6]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int controle, direcao;

    printf("Voce eh um cacador de fantasmas e descobriu um fantasma do tipo Wraith, \ne precisa fugir da torre assombrada em que se encontra... \n\n");
    system("PAUSE");
    for (;;)
    {
        tNivel *nivel;
        geraNivel(nivel);
        controle = 0;
        system("CLS");
        printf("Torre Assombrada - Furia da Wraith: %d\n\n", nivel->dificuldade);
        printf("Chave obtida: %i\n\n", nivel->chaveObtida);

        printf("Controles: 8 (cima)\t6 (direita)\t5 (baixo)\t4 (esquerda)\n\n");
        printf("Fantasma - %c \nPlayer - %c \nChave - %c \nPorta - %c \n\n", 207, 241, 189, 219);
        printf("Sua vez! Digite um controle: ");
        scanf("%i", &controle);
        setbuf(stdin, NULL);
        switch (controle)
        {

        case 8:
            nivel->jogadorY -= 1;
            if (nivel->jogadorY < 1)
            {
                nivel->jogadorY = 1;
            }
            else if (nivel->jogadorX == 20)
            {
                nivel->jogadorY = 4;
            }
            break;

        case 5:
            nivel->jogadorY += 1;
            if (nivel->jogadorY >= MAX_LINHA - 1)
            {
                nivel->jogadorY = MAX_LINHA - 2;
            }
            else if (nivel->jogadorX == 20)
            {
                nivel->jogadorY = 4;
            }
            break;

        case 4:
            nivel->jogadorX -= 1;
            if (nivel->jogadorX < 1)
            {
                nivel->jogadorX = 1;
            }
            else if (nivel->jogadorX != 4)
            {
                if (nivel->jogadorX == 20)
                {
                    nivel->jogadorX = 21;
                }
            }
            break;

        case 6:
            nivel->jogadorX += 1;
            if (nivel->jogadorX >= MAX_COLUNA - 1)
            {
                nivel->jogadorX = MAX_COLUNA - 2;
            }
            else if (nivel->jogadorY != 4)
            {
                if (nivel->jogadorX == 20)
                {
                    nivel->jogadorX = 19;
                }
            }
            break;

        default:
            printf("\nComando invalido!\n");
            system("PAUSE");
        }

        if (nivel->jogadorY == nivel->chaveY && nivel->jogadorX == nivel->chaveX)
        {
            nivel->chaveObtida = 1;
            nivel->chaveY = 0, nivel->chaveX = 0;
        }

        if (nivel->jogadorX == nivel->monstroY)
        {
            if (nivel->jogadorX > nivel->monstroX)
            {
                direcao = 3;
            }
            else if (nivel->jogadorX == nivel->monstroX)
            {
                direcao = 4;
            }
            else
            {
                direcao = 2;
            }
        }
        else if (nivel->jogadorX == nivel->monstroX)
        {
            if (nivel->jogadorY > nivel->monstroY)
            {
                direcao = 1;
            }
            else
            {
                direcao = 0;
            }
        }
        else
        {
            direcao = rand() % 4;
        }

        switch (direcao)
        {

        case 0:
            nivel->monstroY -= nivel->dificuldade;
            if (nivel->monstroY < 1)
            {
                nivel->monstroY = 1;
            }
            break;

<<<<<<< Updated upstream
        case 1:
            nivel->monstroY += nivel->dificuldade;
            if (nivel->monstroY >= MAX_LINHA - 1)
            {
                nivel->monstroY = MAX_LINHA - 2;
            }
            break;
=======
void jogar()
{
    instrucoes();
    /* definicao de variaveis e structs
        definido os caracteres baseados em seus valores ascii
        gerado a struct do monstro, jogador e chave onde logo apos eles terao suas variaveis definidas aos valores padrao do jogo
    */
    int caracteres[7] = {186, 177, 241, 207, 219, 189, 196};
    tJogador jogador;
    tMonstro monstro;
    tChave chave;
    defineJogador(&jogador);
    defineMonstro(&monstro);
    defineChave(&chave);
>>>>>>> Stashed changes

        case 2:
            nivel->monstroX -= nivel->dificuldade;
            if (nivel->monstroX < 1)
            {
                nivel->monstroX = 1;
            }
            break;

        case 3:
            nivel->monstroX += nivel->dificuldade;
            if (nivel->monstroX >= MAX_COLUNA - 1)
            {
                nivel->monstroX = MAX_COLUNA - 2;
            }
            break;

        case 4:
            nivel->monstroX = nivel->monstroX;
            break;
        }

        if (nivel->jogadorX == nivel->monstroX && nivel->jogadorY == nivel->monstroY)
        {
<<<<<<< Updated upstream
            printf("\n\nO fantasma te alcancou na torre\n");
=======
            printf("\nVoce perdeu, tente da proxima vez!!\n");
            system("PAUSE");
>>>>>>> Stashed changes
            break;
        }
        else if (nivel->jogadorX == nivel->ox && nivel->jogadorY == nivel->oy && nivel->chaveObtida == 1)
        {
            printf("\n\nVoce desceu mais um andar\n");
            system("PAUSE");
            nivel->dificuldade++;
            nivel->vitoria = 1;
        }
    }
    system("PAUSE");
<<<<<<< Updated upstream
=======
    system("CLS");
    while (menu())
    {
    }
>>>>>>> Stashed changes
    return 0;
}
