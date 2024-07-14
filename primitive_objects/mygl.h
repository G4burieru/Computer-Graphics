#ifndef _MYGL_H_
#define _MYGL_H_
#endif

#include "definitions.h"

struct Spot{
    int x;
    int y;
};

struct Color{
    int r;
    int g;
    int b;
    int a;
};


//-----------------------------------------------------------------------------
void MyGlDraw(void);

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

void PutPixel(Spot q, Color p);
void DrawLine(Spot begin, Spot end, Color b, Color e);
void DrawTriangle(Spot a, Spot b, Spot c, Color ca, Color cb, Color cc);