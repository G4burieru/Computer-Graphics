#ifndef _MYGL_H_
#define _MYGL_H_
#endif

#include "definitions.h"

struct Spot{
    short int x;
    short int y;
};

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};


//-----------------------------------------------------------------------------
void MyGlDraw(void);

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

void PutPixel(Spot q, Color p);
void DrawLine(Spot begin, Spot end, Color b);
void DrawTriangle(Spot a, Spot b, Spot c, Color ca, Color cb, Color cc);