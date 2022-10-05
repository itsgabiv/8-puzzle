#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int quadro[3][3], espacoX, espacoY;

bool moverPosicao(int pX, int pY)
{
    int temporario;

    if ((pX == espacoX) && (pY == espacoY))
        return false;

    bool bateuNaEsquerda = pX < 0;
    bool bateuEmCima = pY < 0;
    bool bateuNaDireita = pX > 2;
    bool bateuEmBaixo = pY > 2;

    if (bateuNaEsquerda || bateuEmBaixo || bateuNaDireita || bateuEmCima)
        return false;

    int diferencaX = abs(espacoX - pX);
    int diferencaY = abs(espacoY - pY);
    int distanciaDoNumeroParaEspaco = diferencaX + diferencaY;
    if (distanciaDoNumeroParaEspaco > 1)
        return false;

    temporario = quadro[espacoX][espacoY]; // guarda a coordenada do espaco
    quadro[espacoX][espacoY] = quadro[pX][pY]; // define no lugar do espaco o valor no numero que estava em pX e pY
    quadro[pX][pY] = temporario; // define no lugar do numero o espaco em branco

    espacoX = pX;
    espacoY = pY;

    return true;
}

void obterCoordenadaDoNumero(int pNumero, int *pX, int *pY)
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (quadro[x][y] == pNumero)
            {
                *pX = x;
                *pY = y;
            }
        }
    }
}

bool movimentarQuadrado(int pNumero)
{
    int posicaoX, posicaoY;

    obterCoordenadaDoNumero(pNumero, &posicaoX, &posicaoY);

    if (!moverPosicao(posicaoX, posicaoY))
        return false;

    return true;
}

void imprimirQuadro()
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (quadro[x][y] == 0)
                printf("  ");
            else
                printf("%d ", quadro[x][y]);
        }
        printf("\n");
    }
}

void embaralharQuadro()
{
    int x,y;
    unsigned seed = time(NULL);
    srand(seed);

    bool parar;
    int rodadas = 25;
    for (int rodada = 1; rodada <= rodadas; rodada++)
    {
        parar = false;
        while (!parar)
        {
            x = rand() % 3 - 1;
            y = rand() % 3 - 1;

            parar = moverPosicao(espacoX + x, espacoY + y);
        }

        imprimirQuadro();
        system("cls");
        sleep(0.005);
    }
}

void escolherJogada()
{
    bool podeMover = false;

    while (!podeMover)
    {
        podeMover = true;
        printf("Escolha um numero para mover: ");

        int numero = getchar() -48; // TABELA ASCII

        if ((numero < 1) || (numero > 8))
        {
            podeMover = false;
            printf("O numero deve ser entre 1 e 8!\n");
            continue;
        }

        if (!movimentarQuadrado(numero))
        {
            podeMover = false;
            printf("O numero %d nao pode ser movido!\n", numero);
        }
    }
}

void iniciaQuadro()
{
    int numero = 1;

    for (int y = 0; y<3; y++)
    {
        for (int x = 0; x < 3; x++)
            quadro[x][y] = numero++;
    }

    quadro[2][2] = 0;
    espacoX = 2;
    espacoY = 2;
}

bool verificarConquista()
{
    int numero = 1;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (quadro[x][y] != (numero++ % 9))
                return false;
        }
    }

    return true;
}

void iniciarJogo()
{
    iniciaQuadro();
    embaralharQuadro();

    while (!verificarConquista())
    {
        imprimirQuadro();
        escolherJogada();
        system("cls");
    }

    imprimirQuadro();
    printf("Parabens, jogo terminado.\n");
}

int main()
{
    iniciarJogo();
    system("pause");
    return 0;
}


