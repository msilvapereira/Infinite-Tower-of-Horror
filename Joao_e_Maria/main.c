#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINHA 10
#define MAX_COLUNA 40

typedef struct
{
    //char nome[50];
    int jogadorX;
    int jogadorY;
    int chaveObtida;
    int controle, direcao;
} tJogador;

void defineJogador(tJogador *jogador)//, char[] pnome)
{
    //jogador.nome[] = pnome[];
    jogador->jogadorX = 1;
    jogador->jogadorY = 1;
    jogador->chaveObtida = 0;
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

void jogar()
{
    tJogador jogador;
    tMonstro monstro;
    defineJogador(&jogador);
    defineMonstro(&monstro);
    geraNivel(jogador, monstro);
}

void geraNivel(tJogador jogador, tMonstro monstro)
{
    int caracteres[7] = {186, 177, 241, 207, 219, 189, 196};
    int parede[5] = {20, 39, 0, 9, 4};
    int x, y, ox = MAX_COLUNA - 2, oy = MAX_LINHA - 2;
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
          //  else if (x == cx && y == cy)
          //  {
          //      printf("%c", caracteres[5]);
          //  }
            else
            {
                printf("%c", caracteres[6]);
            }
        }
        printf("\n");
    }
}

int main()
{
    jogar();
}
