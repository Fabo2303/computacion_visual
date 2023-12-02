#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

int order = 0; // Puedes ajustar el orden según sea necesario
float lado = 10;
float xA, yA;
float vertices[] = {0.0f, 0.0f};

void verificadorDireccion(float, float, float, float, bool, float);

void drawDragonCurve(int order, float x1, float y1, float x2, float y2, float lado, bool dir)
{
    if (order == 0)
    {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    else
    {
        float ladoAux = lado / 2;
        verificadorDireccion(x1, y1, x2, y2, dir, ladoAux);
        float xA = vertices[0];
        float yA = vertices[1];
        drawDragonCurve(order - 1, x1, y1, xA, yA, lado / sqrt(2), dir);
        drawDragonCurve(order - 1, xA, yA, x2, y2, lado / sqrt(2), !dir);
    }
}

void verificadorDireccion(float x1, float y1, float x2, float y2, bool direccion, float lado)
{
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;
    float modulo = direccion ? 1 : -1;
    if (deltaX == 0)
    {
        vertices[0] = (x1 + x2) / 2 + modulo * lado;
        vertices[1] = (y1 + y2) / 2;
        return;
    }
    if (deltaY == 0)
    {
        vertices[0] = (x1 + x2) / 2;
        vertices[1] = (y1 + y2) / 2 + modulo * lado;
        return;
    }
    float m = deltaY / deltaX;
    if (m > 0)
    {
        vertices[0] = direccion ? x1 : x2;
        vertices[1] = direccion ? y2 : y1;
    }
    else
    {
        vertices[0] = direccion ? x2 : x1;
        vertices[1] = direccion ? y1 : y2;
    }
    return;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco

    // Llama a la función de dibujo de la curva del dragón
    drawDragonCurve(order, -5.0, 5.0, 5.0, 5.0, lado, true);
    glEnd();
    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'b':
        order++;
        glutPostRedisplay();
        break;

    case 'n':
        order--;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Dragon Curve - OpenGL");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color de fondo negro

    glutMainLoop();
    return 0;
}
