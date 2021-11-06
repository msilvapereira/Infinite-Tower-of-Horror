#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINHA 10
#define MAX_COLUNA 40
#define ox (MAX_COLUNA - 2)
#define oy (MAX_LINHA - 2)
#define TAM_NOME 100

// Define as principais caracteristicas do jogador
typedef struct
{
    int jogadorX;
    int jogadorY;
    int chaveObtida;
    int controle;
    int dificuldade;
    int vitoria;
    int derrota;
} tJogador;

// Adiciona um valor padrao ao endereco da memoria de quando o jogador e instanciado
void defineJogador(tJogador *jogador)
{
    jogador->jogadorX = 1;
    jogador->jogadorY = 1;
    jogador->chaveObtida = 0;
    jogador->controle = 0;
    jogador->dificuldade = 1;
    jogador->derrota = 0;
}

// Define as caracteristicas gerais do monstro
typedef struct
{
    int monstroX;
    int monstroY;
} tMonstro;

// Adiciona um valor padrao ao endereco da memoria de quando o monstro e instanciado
void defineMonstro(tMonstro *monstro)
{
    monstro->monstroX = (int)(MAX_COLUNA * 0.4);
    monstro->monstroY = (int)(MAX_LINHA * 0.8);
}

// Define as caracteristicas gerais do jogador
typedef struct
{
    int chaveDefinida;
    int chaveX;
    int chaveY;
} tChave;

// Adiciona um valor padrao ao endereco da memoria de quando a chave e instanciada
void defineChave(tChave *chave)
{
    chave->chaveDefinida = 0;
    chave->chaveX = 0;
    chave->chaveY = 0;
}

// Define as caracteristicas da struct nome
typedef struct
{
    char jogador[TAM_NOME];
    char pontuacao;
} tNome;

// Define valores padroes a struct nome
void limpartNome(tNome *p)
{
    for (int i = 0; i < TAM_NOME; i++)
    {
        p->jogador[i] = '\0';
    }
    p->pontuacao = 0;
}

// menu que sera executado
int menu()
{
    char opcao = '0';

    system("cls");
    printf("\n\n======= INFINITE TOWER OF HORROR =======\n\n");
    printf("\n[ 1 ] - Jogar");
    printf("\n[ 2 ] - Como jogar");
    printf("\n[ 3 ] - Bestiario");
    printf("\n[ 4 ] - Sair\n");

    fflush(stdin);
    // pegar a opcao desejada do usuario
    opcao = getchar();

    switch (opcao)
    {
    case '1':
        jogar();
        break;
    case '2':
        comoJogar();
        break;
    case '3':
        bestiario();
        break;
    case '4':
        return 0;
    default:
        printf("\nOpcao invalida\n");
        system("PAUSE");
    }

    return 1;
}

// informacoes dos monstros do jogo
void bestiario()
{
    system("cls");
    printf("\n\n======= ======= ======= BESTIARIO\n\n");
    printf("\n1o Fantasma");
    printf("\n1.1 Wraith: e um fantasma que atravessa paredes e costuma se irritar quando se sente enganado.");
    printf("\n\n");

    system("PAUSE");
}

// instruções de como é jogado o jogo
void comoJogar()
{
    system("cls");
    printf("\n\nPara jogar voce deve selecionar a opcao Jogar no menu, e apos isso ira comecar o jogo onde...");
    printf("\n\nVoce enquanto jogador deve fugir do monstro, pegar a chave e passar pela saida para alcancar o proximo nivel.");
    printf("\n\nSeus controles para movimentacao consistem nas telcas W, A, S, D onde respectivamente o movimenta para cima, esquerda,  baixo e direita");
    printf("\n\n");

    system("PAUSE");
    system("cls");
}

// Funcao que ira receber o nome do jogador e a pontuacao para salvar
void nomeJogador(tJogador *jogador)
{
    // gerado a struct novoNome e logo em seguido "limpada"
    tNome novoNome;
    FILE *arq;
    limpartNome(&novoNome);

    system("cls");
    printf("\nIdentificacao ");
    printf("\n\nDigite o nome do Jogador para salvar sua pontuacao: ");

    // Limpado o teclado e recebe o nome do jogador
    fflush(stdin);
    fgets(novoNome.jogador, TAM_NOME, stdin);

    printf("\n\nSalvo no arquivo jogador.prog");

    novoNome.pontuacao = jogador->dificuldade;

    printf("\nTente na proxima %s!", &novoNome.jogador);

    arq = fopen("jogador.prog", "ab");

    // digita no arquivo
    fprintf(arq, "\nPontuacao: ");
    fprintf(arq, "%d \n", novoNome.pontuacao);
    fprintf(arq, "Nome:  ");

    fwrite(&novoNome, 50, 2, arq);

    fclose(arq);
}

// funcao que ira desenhar o mapa do jogo
void geraNivel(tJogador jogador, tMonstro monstro, tChave *chave, int *pCaracteres)
{
    srand(time(NULL)); //linha necessaria para gerar valores aleatorios baseado no tempo

    /*
    Declaracao de variaveis locais da funcao onde:
        vetor caracteres sera usado para desenhar o mapa do jogo (onde os caracteres sao recebidos de outra função);
        vetor parede sera usado tambem para auxilio no desenho do mapa;
        e variaveis x e y que serão utilizadas para os lacos de repeticao dos dois for.
    */
    int caracteres[7];
    for (int i = 0; i < 7; i++)
    {
        caracteres[i] = pCaracteres[i];
    }
    int parede[5] = {20, 39, 0, 9, 4};
    int x, y;

    /*
    Sequencia que gera a posicao da chave (de maneira aleatoria),
    onde antes e checado se o jogador ja nao pegou a chave e se ela ja nao foi definida antes

    OBS: a chave nao sera gerada dentro das paredes do jogo.
    */
    if (jogador.chaveObtida == 0 && chave->chaveDefinida == 0)
    {
        while (chave->chaveX == parede[0] || chave->chaveX == parede[1] || chave->chaveX == parede[2] || chave->chaveY == parede[2] || chave->chaveY == parede[3])
        {
            chave->chaveX = (int)(rand() % MAX_COLUNA);
            chave->chaveY = (int)(rand() % MAX_LINHA);
        }
        chave->chaveDefinida = 1;
    }

    //Lacos de repeticao para simular uma matriz
    for (y = 0; y < MAX_LINHA; y++)
    {
        for (x = 0; x < MAX_COLUNA; x++)
        {
            //A partir daqui os ifs dentro desta repeticao irao checar onde se encontra cada elemento visual do jogo e representa-los no desenho
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

// funcao que controla o movimento do jogador, do monstro e a condicao de vitoria e derrota
void andar(tJogador *jogador, tMonstro *monstro, tChave *chave)
{
    // linha necessaria para gerar valores aleatorios baseado no tempo
    srand(time(NULL));

    // variavel direcao que sera usada para guiar o monstro caso ele veja o jogador (mesmo X ou mesmo Y)
    int direcao;

    do
    {
        switch (tolower(getch()))
        {
        case 'w':
            jogador->jogadorY -= 1;
            if (jogador->jogadorY < 1)
            {
                jogador->jogadorY = 1;
            }
            else if (jogador->jogadorX == 20)
            {
                jogador->jogadorY = 4;
            }
            break;

        case 's':
            jogador->jogadorY += 1;
            if (jogador->jogadorY >= MAX_LINHA - 1)
            {
                jogador->jogadorY = MAX_LINHA - 2;
            }
            else if (jogador->jogadorX == 20)
            {
                jogador->jogadorY = 4;
            }
            break;

        case 'a':
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

        case 'd':
            jogador->jogadorX += 1;
            if (jogador->jogadorX >= MAX_COLUNA - 1)
            {
                jogador->jogadorX = MAX_COLUNA - 2;
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
    } while (kbhit());

    // linha de ifs que ira analisar se o jogador se encontra na visao do monstro
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
    // e caso ele nao veja o jogador sera gerado uma direcao aleatoria para o monstro ir
    else
    {
        direcao = rand() % 4;
    }

    // switch-case que ira movimentar o monstro de acordo com a direcao dada anteriormente
    switch (direcao)
    {

    case 0:
        monstro->monstroY -= jogador->dificuldade;
        if (monstro->monstroY < 1)
        {
            monstro->monstroY = 1;
        }
        break;

    case 1:
        monstro->monstroY += jogador->dificuldade;
        if (monstro->monstroY >= MAX_LINHA - 1)
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

    // as linhas abaixo irão analisar o que ocorreu apos toda movimentacao de jogo, ou seja:
    // esta estrutura de if ira ver se o jogador conseguiu obter a chave estando no mesmo lugar que ela
    if (jogador->jogadorY == chave->chaveY && jogador->jogadorX == chave->chaveX)
    {
        jogador->chaveObtida = 1;
        chave->chaveY = 0;
        chave->chaveX = 0;
    }

    // esta estrutura if-else ira ver se o jogador se encontrou com o monstro ou alcancou a saida enquanto possuia a chave em suas maos
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

// inicia o jogo por inteiro
void jogar()
{
    comoJogar();
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

    // repeticao infinita para o jogo continuar rodando, tendo seu motivo de quebra a derrota do jogador
    for (;;)
    {
        // gerado o nivel passando como parametro o jogador, monstro, chave (por referencia de memoria) e caracteres
        geraNivel(jogador, monstro, &chave, caracteres);

        // explicacao dos controles do jogo
        printf("Controles: W (cima)\tD (direita)\tS (baixo)\tA (esquerda)\n\n");
        // pequena linha onde demonstra o que cada caracter usado sera no jogo
        printf("Fantasma - %c \nPlayer - %c \nChave - %c \nPorta - %c \n\n", caracteres[3], caracteres[2], caracteres[5], caracteres[4]);

        // execucao da funcao onde o jogador ira andar, e seus parametros serao todos passados por referencia pois eles vao ter uma modificao que sera usada em outras funcoes
        printf("Sua vez! Digite um comando:  ");
        andar(&jogador, &monstro, &chave);

        // estrutura if que ira verificar se a struct do jogador recebeu o valor de 1 decretando assim a derrota do jogador
        if (jogador.derrota == 1)
        {
            printf("\nVoce perdeu, tente da proxima vez!!\n");
            system("PAUSE");
            nomeJogador(&jogador);
            break;
        }
        system("CLS");
    }
}

int main()
{
    while (menu())
    {
    }
    return 0;
}
