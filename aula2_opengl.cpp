#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLint LARGURA = 600,
      ALTURA = 600;

float last_r, last_g, last_b;
bool mousePressed = false;

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
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        mousePressed = true; 
        desenharPonto(x, 480 - y);

    } else if(button == GLUT_LEFT_BUTTON && action == GLUT_UP){
        mousePressed = false; 
        printf("Botão esquerdo liberado na posição %dx%d\n", x, y);
    } else if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
        printf("Botão direito pressionado na posição %dx%d\n", x, y);
    } else if(button == GLUT_RIGHT_BUTTON && action == GLUT_UP){
        printf("Botão direito liberado na posição %dx%d\n", x, y);
    }
}

}
void eventoMouse3(GLint x, GLint y){
    printf("clicando x=%d e y=%d\n", x, y);
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

void eventoTecladoEsp(GLint key, GLint x, GLint y){
    printf("Evento teclado especial disparado\n");
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
    glutPassiveMotionFunc(eventoMouse2);
    glutMotionFunc(eventoMouse3);
    glutKeyboardFunc(eventoTeclado);
    glutSpecialFunc(eventoTecladoEsp);
    glutMainLoop();
    return 0;
}
