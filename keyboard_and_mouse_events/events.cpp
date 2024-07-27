#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLint LARGURA = 600,
      ALTURA = 600;

GLfloat last_r, last_g, last_b;
GLint mode = 2;
GLint xi, yi, actual_point = 0;

void initGlut(int *argc, char **argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LARGURA, ALTURA);
    // Especifica a posição inicial da janela GLUT
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition( (largura_tela-LARGURA)/2, (altura_tela-ALTURA)/2);

    glutCreateWindow("Meu segundo app com OpenGL");
}

void inicializacao(GLvoid){
    // Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
                //esquerda, direita, baixo, cima
    gluOrtho2D(0, LARGURA, ALTURA, 0);
}

void desenharPonto(GLint x, GLint y){
    glPointSize(3.0);
        glColor3f(last_r, last_g, last_b);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
}

void desenharLinha(GLint xi, GLint yi, GLint xf, GLint yf) {
    glLineWidth(3.0); // Define a largura da linha

    glBegin(GL_LINES);
        glColor3f(last_r, last_g, last_b); // Define a cor da linha
        glVertex2i(xi, yi); // Ponto inicial da linha
        glVertex2i(xf, yf); // Ponto final da linha
    glEnd();
    glFlush(); // Garante que todos os comandos OpenGL sejam executados
}

void desenharRetangulo(GLint xi, GLint yi, GLint xf, GLint yf){
    glLineWidth(3.0); // Define a largura da linha

    glBegin(GL_LINE_LOOP);
        glColor3f(last_r, last_g, last_b); // Define a cor da linha
        glVertex2i(xi, yi); // Ponto inicial da linha
        glVertex2i(xf, yi); // Ponto final da linha
        glVertex2i(xf, yf); // Ponto final da linha
        glVertex2i(xi, yf); // Ponto final da linha
    glEnd();
    glFlush(); // Garante que todos os comandos OpenGL sejam executados
}

void desenharTriangulo(GLvoid){
    glLineWidth(5.0);
    glBegin(GL_TRIANGLES);
        // Altera a cor do desenho para vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(300, 100);
        // Altera a cor do desenho para verde
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(100, 500);
        // Altera a cor do desenho para Azul
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(500, 500);
    glEnd();
}

void desenha(GLvoid){
    glClear(GL_COLOR_BUFFER_BIT); 
    glFlush();
}

void eventoMouse(GLint button, GLint action, GLint x, GLint y){
    if(mode == 0 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        desenharPonto(x, y);
    } 

    else if(mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0){
        xi = x;
        yi = y;
        actual_point = 1;
    } 
    else if(mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1){
        desenharLinha(xi, yi, x, y);
        actual_point = 0;
    }
    else if(mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0){
        xi = x;
        yi = y;
        actual_point = 1;
    } 
    else if(mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1){
        desenharRetangulo(xi, yi, x, y);
        actual_point = 0;
    }


}


void eventoMouse2(GLint x, GLint y){
    //desenha pontos na tela enquanto o mouse estiver com o botao esquerdo pressionado
    if(mode == 0) desenharPonto(x, y);
}

void eventoTeclado(GLubyte key, GLint x, GLint y){
    if(key == 'r' || key == 'R'){
        printf( "opa");
        last_r = 255;
        last_g = 0;
        last_b = 0;
    
    }else if(key == 'g' || key == 'G'){
        last_r = 0;
        last_g = 255;
        last_b = 0;

    }else if(key == 'b' || key == 'B'){
        last_r = 0;
        last_g = 0;
        last_b = 255;
    }
}


int main(int argc, char *argv[])
{
    initGlut(&argc, argv);
    inicializacao();
    last_r = 0;
    last_g = 0;
    last_b = 0;
    glutDisplayFunc(desenha);
    glutMouseFunc(eventoMouse);
    glutMotionFunc(eventoMouse2);
    glutKeyboardFunc(eventoTeclado);
    glutMainLoop();
    return 0;
}
