#include <cmath>
#include <GL/glut.h>

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

void drawHiperbole(int abcisas, int ordenadas){
    for (float i = 0.5; i < 10; i += 0.4)
    {
        glVertex2f(abcisas * i, 0);
        glVertex2f(0, ordenadas * (10 - i));
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(2.0);
    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 1.0); // Puntos en negro

    drawHiperbole(1,1);
    drawHiperbole(-1, 1);
    drawHiperbole(-1, -1);
    drawHiperbole(1, -1);

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