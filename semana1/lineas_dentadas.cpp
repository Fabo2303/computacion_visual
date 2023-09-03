#include <cmath>
#include <GL/glut.h>
#include <iostream>

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
    GLfloat ang, R = 7.0f, r = 4.0f,  x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(5.0);
    glBegin(GL_LINE_LOOP);


    glColor3f(1.0, 0.0, 0.0); // Puntos en negro
    for (int i = 0; i < 20; ++i)
    {
        float ang = 2 * M_PI * i / 20;
        float x, y;

        if (i % 2 == 0)
        {
            x = r * sin(ang);
            y = r * cos(ang);
        }
        else
        {
            x = R * sin(ang);
            y = R * cos(ang);
        }

        glVertex2f(x, y);
    }
    glEnd();
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
