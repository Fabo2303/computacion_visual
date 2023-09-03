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
    GLfloat ang, R = 8.0f, r = 4.0f,  x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(5.0);
    glBegin(GL_LINE_LOOP);


    glColor3f(1.0, 0.0, 0.0); // Puntos en negro
    int i = 0;
    bool a = false;
    float arg = 2 * M_PI /80;
    for (ang = -1 * arg; ang < 2 * M_PI; ang += arg)
    {
        if(i % 2 == 0 && a){
            ang -= arg;
        }
        if(i < 2) {
            x = R * sin(ang);
            y = R * cos(ang);
        }
        if(i >= 2 && i< 4){
            x = r * sin(ang);
            y = r * cos(ang);
        }
        i++;
        if(i==4){
            i = 0;
        }
        a = true;
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