#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>

GLint LARGURA = 600, ALTURA = 600;
GLfloat last_r = 0.0f, last_g = 0.0f, last_b = 0.0f;
GLint mode = 0, xi, yi, actual_point = 0;

struct Objeto{ //struct para ajudar na identificação dos tipos de objetos
    int tipo; // 0 = ponto, 1 = linha, 2 = retângulo, 3 = circulo
    int xi, yi, xf, yf;  //xi,yi: coordenadas iniciais  xf,yf:coordenadas finais
    float r, g, b;     //cores
};

std::vector<Objeto> objetos; //vector que irá guardar os objetos q já foram desenhados na tela

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
    int num_segments = 75; // número de segmentos para aproximar o círculo
    GLfloat angle;

    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        angle = 2.0f * M_PI * i / num_segments; 
        GLfloat dx = radius * cosf(angle); // calcula o componente x
        GLfloat dy = radius * sinf(angle); // calcula o componente y
        glVertex2f(x + dx, y + dy); // especifica o vértice
    }
    glEnd();
    glFlush();
}

void desenha() {  //função que vai desenhar na tela todos os objetos que já foram desenhados
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto obj : objetos) {  //resgata o obj do vetor e o desenha novamente
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
                GLfloat raio; 
                if(obj.yi > obj.yf){  //foi utilizado o critério de que o raio vai ser o modulo da diferenca entre yi e yf dividido por 2
                    raio = (obj.yi - obj.yf)/2;
                }else{
                    raio = (obj.yf - obj.yi)/2;  
                }
                desenhaCirculo(obj.xi, obj.yi, raio, obj.r, obj.g, obj.b);
        }
    }
    glFlush();
}

void eventoMouse(GLint button, GLint action, GLint x, GLint y) {
    if (mode == 0 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {  //se mode=0 então está no modo "desenhar pontos" e se o botão esq foi pressionado
        objetos.push_back({0, x, y, x, y, last_r, last_g, last_b});  //guardamos um novo ponto nos objetos (que será em breve desenhado)
        glutPostRedisplay();
    } else if (mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0) { //se modo=1 então está no modo "desenhar linha" e se actual_point=0 significa é o ponto de inicio da linha
        xi = x;
        yi = y;
        actual_point = 1;  //se o usuário já escolheu o ponto inicial, a variável recebe 1
    } else if (mode == 1 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1) {  //modo de "desenhar linhas" e se actual_point=1 significa que o usuário está determinando o ponto final da linha
        objetos.push_back({1, xi, yi, x, y, last_r, last_g, last_b});  //coloca a linha no vetor de objetos 
        actual_point = 0;   //a variável é zerada pra o usuário poder desenhar uma nova linha
        glutPostRedisplay();
    } else if (mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0) { //se modo=2 então está no modo "des. retangulos" e se actual_point=1 significa q o user está determinando o ponto que inicia o retangulo
        xi = x;
        yi = y;
        actual_point = 1;
    } else if (mode == 2 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1) { //"des. retangulo" e estamos determinando o ponto final do retangulo
        objetos.push_back({2, xi, yi, x, y, last_r, last_g, last_b}); //guardamos um retangulo na lista de objetos
        actual_point = 0;
        glutPostRedisplay();

    }else if(mode == 3 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 0){ //estamos no modo de "des. circulos" e demarcamos onde o diametro do circ. começa
        xi = x;
        yi = y;
        actual_point = 1;

    }else if(mode == 3 && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && actual_point == 1){ //estamos no modo de "des. circulos" e demarcamos onde o diametro do cir. termina 
        objetos.push_back({3, xi, yi, x, y, last_r, last_g, last_b});  //guardamos o circulo no vetor de objetos
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
        case 1:  //se a opção escolhida no menu foi 1, então determinamos mode=0 (desenhar pontos)
            mode = 0;
            break;
        case 2:  //se a opção escolhida no menu foi 2, então determinamos mode=1 (desenhar linhas)
            mode = 1;
            actual_point = 0;
            break;
        case 3:  //se a opção escolhida no menu foi 3, então determinamos mode=2 (retangulo)
            mode = 2;
            actual_point = 0;
            break;
        case 4:
            mode = 3;
            actual_point = 0;
            break;
        case 5:   //se a opcao escolhida no menu foi 5, então limpamos a tela
            objetos.clear();  //limpamos o vetor que possui todos os objetos que "estavam" na tela
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
