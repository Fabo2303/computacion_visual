#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include <GL/freeglut.h>

void init();
void display();
void reshape(int, int);
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void drawKochCurve(int order, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    if (order == 0)
    {
        // Dibuja una línea simple si el orden es 0
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
    else
    {
        // Calcula puntos intermedios
        GLfloat deltaX = (x2 - x1) / 3.0;
        GLfloat deltaY = (y2 - y1) / 3.0;
        GLfloat xA = x1 + deltaX;
        GLfloat yA = y1 + deltaY;
        GLfloat xB = x1 + 2.0 * deltaX;
        GLfloat yB = y1 + 2.0 * deltaY;
        GLfloat xC = xA + (cos(M_PI / 3.0) * deltaX - sin(M_PI / 3.0) * deltaY);
        GLfloat yC = yA + (sin(M_PI / 3.0) * deltaX + cos(M_PI / 3.0) * deltaY);

        // Llama a la función recursivamente para los segmentos de la curva
        drawKochCurve(order - 1, x1, y1, xA, yA);
        drawKochCurve(order - 1, xA, yA, xC, yC);
        drawKochCurve(order - 1, xC, yC, xB, yB);
        drawKochCurve(order - 1, xB, yB, x2, y2);
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // salva el estado actual de la matriz
    glPointSize(5.0);
    glLineWidth(4.0f);
    glColor3f(1, 0, 0);
    drawKochCurve(1, -6, 0, 6, 0);
    glBegin(GL_LINES);
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
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}