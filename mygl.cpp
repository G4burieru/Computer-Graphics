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
    Spot any_f = {0, 0};
    Spot any_s = {256, 256};
    Color white = {255, 255, 255, 255};
    PutPixel(any_s, white);
    DrawLine(any_f, any_s, white, white);

}

void PutPixel (Spot q, Color p) {
    // Escreve um pixel vermelho na posicao (0,0) da tela
    int position = (4 * q.x)+ (4 * q.y * IMAGE_WIDTH);

    FBptr[position] = p.r; // componente R
    FBptr[position+1] = p.g;   // componente G
    FBptr[position+2] = p.b;   // componente B
    FBptr[position+3] = p.a; // componente A
}

void DrawLine (Spot begin, Spot end, Color b, Color e)
{
    int dx = end.x - begin.x;
    int dy = end.y - begin.y;
    int x = begin.x;
    int y = begin.y;
    int error = 0;

    while (x < end.x)
    {
        PutPixel(Spot{x, y}, b);
        x = x + 1;
        error = error + 2*dy;

        if (error >= dx){
            y = y + 1;
            error = error - 2*dx;
        }
    }
}