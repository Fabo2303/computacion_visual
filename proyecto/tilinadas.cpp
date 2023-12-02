#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

void display()
{
    float x1 = -5, y1 = 0, x2 = 5, y2 = 0;

    // Calcular el punto medio entre (x1, y1) y (x2, y2)
    float xMid = (x1 + x2) / 2;
    float yMid = (y1 + y2) / 2;

    // Calcular la mitad de la distancia entre (x1, y1) y (x2, y2)
    float halfDistance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / 2;

    // Calcular las coordenadas del tercer vértice del triángulo rectángulo isósceles
    float angle = 45.0;                      // Ángulo en grados
    float angleRad = angle * (M_PI / 180.0); // Convertir a radianes

    float a = 5;

    float x3 = xMid + a / sqrt(2);
    float y3 = yMid + a / sqrt(2);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x3, y3);
    glVertex2f(x3, y3);
    glVertex2f(x2, y2);
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
        glutPostRedisplay();
        break;

    case 'n':
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
