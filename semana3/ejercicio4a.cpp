#include <iostream>
#include <cmath>
#include <GL/glut.h>

void init();

void display();

void reshape(int, int);

void controlRaton(int, int, int, int);

void bresenham(int, int, int, int);

void casos(int, int, int, int);

void vertical(int, int, int, int);

void horizontal(int, int, int, int);

bool entrar = false;

int indicador = 0;

int X0, Y0, X1, Y1;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(1200, 100);
    glutCreateWindow("Algoritmo Basico");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(controlRaton);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void controlRaton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (indicador == 0) {
            X0 = (x >= 300) ? (x - 300) / 12 : (-x - 300) / 12;
            Y0 = (y <= 300) ? (y + 300) / 12 : (-y + 300) / 12;
            indicador++;
            std::cout << "X: " << X0 << " Y: " << Y0 << "\n";
        } else if (indicador == 1) {
            X1 = (x >= 300) ? (x - 300) / 12 : (-x - 300) / 12;
            Y1 = (y <= 300) ? (y + 300) / 12 : (-y + 300) / 12;
            indicador++;
            entrar = true;
            std::cout << "X: " << X1 << " Y: " << Y1 << "\n";
        }
    }
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();   // salva el estado actual de la matriz
    glColor3f(0, 0, 1);   // Azul
    glPointSize(4);   // Fije el grosor de pixel = 2
    if (entrar) {
        casos(X0, Y0, X1, Y1);
    }
    //casos(-44, 45, 10, -11);
    //casos(1, 8, 1, 1);
    //casos(8, 1, 1, 1);
    //casos(1, 1, 8, 1);
    //casos(1, 2, 7, 8);
    glPopMatrix();   // recupera el estado del matriz
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void casos(int x0, int y0, int x1, int y1) {
    if (x0 == x1) {
        vertical(x0, y0, x1, y1);
    } else if (y0 == y1) {
        horizontal(x0, y0, x1, y1);
    } else {
        bresenham(x0, y0, x1, y1);
    }
}

void vertical(int x0, int y0, int x1, int y1) {
    glBegin(GL_POINTS);
    int x = x0;
    int yi = y0 < y1 ? y0 : y1;
    int yj = y0 < y1 ? y1 : y0;
    for (int y = yi; y <= yj; y++) {
        glVertex2f(x, y);
    }
    glEnd();
}

void horizontal(int x0, int y0, int x1, int y1) {
    glBegin(GL_POINTS);
    int y = y0;
    int xi = x0 < x1 ? x0 : x1;
    int xj = x0 < x1 ? x1 : x0;
    for (int x = xi; x <= xj; x++) {
        glVertex2f(x, y);
    }
    glEnd();
}

void bresenham(int x0, int y0, int x1, int y1) {
    int dx, dy, dE, dNE, d, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    d = 2 * dy - dx;
    dE = 2 * dy;
    dNE = 2 * (dy - dx);
    x = x0;
    y = y0;
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    while (x < x1) {
        if (d <= 0) {
            d += dE;
            x++;
        } else {
            d += dNE;
            x++;
            y++;
        }
        glVertex2f(x, y);
    }
    glEnd();
}
