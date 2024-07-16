#include "definitions.h"
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;


//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //*************************************************************************
    Spot any_s = {0, 0};
    Spot any_f = {256, 256};
    Color white = {255, 255, 255, 255};
    Color red = {255, 0, 0, 255};
    Color green = {0, 255, 0, 255};
    Color blue = {0, 0, 255, 255};
    PutPixel(any_s, white);
    //DrawLine(any_f, any_s, white, red);
    DrawTriangle( Spot{0, 0}, Spot{256, 256}, Spot{512, 0}, red, red, red);

}

void PutPixel (Spot q, Color p) {
    int position = (4 * q.x)+ (4 * q.y * IMAGE_WIDTH);

    FBptr[position] = p.r; // componente R
    FBptr[position+1] = p.g;   // componente G
    FBptr[position+2] = p.b;   // componente B
    FBptr[position+3] = p.a; // componente A
}

void DrawLine(Spot begin, Spot end, Color b) {
    // Calcula a diferença absoluta entre as coordenadas x dos pontos de início e fim
    int dx = abs(end.x - begin.x);
    // Calcula a diferença absoluta entre as coordenadas y dos pontos de início e fim
    int dy = abs(end.y - begin.y);

    // Determina a direção do incremento de x: se o ponto de início é menor que o ponto final, incrementa x; caso contrário, decrementa x
    int sx = (begin.x < end.x) ? 1 : -1;
    // Determina a direção do incremento de y: se o ponto de início é menor que o ponto final, incrementa y; caso contrário, decrementa y
    int sy = (begin.y < end.y) ? 1 : -1;

    // Inicializa a variável de erro para controle do algoritmo de Bresenham
    int err = dx - dy;

    // Loop infinito para traçar a linha pixel por pixel
    while (true) {
        // Coloca um pixel na posição atual
        PutPixel(Spot{begin.x, begin.y}, b);

        // Se o ponto atual é igual ao ponto final, termina o loop
        if (begin.x == end.x && begin.y == end.y) break;

        // Calcula o dobro do erro atual
        int e2 = 2 * err;

        // Ajusta o erro e a coordenada x se necessário
        if (e2 > -dy) {
            err -= dy;
            begin.x += sx;
        }

        // Ajusta o erro e a coordenada y se necessário
        if (e2 < dx) {
            err += dx;
            begin.y += sy;
        }
    }
}

void DrawTriangle(Spot a, Spot b, Spot c, Color ab, Color ac, Color bc) {
    // Desenha uma linha entre os pontos a e b com as cores ca e cb
    DrawLine(a, b, ab);

    // Desenha uma linha entre os pontos a e c com as cores ca e cc
    DrawLine(a, c, ac);

    // Desenha uma linha entre os pontos b e c com as cores cb e cc
    DrawLine(b, c, bc);
}
