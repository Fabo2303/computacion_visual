#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include <GL/freeglut.h>

void init();
void display();
void reshape(int,int);
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
void init()
{
    glClearColor(1.0,1.0,1.0,0.0); //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(5.0);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // Puntos en rojo
    glVertex2f(-6, 0);
    glVertex2f(6, 0);
    glColor3f(0.0, 0.0, 0.0); // Puntos en negro
    glVertex2f(-6, -1);
    glVertex2f(-2, -1);
    glVertex2f(-6, -0.5);
    glVertex2f(-6, -1.5);
    glVertex2f(-2, -0.5);
    glVertex2f(-2, -1.5);
    glEnd();
    glRasterPos2f(-4.5, -1.5); // Posición donde se dibujará el texto
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '/');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}