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
    glutInitWindowSize(600,600);
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

void drawCircle(float radio, float start, float end, float h, float k){
    float x,y,ang;
    for (ang = start; ang < end; ang += 2 * M_PI/10000)
    {
        x = radio * cos(ang) + h;
        y = radio * sin(ang) + k;
        glVertex2f(x,y);
    }
}

void display()
{
    GLfloat r = 8.0f;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(2.0);

    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0); // Puntos en negro
    drawCircle(r, M_PI/2, 3 * M_PI/2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); // Puntos en negro
    drawCircle(r, M_PI/2, 3 * M_PI/2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r, 3* M_PI/2,   5 * M_PI / 2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(r/2, 0.0f,   2 * M_PI, 0, r/2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r/2, 0.0f,   2 * M_PI, 0, -r/2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r/6, 0.0f,   2 * M_PI, 0, r/2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(r/6, 0.0f,   2 * M_PI, 0, -r/2);
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