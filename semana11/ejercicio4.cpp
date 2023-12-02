#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include <iostream>
#define miLista 1

void ejes(int);
void graficaCurvaBezier(void);
float CoeficienteNewton(int, int);
float factorial(int);
float CurvaBezier(float, int);
void graficaPuntosBezier(void);

GLdouble angulo = 0, incremento_angulo = 0.1;
GLdouble angulo2 = 0, incremento_angulo2 = 0.1;
GLdouble const radio = 0.5;
GLfloat px0 = 0, py0 = 0, pz0 = 5;
GLfloat px1 = 0, py1 = 0, pz1 = 4;
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;
float pcontrol[7][3] = {{-3.0, 0.0, 3.0}, {-3.0, 3.0, -3.0}, {3.0, 3.0, 3.0}, {3.0, 0.0, 0.0}, {3.0, -3.0, 0.0}, {0.0, -0.0, 0.0}, {0, 0, 0}};
int N = 7, paso = 0;

void iniciar()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    // La camara se desplaza sobre el plano xz
    gluLookAt(px0, py0, pz0, px1, py1, pz1, 0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    ejes(2);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    if (paso == 1)
    {
        glPointSize(5);
        graficaPuntosBezier();
        glPointSize(1);
        glColor3f(0.0, 1.0, 0.0);
        graficaCurvaBezier();
    }
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

void graficaPuntosBezier(void)
{
    float x, y, z;
    //glBegin(GL_POINTS);
    for (int i = 0; i < N; i++)
    {
        x = pcontrol[i][0];
        y = pcontrol[i][1];
        z = pcontrol[i][2];
        glPushMatrix();
        glTranslatef(x, y, z);
        glutWireSphere(0.1, 20, 20);
        glPopMatrix();
        //glVertex3f(x, y, z);
    }
    //glEnd();
}
/********************/
void graficaCurvaBezier(void)
{
    float x, y, z;
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0; u <= 1; u += 0.01)
    {
        x = CurvaBezier(u, 0);
        y = CurvaBezier(u, 1);
        z = CurvaBezier(u, 2);
        glVertex3f(x, y, z);
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

void CubeSpin()
{
    theta[axis] += .02;
    if (theta[axis] > 360)
        theta[axis] -= 360.0;
    display();
}

void rotacamara()
{
    px1 = px0 + radio * sin(angulo);
    pz1 = pz0 - radio * cos(angulo);
}

void mirarAbajo(){
    py1 = py0 + radio * sin(angulo2);
    pz1 = pz0 - radio * cos(angulo2);
}

void avanza()
{
    px0 = px1;
    pz0 = pz1;
    px1 = px0 - radio * sin(angulo);
    pz1 = pz0 - radio * cos(angulo);
}

void retro()
{
    px1 = px0;
    pz1 = pz0;
    px0 = px0 - radio * sin(angulo);
    pz0 = pz0 + radio * cos(angulo);
}

void subir(){
    py0 = py1;
    pz0 = pz1;
    py1 = py0 + radio * sin(angulo);
    pz1 = pz0 - radio * cos(angulo);
}

void bajar(){
    py1 = py0;
    pz1 = pz0;
    py0 = py0 - radio * cos(angulo);
    pz0 = pz0 + radio * sin(angulo);
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'i':
        avanza();
        break;
    case 'm':
        retro();
        break;
    case 'o':
        subir();
        break;
    case 'p':
        bajar();
        break;
    case 'k':
        angulo = angulo + incremento_angulo;
        rotacamara();
        break;
    case 'j':
        angulo = angulo - incremento_angulo;
        rotacamara();
        break;
    case 'r':
        angulo2 = angulo2 + incremento_angulo2;
        mirarAbajo();
        break;
    case 't':
        angulo2 = angulo2 - incremento_angulo2;
        mirarAbajo();
        break;
    case 'a':
        axis = 0;
        break;
    case 's':
        axis = 1;
        break;
    case 'd':
        axis = 2;
        break;
    case 'b':
        paso = 1;
        glutPostRedisplay();
        break;
    case 'f':
        exit(0);
        break;
    }
}

void ejes(int longitud)
{
    glBegin(GL_LINES);
    glVertex3d(0, 0, longitud);
    glVertex3d(0, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(0, longitud, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(longitud, 0, 0);
    glEnd();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CAMARA MOVIL");
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}