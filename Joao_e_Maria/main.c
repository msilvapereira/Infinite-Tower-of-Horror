#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINHA 10
#define MAX_COLUNA 40
#define ox (MAX_COLUNA - 2)
#define oy (MAX_LINHA - 2)

typedef struct
{
    //char nome[50];
    int jogadorX;
    int jogadorY;
    int chaveObtida;
    int controle;
    int dificuldade;
    int vitoria;
    int derrota;
} tJogador;

void defineJogador(tJogador *jogador)//, char[] pnome)
{
    //jogador.nome[] = pnome[];
    jogador->jogadorX = 1;
    jogador->jogadorY = 1;
    jogador->chaveObtida = 0;
    jogador->controle = 0;
    jogador->dificuldade = 1;
    jogador->derrota = 0;
}

typedef struct
{
    int monstroX;
    int monstroY;
} tMonstro;

void defineMonstro(tMonstro *monstro)
{
    monstro->monstroX = (int)(MAX_COLUNA * 0.4);
    monstro->monstroY = (int)(MAX_LINHA * 0.8);
}

typedef struct
{
    int chaveDefinida;
    int chaveX;
    int chaveY;
} tChave;

void defineChave(tChave *chave)
{
    chave->chaveDefinida = 0;
    chave->chaveX = 0;
    chave->chaveY = 0;
}

void geraNivel(tJogador jogador, tMonstro monstro, tChave *chave, int *pCaracteres)
{
    srand(time(NULL));
    int caracteres[7];
    for (int i = 0; i < 7; i++)
    {
        caracteres[i] =  pCaracteres[i];
    }
    int parede[5] = {20, 39, 0, 9, 4};
    int x, y;

    if (jogador.chaveObtida == 0 && chave->chaveDefinida == 0)
    {
        while (chave->chaveX == parede[0] || chave->chaveX == parede[1]|| chave->chaveX == parede[2] || chave->chaveY == parede[2] || chave->chaveY == parede[3])
        {
            chave->chaveX = (int)(rand() % MAX_COLUNA);
            chave->chaveY = (int)(rand() % MAX_LINHA);
        }
        chave->chaveDefinida = 1;
    }

    for (y = 0; y < MAX_LINHA; y++)
    {
        for (x = 0; x < MAX_COLUNA; x++)
        {

            if (x == parede[0] && y != parede[2] && y != parede[3] && y != parede[4])
            {
                printf("%c", caracteres[0]);
            }
            else if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
            {
                printf("%c", caracteres[1]);
            }

            else if (x == jogador.jogadorX && y == jogador.jogadorY)
            {
                printf("%c", caracteres[2]);
            }
            else if (x == monstro.monstroX && y == monstro.monstroY)
            {
                printf("%c", caracteres[3]);
            }
            else if (x == ox && y == oy)
            {
                printf("%c", caracteres[4]);
            }
            else if (x == chave->chaveX && y == chave->chaveY)
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
}

void andar(tJogador *jogador, tMonstro *monstro, tChave *chave)
{
    int direcao;
    scanf("%i", &jogador->controle);
    setbuf(stdin, NULL);
    switch(jogador->controle)
    {

    case 8:
        jogador->jogadorY -= 1;
        if(jogador->jogadorY < 1)
        {
            jogador->jogadorY = 1;
        }
        else if (jogador->jogadorX == 20)
        {
            jogador->jogadorY = 4;
        }
        break;

    case 5:
        jogador->jogadorY += 1;
        if(jogador->jogadorY >= MAX_LINHA - 1)
        {
            jogador->jogadorY = MAX_LINHA -2;
        }
        else if (jogador->jogadorX == 20)
        {
            jogador->jogadorY = 4;
        }
        break;

    case 4:
        jogador->jogadorX -= 1;
        if (jogador->jogadorX < 1)
        {
            jogador->jogadorX = 1;
        }
        else if (jogador->jogadorY != 4)
        {
            if (jogador->jogadorX == 20)
            {
                jogador->jogadorX = 21;
            }
        }
        break;

    case 6:
        jogador->jogadorX += 1;
        if(jogador->jogadorX >= MAX_COLUNA - 1)
        {
            jogador->jogadorX = MAX_COLUNA -2;
        }
        else if (jogador->jogadorY != 4)
        {
            if (jogador->jogadorX == 20)
            {
                jogador->jogadorX = 19;
            }
        }
        break;

    default:
        printf("\nComando invalido!\n");
        system("PAUSE");
    }

    if (jogador->jogadorY == monstro->monstroY)
    {
        if (jogador->jogadorX > monstro->monstroX)
        {
            direcao = 3;
        }
        else if (jogador->jogadorX == monstro->monstroX)
        {
            direcao = 4;
        }
        else
        {
            direcao = 2;
        }
    }
    else if (jogador->jogadorX == monstro->monstroX)
    {
        if (jogador->jogadorY > monstro->monstroY)
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

    switch(direcao)
    {

    case 0:
        monstro->monstroY -= jogador->dificuldade;
        if  (monstro->monstroY < 1)
        {
            monstro->monstroY = 1;
        }
        break;

    case 1:
        monstro->monstroY += jogador->dificuldade;
        if  (monstro->monstroY >= MAX_LINHA - 1)
        {
            monstro->monstroY = MAX_LINHA - 2;
        }
        break;

    case 2:
        monstro->monstroX -= jogador->dificuldade;
        if (monstro->monstroX < 1)
        {
            monstro->monstroX = 1;
        }
        break;

    case 3:
        monstro->monstroX += jogador->dificuldade;
        if (monstro->monstroX >= MAX_COLUNA - 1)
        {
            monstro->monstroX = MAX_COLUNA - 2;
        }
        break;

    case 4:
        monstro->monstroX = monstro->monstroX;
        break;

    }

    if (jogador->jogadorY == chave->chaveY && jogador->jogadorX == chave->chaveX)
    {
        jogador->chaveObtida = 1;
        chave->chaveY = 0;
        chave->chaveX = 0;
    }

    if (jogador->jogadorX == monstro->monstroX && jogador->jogadorY == monstro->monstroY)
    {
        printf("\n\nO fantasma te alcancou na torre\n");
        jogador->derrota = 1;
    }
    else if (jogador->jogadorX == ox && jogador->jogadorY == oy && jogador->chaveObtida == 1)
    {
        printf("\n\nVoce desceu mais um andar\n");
        system("PAUSE");
        jogador->dificuldade++;
        jogador->jogadorX = 1;
        jogador->jogadorY = 1;
        jogador->chaveObtida = 0;
        monstro->monstroX = (int)(MAX_COLUNA * 0.4);
        monstro->monstroY = (int)(MAX_LINHA * 0.8);
        chave->chaveDefinida = 0;
    }
}

void jogar()
{
    int caracteres[7] = {186, 177, 241, 207, 219, 189, 196};
    tJogador jogador;
    tMonstro monstro;
    tChave chave;
    defineJogador(&jogador);
    defineMonstro(&monstro);
    defineChave(&chave);
    for (;;)
    {

        geraNivel(jogador, monstro, &chave, caracteres);
        printf("Controles: 8 (cima)\t6 (direita)\t5 (baixo)\t4 (esquerda)\n\n");
        printf("Fantasma - %c \nPlayer - %c \nChave - %c \nPorta - %c \n\n", caracteres[3], caracteres[2], caracteres[5], caracteres[4]);
        printf("Sua vez! Digite um comando:  ");
        andar(&jogador, &monstro, &chave);
        if(jogador.derrota == 1)
        {
            break;
        }
        system("CLS");
    }
}



int main()
{
    jogar();
}
