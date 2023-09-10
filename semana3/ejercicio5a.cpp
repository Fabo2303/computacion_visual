#include <cmath>
#include <GL/glut.h>
#include <iostream>

void init();

void display();

void reshape(int, int);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);
}

void display() {
    GLfloat ang, r = 4.0f, x, y;
    int nVertices = 6;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(5.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0); // Puntos en negro
    float verif = nVertices / 2;
    int min = nVertices % 2 != 0 ? nVertices : nVertices - 1;
    for (int i = 0; i < nVertices; ++i) {
        if (i < ceil(verif))
            ang = 2 * M_PI * (2 * i) / nVertices;
        else
            ang = 2 * M_PI * (2 * i - min) / nVertices;
        x = r * sin(ang);
        y = r * cos(ang);

        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}