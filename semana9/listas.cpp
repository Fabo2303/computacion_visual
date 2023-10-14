#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glut.h>
#define miListaCirculo 1

void init();

void display();

void reshape(int, int);

void drawCircle(GLfloat);

void drawCircle2(GLfloat);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmo Basico");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    drawCircle2(5);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();   // salva el estado actual de la matriz
    glColor3f(0, 0, 1);   // Azul
    //drawCircle(5);
    glCallList(miListaCirculo);
    glPopMatrix();   // recupera el estado del matriz
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCircle(GLfloat radio){
    GLint i;
    GLfloat x, y;
    glBegin(GL_POLYGON);
    for(i = 0; i < 1000; i++){
        x = radio * cos(i * 2 * M_PI / 1000);
        y = radio * sin(i * 2 * M_PI / 1000);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCircle2(GLfloat radio){
    GLint i;
    GLfloat x, y;
    glNewList(miListaCirculo, GL_COMPILE);

    glBegin(GL_POLYGON);
    for(i = 0; i < 1000; i++){
        x = radio * cos(i * 2 * M_PI / 1000);
        y = radio * sin(i * 2 * M_PI / 1000);
        glVertex2f(x, y);
    }
    glEnd();

    glEndList();
}