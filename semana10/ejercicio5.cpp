#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include <iostream>
#define miLista 1

void ejes(int);
GLdouble angulo = 0, incremento_angulo = 0.1;
GLdouble const radio = 0.5;
GLfloat px0 = 0, py0 = 0, pz0 = 5;
GLfloat px1 = 0, py1 = 0, pz1 = 4;
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;

void iniciar()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void cilindro(double radius, double base, double cortes)
{
    double i, j, k;
    double x, y, z, twopi;
    twopi = 2 * M_PI;
    double ang = 0;
    double av = twopi / (base);
    bool entrar = false;
    glNewList(miLista, GL_COMPILE);
    for (i = 0; i < base; i++)
    {
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < 2; j++)
        {
            for (k = radius / 2; k >= -radius / 2; k -= radius)
            {
                x = radius * cos(ang);
                y = entrar ? -k : k;
                z = radius * sin(ang);
                glVertex3f(x, y, z);
            }
            entrar = !entrar;
            ang = entrar ? ang + av : ang;
        }
        glEnd();
    }
    ang = 0;
    for (i = radius / 2; i >= -radius / 2; i -= radius / cortes)
    {
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < base; j++)
        {
            x = radius * cos(ang);
            y = i;
            z = radius * sin(ang);
            glVertex3f(x, y, z);
            ang += av;
        }
        glEnd();
    }
    glEndList();
}

void cilindroAlargado()
{
    glPushMatrix();
    glCallList(miLista);
    glPopMatrix();
}

void initMolecula()
{
    glNewList(2, GL_COMPILE);
    glTranslatef(2, 2, -2);
    glPushMatrix();
    glColor3f(1, 0, 0);
    glutWireSphere(2, 20, 20);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(0, 4, 0);
    glScalef(0.3, 2, 0.3);
    cilindroAlargado();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(0, 3, 0);
    glScalef(0.3, 1, 0.3);
    cilindroAlargado();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-45, 1, 0, 1);
    glPushMatrix();
        glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(0, 3, 0);
        glScalef(0.3, 1, 0.3);
        cilindroAlargado();
        glPopMatrix();
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0, 5, 0);
        glScalef(0.3, 1, 0.3);
        cilindroAlargado();
        glPopMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0, 7.5, 0);
        glutWireSphere(1.5, 20, 20);
    glPopMatrix();
    glPopMatrix();
    glEndList();
}

void cubanoSuperior(){
    glPushMatrix();
    glCallList(2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-4, 0, 0);
        glRotatef(90, 0, 1, 0);
        glCallList(2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-4, 0, 4);
        glRotatef(180, 0, 1, 0);
        glCallList(2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, 4);
        glRotatef(270, 0, 1, 0);
        glCallList(2);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    // La camara se desplaza sobre el plano xz
    gluLookAt(px0, 0.0, pz0, px1, 0.0, pz1, 0, 1, 0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glPushMatrix();
    cubanoSuperior();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -4, 0);
    glScalef(1.0f, -1.0f, 1.0f); //Reflexion eje Y
    cubanoSuperior();
    glPopMatrix();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

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

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'a':
        theta[1] += 5.0;
        break;
    case 's':
        theta[0] += 5.0;
        break;
    case 'd':
        theta[2] += 5.0;
        break;
    case 'i':
        avanza();
        break;
    case 'm':
        retro();
        break;
    case 'j':
        angulo = angulo + incremento_angulo;
        rotacamara();
        break;
    case 'k':
        angulo = angulo - incremento_angulo;
        rotacamara();
        break;
    case 'f':
        exit(0);
        break;
    }
    glutPostRedisplay();
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
    cilindro(2, 10, 10);
    initMolecula();
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    // glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}