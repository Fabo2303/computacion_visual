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
    glutInitWindowSize(800,800);
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

void diskete(){
    glLoadIdentity();

    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Define la vista en el plano XY

    GLUquadricObj *pt;
    pt = gluNewQuadric();
    gluQuadricDrawStyle(pt, GLU_LINE);
    glColor3f(1.0, 0.0, 0.0);

    gluDisk(pt, 0, 7, 20, 6);
}

void display()
{
    GLfloat ang, r,  x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    diskete();
    glBegin(GL_LINE_STRIP);


    glColor3f(0.0, 0.0, 1.0); // Puntos en negro
    float arg = 2 * M_PI /1000;

    // a = 2 b = 3
    for (ang = 0; ang < 2 * M_PI; ang += arg)
    {
        x = 3 * cos(ang);
        y = 2 * sin(ang);
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