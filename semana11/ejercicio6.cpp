#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <random>
#include <iostream>

void dibujarEjes(void);
void init(void);
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void graficaCurvaBezier(void);
float CoeficienteNewton(int, int);
float factorial(int);
float CurvaBezier(float, int);
void controlRaton(int, int, int, int);
void graficaPuntosBezier(void);
void menu();
void generarAleatorios();

struct punto
{
    double x = 0;
    double y = 0;
    struct punto *sgte;
};

float dim = 1000, xOrtho = 20, yOrtho = 20;
int N = 0, paso = 0, mainMenu;
double X0, Y0;
bool activarMouse = false;

typedef struct punto *Tlista;
Tlista lista = NULL;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(dim, dim);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Grafico de una curva de Bezier 2D");
    menu();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(controlRaton);
    glutMainLoop();
    return 0;
}
/********************/
void dibujarEjes(void)
{
    glBegin(GL_LINES);
    glVertex2f(-20, 0);
    glVertex2f(20, 0);
    glVertex2f(0, -20);
    glVertex2f(0, 20);
    glEnd();
}
/********************/
void init(void)
{
    // parametros: rojo, amarillo y azul, el cuarto es el parametro alpha
    // color de fondo
    glClearColor(0.1, 0.2, 0.4, 0.5);
    glShadeModel(GL_FLAT);
}
/********************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // salva el estado actual de la matriz
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    dibujarEjes();
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(X0, Y0);
    glEnd();
    if (paso == 1)
    {
        glPointSize(5);
        graficaPuntosBezier();
        glPointSize(1);
        glColor3f(0.0, 1.0, 0.0);
        graficaCurvaBezier();
    }
    glPopMatrix();
    // reecupera el estado del matriz
    glFlush();
}
/********************/
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'b':
        paso = 1;

        // se grafica la curva de Bezier
        glutPostRedisplay();
        break;

    case 27:
        exit(0);
        break;
    }
}
/********************/
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-xOrtho, xOrtho, -yOrtho, yOrtho, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/********************/
void graficaPuntosBezier()
{
    Tlista t = lista;
    float x, y;
    glBegin(GL_POINTS);
    while (t != NULL)
    {
        x = t->x;
        y = t->y;
        glVertex2f(x, y);
        t = t->sgte;
    }
    glEnd();
}
/********************/
void graficaCurvaBezier(void)
{
    float x, y;
    glBegin(GL_LINE_STRIP);
    glLineWidth(3.0);
    for (float u = 0.0; u <= 1; u += 0.01)
    {
        x = CurvaBezier(u, 0);
        y = CurvaBezier(u, 1);
        glVertex2f(x, y);
    }
    glEnd();
}
/********************/
float CoeficienteNewton(int n, int k)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}
/********************/
float factorial(int n)
{
    float p = 1;
    for (int i = 1; i <= n; i++)
        p = p * (float)i;
    return p;
}
/********************/
float CurvaBezier(float u, int coordenada)
{
    Tlista t = lista;
    float suma = 0.0;
    bool coor = coordenada == 0;
    int i = 0;
    while (t != NULL)
    {
        suma = suma + (coor ? t->x : t->y) * CoeficienteNewton(N - 1, i) * pow(u, N - 1 - i) * pow(1.0 - u, i);
        t = t->sgte;
        i++;
    }
    return suma;
}
/********************/

void insertarFinal(double x, double y)
{
    Tlista t;
    Tlista q = new (struct punto);

    q->x = x;
    q->y = y;
    q->sgte = NULL;

    if (lista == NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while (t->sgte != NULL)
        {
            t = t->sgte;
        }
        t->sgte = q;
    }
    N++;
}

void limpiar(){
    Tlista t = lista;
    t = NULL;
    while(t->sgte != NULL){
        t = NULL;
        t = t->sgte;
    }
    N = 0; 
}

void menuFunc(int value){
    switch (value)
    {
    case 1:
        activarMouse = true;
        break;
    case 2:
        activarMouse = false;
        generarAleatorios();
    default:
        limpiar();
        break;
    }
}

void menu(){
    mainMenu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Dibujar Con Mouse", 1);
    glutAddMenuEntry("Dibujar Con Random", 2);
    glutAddMenuEntry("Limpiar", 3);
    glutSetMenu(mainMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void controlRaton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && activarMouse)
    {
        X0 = (x / ((dim / 2) / xOrtho)) - xOrtho;
        Y0 = (y / -((dim / 2) / yOrtho)) + yOrtho;
        std::cout << "X: " << X0 << "Y: " << Y0 << std::endl;
        insertarFinal(X0, Y0);
    }
}

void generarAleatorios()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-20.0, 20.0);
    for (int i = 0; i < 2; ++i)
    {
        float x = dist(rng);
        float y = dist(rng);
        insertarFinal(x, y);
    }
}