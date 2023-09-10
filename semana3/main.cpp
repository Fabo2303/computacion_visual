#include <GL/glut.h>
#include <cmath>

int sides = 5;     // Número de lados del polígono regular (pentágono por defecto)
int spikes = 3;    // Factor que determina la cantidad de picos (2 por defecto)

void drawStarPolygon() {
    glColor3f(1.0, 1.0, 1.0); // Color blanco
    glBegin(GL_LINE_LOOP);

    float centerX = 0.0;
    float centerY = 0.0;
    float radius = 0.5;

    for (int i = 0; i < sides * spikes; ++i) {
        float angle = 2 * M_PI * i / (sides * spikes);
        float x, y;

        if (i % 2 == 0) {
            x = centerX + radius * cos(angle);
            y = centerY + radius * sin(angle);
        } else {
            x = centerX + (radius / 2.0) * cos(angle);
            y = centerY + (radius / 2.0) * sin(angle);
        }

        glVertex2f(x, y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawStarPolygon();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Polígono Estrellado");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
