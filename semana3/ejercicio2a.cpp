#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glut.h>

void init();

void display();

void reshape(int, int);

void abasico(int, int, int, int);

void dda(int, int, int, int);

void bresenham(int, int, int, int);

void ingresoDatos();

void menu();

void menuFunc(int);

int px0, py0, px1, py1;
int mainMenu;
int opc = 1;

int main(int argc, char **argv) {
    ingresoDatos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(1200, 100);
    glutCreateWindow("Algoritmo Basico");
    init();
    menu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void menuFunc(int value) {
    if(value == 4) exit(0);
    opc = value;
    glutPostRedisplay();
}

void menu() {
    mainMenu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Basico", 1);
    glutAddMenuEntry("DDA", 2);
    glutAddMenuEntry("Punto Medio", 3);
    glutSetMenu(mainMenu);
    glutAddMenuEntry("Salir", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();   // salva el estado actual de la matriz
    glColor3f(0, 0, 1);   // Azul
    glPointSize(4);   // Fije el grosor de pixel = 2
    switch (opc) {
        case 1:
            abasico(px0, py0, px1, py1);
            break;
        case 2:
            dda(px0, py0, px1, py1);
            break;
        case 3:
            bresenham(px0, py0, px1, py1);
    }
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

void abasico(int x0, int y0, int x1, int y1) {
    int x;
    float dx, dy, m, b, y;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    b = y0 - m * x0;
    y = y0;
    glBegin(GL_POINTS);
    for (x = x0; x <= x1; x++) {
        y = m * x + b;
        std::cout << x << "  " << y << "  " << (int) ceil(y - 0.5) << "\n";
        glVertex2f(x, (int) ceil(y - 0.5));
    }
    glEnd();
}

void dda(int x0, int y0, int x1, int y1) {
    int x;
    float dx, dy, m, y;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    y = y0;
    glBegin(GL_POINTS);
    for (x = x0; x <= x1; x++) {
        std::cout << x << "  " << y << "  " << round(y) << "\n";
        glVertex2f(x, round(y));
        y += m;
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

void ingresoDatos() {
    std::cout << "\n leer px0 = ";
    std::cin >> px0;
    std::cout << "\n leer py0 = ";
    std::cin >> py0;
    std::cout << "\n leer px1 = ";
    std::cin >> px1;
    std::cout << "\n leer py1 = ";
    std::cin >> py1;
}