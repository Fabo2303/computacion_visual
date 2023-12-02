#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

void dibujarEjes(void);
void init(void);
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void graficaCurvaBezier(void);
float CoeficienteNewton(int, int);
float factorial(int);
float CurvaBezier(float, int);
void graficaPuntosBezier(void);

float dim = 400;
float pcontrol[7][2] = {{-10.0, 0.0}, {-10.0, 10.0}, {10.0, 10.0}, {10.0, 0.0}, {10.0, -10.0}, {0.0, -0.0}, {0, 0}};
int N = 7, paso = 0;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(dim, dim);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Grafico de una curva de Bezier 2D");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
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
    glClearColor(0.0, 0.5, 0.5, .0);
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
    case 'n':
        paso = 0;

        // No se grafica la curva de Bezier
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
    glOrtho(-20.0, 20.0, -20.0, 20, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/********************/
void graficaPuntosBezier(void)
{
    float x, y;
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++)
    {
        x = pcontrol[i][0];
        y = pcontrol[i][1];
        glVertex2f(x, y);
        getch();
    }
    glEnd();
}
/********************/
void graficaCurvaBezier(void)
{
    float x, y;
    glBegin(GL_LINE_STRIP);
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
    float suma = 0.0;
    for (int i = 0; i < N; i++)
    {
        suma = suma + pcontrol[i][coordenada] * CoeficienteNewton(N - 1, i) * pow(u, N - 1 - i) * pow(1.0 - u, i);
    }
    return suma;
}
/********************/