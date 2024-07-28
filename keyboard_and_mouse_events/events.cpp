#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>

GLint LARGURA = 600, ALTURA = 600;
GLfloat last_r = 0.0f, last_g = 0.0f, last_b = 0.0f;
GLint mode = 2, xi, yi, actual_point = 0;

struct Objeto {
    int tipo; // 0 = ponto, 1 = linha, 2 = retângulo, 3 = circulo
    int xi, yi, xf, yf;
    float r, g, b;
};

std::vector<Objeto> objetos;

void initGlut(int *argc, char **argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LARGURA, ALTURA);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((largura_tela - LARGURA) / 2, (altura_tela - ALTURA) / 2);
    glutCreateWindow("Meu segundo app com OpenGL");
}

void inicializacao(GLvoid) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, LARGURA, ALTURA, 0);
}

void desenhaPonto(GLint x, GLint y, float r, float g, float b) {
    glPointSize(3.0);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void desenhaLinha(GLint xi, GLint yi, GLint xf, GLint yf, float r, float g, float b) {
    glLineWidth(3.0);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2i(xi, yi);
    glVertex2i(xf, yf);
    glEnd();
}

void desenhaRetangulo(GLint xi, GLint yi, GLint xf, GLint yf, float r, float g, float b) {
    glLineWidth(3.0);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xi, yi);
    glVertex2i(xf, yi);
    glVertex2i(xf, yf);
    glVertex2i(xi, yf);
    glEnd();
}

void desenhaCirculo(GLint x, GLint y, GLfloat radius, float r, float g, float b) {
    int num_segments = 75; // Número de segmentos para aproximar o círculo
    GLfloat angle;

    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        angle = 2.0f * M_PI * i / num_segments; 
        GLfloat dx = radius * cosf(angle); // Calcula o componente x
        GLfloat dy = radius * sinf(angle); // Calcula o componente y
        glVertex2f(x + dx, y + dy); // Especifica o vértice
    }
    glEnd();
    glFlush();
}

void desenha(GLvoid) {
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto obj : objetos) {
        switch (obj.tipo) {
            case 0:
                desenhaPonto(obj.xi, obj.yi, obj.r, obj.g, obj.b);
                break;
            case 1:
                desenhaLinha(obj.xi, obj.yi, obj.xf, obj.yf, obj.r, obj.g, obj.b);
                break;
            case 2:
                desenhaRetangulo(obj.xi, obj.yi, obj.xf, obj.yf, obj.r, obj.g, obj.b);
                break;
            case 3:
                desenhaCirculo(obj.xi, obj.yi, (obj.yf-obj.yi), obj.r, obj.g, obj.b);
        }
    }
    glFlush();
}

void eventoMouse(GLint button, GLint action, GLint x, GLint y) {
    if (mode == 0 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        objetos.push_back({0, x, y, x, y, last_r, last_g, last_b});
        glutPostRedisplay();
    } else if (mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0) {
        xi = x;
        yi = y;
        actual_point = 1;
    } else if (mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1) {
        objetos.push_back({1, xi, yi, x, y, last_r, last_g, last_b});
        actual_point = 0;
        glutPostRedisplay();
    } else if (mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0) {
        xi = x;
        yi = y;
        actual_point = 1;
    } else if (mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1) {
        objetos.push_back({2, xi, yi, x, y, last_r, last_g, last_b});
        actual_point = 0;
        glutPostRedisplay();

    }else if(mode == 3 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0){
        xi = x;
        yi = y;
        actual_point = 1;

    }else if(mode == 3 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1){
        objetos.push_back({3, xi, yi, x, y, last_r, last_g, last_b});
        actual_point = 0;
        glutPostRedisplay();
    }
}

void eventoMouse2(GLint x, GLint y) {
    if (mode == 0) {
        objetos.push_back({0, x, y, x, y, last_r, last_g, last_b});
        glutPostRedisplay();
    }
}

void eventoTeclado(GLubyte key, GLint x, GLint y) {
    if (key == 'r' || key == 'R') {
        last_r = 1.0f;
        last_g = 0.0f;
        last_b = 0.0f;
    } else if (key == 'g' || key == 'G') {
        last_r = 0.0f;
        last_g = 1.0f;
        last_b = 0.0f;
    } else if (key == 'b' || key == 'B') {
        last_r = 0.0f;
        last_g = 0.0f;
        last_b = 1.0f;
    }
}

void menu(int option) {
    switch (option) {
        case 1:
            mode = 0;
            break;
        case 2:
            mode = 1;
            actual_point = 0;
            break;
        case 3:
            mode = 2;
            actual_point = 0;
            break;
        case 4:
            mode = 3;
            actual_point = 0;
            break;
        case 5:
            objetos.clear();
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    initGlut(&argc, argv);
    inicializacao();
    glutDisplayFunc(desenha);
    glutMouseFunc(eventoMouse);
    glutMotionFunc(eventoMouse2);
    glutKeyboardFunc(eventoTeclado);
    glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Linha", 2);
    glutAddMenuEntry("Retangulo", 3);
    glutAddMenuEntry("Circulo", 4);
    glutAddMenuEntry("Limpar tela", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
